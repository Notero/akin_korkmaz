//
//  main.c
//  magicContainment
//
//  Created by Akin Korkmaz on 10/20/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void quickSort(double * arr, int len) {
    
    if (len <= 1)
        return;
    
    double pivot = arr[0];
    
    int fptr = 1;
    int bptr = len-1;
    for (int i = 0; i < len-1; i++) {
        if (arr[fptr] < pivot) {
            // into smaller
            fptr++;
        } else {
            // into greater
            double tmp = arr[fptr];
            arr[fptr] = arr[bptr];
            arr[bptr] = tmp;
            bptr--;
        }
    }
    // Swap the pivot with last of smaller partition
    double tmp = arr[0];
    arr[0] = arr[fptr-1];
    arr[fptr-1] = tmp;
    // Sorting the smaller partition
    quickSort(arr, fptr - 1);
    // Sorting the greater partition
    quickSort(arr + fptr, len - fptr);
}

int main(int argc, const char * argv[]) {
    
    int moteN = 0;
    int deviceN = 0;
    double res = 0;
    
    //gets the array size
    if (scanf("%d %d", &moteN, &deviceN) != 2) return 1;
    
    //allocates memmory for arrays
    double * moteVol = (double*) calloc(moteN, sizeof(double));
    double * deviceVol = (double*) calloc(deviceN, sizeof(double));
    
    //Variables
    int moteRadii = 0;
    int deviceDimensions[3] = {0,0,0};
    
    //gets the mote Radius and calculates the Volume accurately
    for (int i = 0; i < moteN; i++) {
        scanf("%d", &moteRadii);
        //using 4.0/3.0 ensures accurate floating point division
        moteVol[i] =  (4.0 / 3.0) * M_PI * (moteRadii * moteRadii * moteRadii);
    }
    
    //gets the dimensions and calculates each device volume
    for (int i = 0; i < deviceN; i++) {
        scanf("%d %d %d", &deviceDimensions[0],&deviceDimensions[1],&deviceDimensions[2]);
        deviceVol[i] = deviceDimensions[0] * deviceDimensions[1] * deviceDimensions[2];
    }
    
    //Sorts Both Arrays
    quickSort(moteVol, moteN);
    quickSort(deviceVol, deviceN);
    
    //uses two pointers to match motes to devices exactly once
    int m = 0;
    int d = 0;
    
    while (m < moteN && d < deviceN) {
        //if the mote volume fits inside the device volume
        if (moteVol[m] <= deviceVol[d]) {
            //it fits! consume the device and move to the next mote
            m++;
            d++;
        } else {
            //device is too small, try the next bigger device
            d++;
        }
    }
    
    //add together all of the other mote Volumes in the array that didn't fit
    for (int i = m; i < moteN; i++) {
        res += moteVol[i];
    }
    
    //prints the result
    printf("%f\n", res);
    
    //free memmory
    free(moteVol);
    free(deviceVol);
    
    return 0;
}
