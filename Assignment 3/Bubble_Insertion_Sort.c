#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* arr, int size) {
    int j, key, cct, sct;
    cct = sct = 0;
    for (int i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            sct++;
            cct++;
        }
        arr[j + 1] = key;
    }
    printf("Insertion Sort\nComparison Count: %d\nMove Count: %d\n", cct, sct);
}

void bubbleSort(int* arr, int size){
    int p, bcct, bsct;
    bcct = bsct = 0;
    for(int i = 0;i<size-1;i++){
        for(int j = 0; j<size-i-1;j++){
            if(arr[j]>arr[j+1]){
                bcct++;
                bsct++;
                p = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = p;
            }
        }
    }
    printf("\nBubble Sort\nComparison Count: %d\nSwap Count: %d\n", bcct, bsct);
}

void print(int *arr, int size){
    for (int k = 0; k < size; k++) {
        printf("%d ", arr[k]);
    }
}

int main() {
    int x;
    printf("Enter length of array: ");
    scanf("%d", &x);
    int* arr1 = (int *)malloc(x*sizeof(int));
    int* arr2 = (int *)malloc(x*sizeof(int));
    printf("Enter integers in array: ");
    for (int i = 0; i < x; i++) {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i];
    }
    insertionSort(arr1, x);
    print(arr1, x);
    printf("\n");
    bubbleSort(arr2, x);
    print(arr2,x);
    return 0;
}
