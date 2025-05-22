#include <stdio.h>
#include <random>
#include <time.h>
#include <thread>

//funktionsdeklarationer
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
int quickSort(int arr[], int low, int high);
int getRandomInt(int min, int max);
int readIntegersFromFile(const char* filename, int arr[], int maxSize);


//hjälpfunktion för qs
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//hjälpfunktion för qs
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

//funktion för utskrift av räcka
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {

    

    int arr[] = { 0 };
	for (int i = 0; i < 100; i++) arr[i] = getRandomInt(0, 100);


    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);
    printf("Sorted array:   ");
    printArray(arr, n);
    return 0;
}

//slumpad integer, ge minimum- och maxvärden som argument för intervallen du
//vill ha slumptalet från
int getRandomInt(int min, int max) {
    static std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

//funktion för inläsning till räcka från fil
int readIntegersFromFile(const char* filename, int arr[], int maxSize) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }
    int count = 0;
    while (count < maxSize && fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }
    fclose(file);
    return count;
}