//
//  main.c
//  spellconstruction
//
//  Created by Akin Korkmaz on 10/7/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ***Function Declarations***
void readBlocks(void);
void checkIfAnySame(void);
int getOverlap(char *str1, char *str2);

char ** inputBlocks = NULL;
int xMany = 0;
int xLong = 0;

int main(void) {
    
    //gets all the required information from the panel input
    readBlocks();
    
    //check wheather any block in the array is equal to eachother ,
    //and rebuild the array also adjust the xMany count for keeping track of the amount of blocks present
    checkIfAnySame();

    if (xMany == 0) return 0;

    //loop until everything is merged into one final block
    while (xMany > 1) {
        int maxOverlap = -1;
        int bestLeft = 0;
        int bestRight = 1;

        //check all pairs to find the biggest overlap
        for (int i = 0; i < xMany; i++) {
            for (int j = 0; j < xMany; j++) {
                if (i == j) continue;

                int overlap = getOverlap(inputBlocks[i], inputBlocks[j]);
                if (overlap > maxOverlap) {
                    maxOverlap = overlap;
                    bestLeft = i;
                    bestRight = j;
                }
            }
        }

        //length is both strings minus the overlap amount
        int mergedLen = strlen(inputBlocks[bestLeft]) + strlen(inputBlocks[bestRight]) - maxOverlap;
        char *mergedStr = (char *)malloc((mergedLen + 1) * sizeof(char));

        //use strcpy and strcat to put them together
        strcpy(mergedStr, inputBlocks[bestLeft]);
        strcat(mergedStr, inputBlocks[bestRight] + maxOverlap);

        //free the memory for the old blocks
        free(inputBlocks[bestLeft]);
        free(inputBlocks[bestRight]);

        //put the merged string back into the array
        inputBlocks[bestLeft] = mergedStr;

        //shift non-null entries down to fill the gap
        for (int k = bestRight; k < xMany - 1; k++) {
            inputBlocks[k] = inputBlocks[k + 1];
        }
        xMany--;
    }

    //print the final spell
    printf("%s\n", inputBlocks[0]);

    free(inputBlocks[0]);
    free(inputBlocks);

    return 0;
}

//check amount to add from begining of str2 to the end of str1
int getOverlap(char *str1, char *str2) {
    int len1 = (int)strlen(str1);
    int len2 = (int)strlen(str2);
    int maxMatch = (len1 < len2) ? len1 : len2;

    for (int len = maxMatch; len > 0; len--) {
        if (strncmp(str1 + len1 - len, str2, len) == 0) {
            return len;
        }
    }
    return 0;
}

void readBlocks(void) {
    scanf("%d", &xMany);
    scanf("%d", &xLong);

    inputBlocks = (char **)calloc(xMany, sizeof(char *));

    for (int i = 0; i < xMany; i++) {
        // Allocate enough memory for xLong characters + 1 for the null terminator
        inputBlocks[i] = (char *)malloc((xLong + 1) * sizeof(char));
        scanf("%s", inputBlocks[i]);
    }
}

void checkIfAnySame(void) {
    int flag = 0;

    // Check for duplicates
    for (int i = 0; i < xMany; i++) {
        if (inputBlocks[i] == NULL) continue;
        for (int j = i + 1; j < xMany; j++) {
            if (inputBlocks[j] != NULL && strcmp(inputBlocks[i], inputBlocks[j]) == 0) {
                free(inputBlocks[j]); // Free the memory for the duplicate block
                inputBlocks[j] = NULL;
                flag++;
            }
        }
    }

    // Rebuild the array without NULL elements
    int writeIdx = 0;
    for (int readIdx = 0; readIdx < xMany; readIdx++) {
        if (inputBlocks[readIdx] != NULL) {
            inputBlocks[writeIdx++] = inputBlocks[readIdx];
        }
    }
    
    // Resize the inputBlocks array to the new size after removing duplicates
    xMany -= flag;
}
