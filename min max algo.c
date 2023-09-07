#include <stdio.h>
void main() {
    printf("Enter length of array: \n");
    int n;
    scanf("%d",&n);
    int arr[n];
    int x;
    for(int i = 0; i<n; i++){
        scanf("%d",&x);
        arr[i] = x;
    }
    int l;
    int h;
    int min;
    int max;
    for(int j = 0; j<n; j=j+2){
        if(arr[j]<arr[j+1]){
            if(arr[j]<min) min = arr[j];
            if(arr[j+1]>max) max = arr[j+1];
        }
        else
            if(arr[j+1]<min) min = arr[j+1];
            if(arr[j]>max) max = arr[j];
    }
    printf("%d %d", min, max);
}