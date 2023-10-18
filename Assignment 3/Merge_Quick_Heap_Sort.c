#include <stdio.h>
#include <stdlib.h>

// Function to print an array
void print(int *arr, int size) {
    for (int k = 0; k < size; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");
}

void merge(int *arr, int a, int b, int c, int *cct) {
    int arr1[b - a + 1], arr2[c - b];
    int k = 0;

    // Copy elements to two temporary arrays
    for (int i = 0; i < b - a + 1; i++) {
        arr1[i] = arr[a + i];
        k++;
    }
    for (int j = 0; j < c - b; j++) {
        arr2[j] = arr[b + 1 + j];
        k++;
    }

    int p = 0;
    int q = 0;
    int r = a;

    // Merge the two arrays back into the original array
    while (p < b - a + 1 && q < c - b) {
        (*cct) = (*cct) + 3;

        if (arr1[p] <= arr2[q]) {
            arr[r] = arr1[p];
            p++;
        } else {
            arr[r] = arr2[q];
            q++;
        }
        r++;
    }

    // Copy remaining elements into the two arrays
    while (q < c - b) {
        arr[r] = arr2[q];
        q++;
        r++;
    }
    while (p < b - a + 1) {
        arr[r] = arr1[p];
        p++;
        r++;
    }
}

// Merge sort function
void mergeSort(int *arr, int a, int c, int *cct) {
    int b = a + (c - a) / 2;
    (*cct)++;

    if (a < c) {
        //first half of array is sorted
        mergeSort(arr, a, b, cct);
        //second half of array is sorted
        mergeSort(arr, b + 1, c, cct);
        //the two sorted halves are merged back together
        merge(arr, a, b, c, cct);
    }
}

// Function to swap two elements in an array
void swap(int *arr, int y, int z) {
    int temp = arr[y];
    arr[y] = arr[z];
    arr[z] = temp;
}

// Quick Sort function
void quickSort(int *arr, int a, int c, int *cct, int *sct) {
    if (a < c) {
        int pivot = arr[a];//set pivot as the first element in the array
        int ptr1 = c + 1;

        // Partition the array so that elements smaller than the pivot are to the left of the pivot and the elements greater than the pivot are to the right of the pivot
        for (int ptr2 = c; ptr2 > a; ptr2--) {
            if (arr[ptr2] > pivot) {
                (*cct)++;
                ptr1--;
                (*sct)++;
                swap(arr, ptr1, ptr2);
            }
        }

        (*sct)++;
        //puts pivot in the right place in the array
        swap(arr, ptr1 - 1, a);

        //half of array with elements greater than array is sorted
        quickSort(arr, a, ptr1 - 2, cct, sct);
        //half of array with elements less than array is sorted
        quickSort(arr, ptr1, c, cct, sct);
    }
}

// Heapify the array
void heapify(int *arr, int n, int i, int *cct, int *sct) {
    int largest, left, right, j;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        largest = i;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
            (*cct)++;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
            (*cct)++;
        }

        if (largest != i) {
            swap(arr, i, largest);
            (*sct)++;
            i = largest;
        } else {
            break;
        }
    }
}

// Heap Sort function
void heapSort(int *arr, int size, int *cct, int *sct) {
    // Builds a max heap
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(arr, size, i, cct, sct);
    }

    for (int j = size - 1; j >= 0; j--) {
        swap(arr, 0, j);//swaps first element with last and ignores last element
        (*sct)++;
        heapify(arr, j, 0, cct, sct);//heapifys the array till the jth element
    }
}

int main() {
    int x, a, c;
    printf("Enter length of array: ");
    scanf("%d", &x);
    int *array = (int *)malloc(x * sizeof(int));
    int *array2 = (int *)malloc(x * sizeof(int));
    int *array3 = (int *)malloc(x * sizeof(int));

    printf("Enter integers in array: ");
    for (int i = 0; i < x; i++) {
        scanf("%d", &array[i]);
        array2[i] = array[i];
        array3[i] = array[i];
    }

    a = 0;
    c = x - 1;

    printf("Unsorted Array: ");
    print(array, x);

    int mcct = 0;
    mergeSort(array, a, c, &mcct);
    printf("Merge Sorted Array: ");
    print(array, x);
    printf("Time Complexity: %d\n", mcct);

    int qcct = 0;
    int qsct = 0;
    quickSort(array2, a, c, &qcct, &qsct);
    printf("\nQuick Sorted Array: ");
    print(array2, x);
    printf("Comparison Count: %d\nSwap Count: %d\n", qcct, qsct);

    int hcct = 0;
    int hsct = 0;
    heapSort(array3, x, &hcct, &hsct);
    printf("\nHeap Sorted Array: ");
    print(array3, x);
    printf("Comparison Count: %d\nSwap Count: %d\n", hcct, hsct);
}
