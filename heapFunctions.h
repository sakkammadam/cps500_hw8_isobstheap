//
// Created by sakkammadam on 6/19/22.
//

#ifndef CPS500_HW8_ISOBSTHEAP_HEAPFUNCTIONS_H
#define CPS500_HW8_ISOBSTHEAP_HEAPFUNCTIONS_H

// struct for Heap
typedef struct Heap {
    int* array;
    int capacity;
    int size;
} Heap;

void swapHeapValues(int* a, int* b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapifyDown(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[smallest]) {
        smallest = left;
    }
    if (right < n && arr[right] > arr[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swapHeapValues(&arr[i], &arr[smallest]);
        heapifyDown(arr, n, smallest);
    }
}

void heapifyUp(int array[], int size, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] > array[largest])
        largest = l;
    if (r < size && array[r] > array[largest])
        largest = r;
    if (largest != i){
        swapHeapValues(&array[i], &array[largest]);
        heapifyUp(array, size, largest);
    }
}

// function to build a heap
void buildHeap(int arr[], int n){
    for(int i=(n-1)/2; i > 0; i--){
        heapifyDown(arr, n, i);
    }
}


#endif //CPS500_HW8_ISOBSTHEAP_HEAPFUNCTIONS_H
