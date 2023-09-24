#include <stdio.h>
#include <stdbool.h>
int available(int x, int *arr1, int m, bool flag){
    int yn[m];//stores the numbers that aren't in the array before index x.
    for (int i = 0; i < m; i++) {
        yn[i] = i + 1;
    }
    for(int r = 0;r<x;r++){
        yn[arr1[r]-1] = 0;
    }
    int avail[m-x];
    int t = 0;
    for(int u = 0;u<m;u++){
        if(yn[u]!=0){
            avail[t] = yn[u];
            t++;
        }
    }
    int wanted = m+1;
    if(flag==0){
        //finds the smallest number that hasn't been used already that is also larger than the number at x
        for(int k = 0; k<m-x; k++){
            if(avail[k]>arr1[x]&& avail[k]<wanted){
                wanted = avail[k];
            }
        }
    }
    else{
        //finds the largest number out of all numbers that haven't already been used in the permutation 
            arr[pt] = 0;
        wanted = arr1[x];
        for(int e = 0; e<m-x; e++){
            if(avail[e]>wanted){
                wanted = avail[e];
            }
        }
    }
    return wanted;
}

int main() {
    //The idea is to print all possible permutations such that the integers formed by the permutations are in ascending order 
    int n;
    scanf("%d", &n);
    int arr[n];//stores the numbers to be permuted
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    int pt = n;//points to the index of the array
    while(pt>-1){//loops through as long as index being pointed to is not -1, each iteration prints a new permutation
    for (int j = 0; j < n; j++) {
            if(j==n -1) printf("%d", arr[n-1]);
            else printf("%d,",arr[j]);
    }//prints array
    pt--;//starts at pt = n-1
    printf("\n");
    while(pt<n){//used to find the next permutation
        if(arr[pt]==available(pt, arr, n, 1)){//if the number at pt is already the largest number out of all numbers that haven't already been used in the permutation 
            arr[pt] = 0;
            pt--;//then we move to the previous number because it won't be possible to find a number larger than this by changing the number at this index
        }
        else{//this means that the number at this index can still be changed to get a larger permutation
            arr[pt]=available(pt, arr, n, 0);//we replace the number here with the smallest number that hasn't been used already that is also larger than the number at pt
            pt++;//we then move to the next number to see if it needs
        }
        if (pt<0) break;//continues until we have gone through the whole array,a new permutation is found at the end of this loop
    }
    }
    return 0;
}
