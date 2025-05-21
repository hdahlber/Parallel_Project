#include <stdio.h>
#include <random>
#include <time.h>
#include <thread>



// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
// This takes last element as pivot, places the pivot element at its correct sorted position,
// and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Utility function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
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

int getRandomInt(int min, int max) {
    static std::mt19937 mt{ std::random_device{}() }; // Mersenne Twister engine seeded once
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

// test change