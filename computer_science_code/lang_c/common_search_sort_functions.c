//
//  main.c
//  testin
//
//  Created by Akin Korkmaz on 11/28/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//Searching
int binarySearchR(int i, int k, int item,int *arr);
int binarySearchL(int len, int item, int *arr);
int linearSearch(int *arr, int len, int item);
//Sorting
void bubbleSort(int *arr, int len);
void selectionSort(int *arr, int len);
void insertionSort(int *arr, int len);
void mergeSort(int *arr, int l, int r);
void merge(int *arr, int l, int m, int r);

int main(int argc, const char * argv[]) {

    return 0;
}

int binarySearchR(int i, int k, int item, int *arr){
    
    
    
    //checks index out of bounds
    if(i > k)
        return 0;
    //gets midpoint
    int midpoint = (i + k) / 2;
    //checks if midpoint is item
    if (arr[midpoint] == item) {
        return 1;
    }
    
    //recurse conditions
    if (arr[midpoint] > item) {
        return binarySearchR(i, midpoint - 1, item, arr);
    }
    
    return binarySearchR(midpoint + 1, k, item, arr);
}

int binarySearchL(int len, int item, int *arr){
    
    int left = 0;
    int right = len - 1;
    int mid;
    
    while (left <= right) {
        
        mid = (right + left) / 2;
        
        if(arr[mid] == item)
            return 1;
        else if(arr[mid] > item){
            right = mid - 1;
        }else
            left = mid + 1;
        }

    return 0;
}

int linearSearch(int *arr, int len, int item){
    
    for (int i = 0; i < len; i++) {
        if (arr[i] == item) {
            return 1;
        }
    }
    
    return 0;
}

void bubbleSort(int *arr, int len){
        
    int temp = 0;
    int swapped = 0;
    
    for (int i = 0; i < len; i++) {
        swapped = 0;
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
    
}

void selectionSort(int *arr, int len){
    
    int index = 0;
    int temp = 0;
  
    //in a nested loop get the min values index then swap it with the outter loop iterrator index
    
    for (int i = 0; i < len; i ++) {
        
        index = i;
    
        for (int j = i + 1; j < len; j++) {
            if (arr[index] > arr[j]) {
                index = j;
            }
        }
        
        temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;
    
    }
}

void insertionSort(int *arr, int len){
    int temp = 0;
    int j = 0;
    for (int i = 1; i < len; i++) {
        temp = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > temp) {
                arr[j+1] = arr[j];
                
            }else
                break;
        }
        arr[j + 1] = temp;
    }
}

void mergeSort(int *arr, int l, int r){
   
    if (r > l) {
        int midpoint = (r + l)/2;
        
        mergeSort(arr, l, midpoint);
        mergeSort(arr, midpoint + 1, r);
        
        merge(arr, l, midpoint, r);
    }
    
}

void merge(int *arr, int l, int m , int r){
    
    int i,j,k;
    //gets size for both arrays
    int Lsize = m - l + 1;
    int Rsize = r - m;
    //Allocate Memmory
    int *L = malloc(sizeof(int)*Lsize);
    int *R = malloc(sizeof(int)*Rsize);
    //initiate array
    for (i = 0; i < Lsize; i++) {
        L[i] = arr[l+i];
    }
    //initiate array
    for (j = 0; j < Rsize; j++) {
        R[j] = arr[m + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < Lsize && j < Rsize) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
            k++;
        }else{
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    
    while(i < Lsize){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < Rsize) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
    
}
