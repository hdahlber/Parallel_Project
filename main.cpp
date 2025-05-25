#include <stdio.h>
#include <random>
#include <time.h>
#include <thread>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <windows.h>
#include <intrin.h>

#include <cstdlib>
//funktionsdeklarationer
/*
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
int quickSort(int arr[], int low, int high);
int getRandomInt(int min, int max);
int readIntegersFromFile(const char* filename, int arr[], int maxSize);
*/
const int MAX_SIZE = 1000000;


void writeSystemInfo(std::ofstream& out) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    int cpuInfo[4] = { -1 };
    char cpuBrand[0x40];
    __cpuid(cpuInfo, 0x80000000);
    unsigned int nExIds = cpuInfo[0];

    memset(cpuBrand, 0, sizeof(cpuBrand));
    if (nExIds >= 0x80000004) {
        __cpuid((int*)cpuInfo, 0x80000002);
        memcpy(cpuBrand, cpuInfo, sizeof(cpuInfo));
        __cpuid((int*)cpuInfo, 0x80000003);
        memcpy(cpuBrand + 16, cpuInfo, sizeof(cpuInfo));
        __cpuid((int*)cpuInfo, 0x80000004);
        memcpy(cpuBrand + 32, cpuInfo, sizeof(cpuInfo));
    }

    out << "System Info:\n";
    out << "CPU: " << cpuBrand << "\n";
    out << "Logical Processors: " << sysInfo.dwNumberOfProcessors << "\n\n";
}



//hj�lpfunktion f�r qs
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//hj�lpfunktion f�r qs
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//qs
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortParallel(int arr[], int low, int high,int depth = 0, int maxDepth = 4) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (depth < maxDepth) {
            std::thread left(quickSortParallel, arr, low, pi - 1, depth + 1, maxDepth);
            std::thread right(quickSortParallel, arr, pi + 1, high, depth + 1, maxDepth);
            left.join();
            right.join();
        } else {
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}



//funktion f�r utskrift av r�cka
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
bool isSorted(const int* arr, int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {



    /*
    int arr[] = { 0 };
	for (int i = 0; i < 100; i++) arr[i] = getRandomInt(0, 100);


    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    printArray(arr, n);
    */
    std::string folder = argv[1];
    std::string base_path = "data/" + folder + "/";
    std::stringstream results_path;
    results_path << "data/" << folder << "/result.txt";
    std::ofstream results_file(results_path.str().c_str());

    writeSystemInfo(results_file);

    for (int file_num = 0; file_num < 10; ++file_num) {
        std::stringstream file_path;
        file_path << base_path << file_num << ".txt";
        std::ifstream input_file(file_path.str().c_str());

        int* arr = new int[MAX_SIZE];
        int size = 0;
        while (size < MAX_SIZE && input_file >> arr[size]) {
            ++size;
        }
        input_file.close();

        int* arr_copy = new int[size];
        std::copy(arr, arr + size, arr_copy);


        auto start_base = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, size - 1);
        auto end_base = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration_base = end_base - start_base;
        bool ok_base = isSorted(arr, size);

        auto start_mt = std::chrono::high_resolution_clock::now();
        quickSortParallel(arr_copy, 0, size - 1);
        auto end_mt = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_mt = end_mt - start_mt;
        bool ok_mt = isSorted(arr_copy, size);
        results_file << "Folder: " << folder
                     << ", File: " << file_num << ".txt"
                     << ", Naive(ms): " << std::fixed << std::setprecision(3) << duration_base.count()
                     << ", MT(ms): " << duration_mt.count()
                     << ", Sorted_Naive: " << (ok_base ? "Yes" : "No")
                     << ", Sorted_MT: " << (ok_mt ? "Yes" : "No") << "\n";

        delete[] arr;
    }
    results_file.close();
    return 0;
}
