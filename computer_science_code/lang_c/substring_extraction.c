//
//  main.c
//  SpellbookMinimizationProblem
//
//  Created by Akin Korkmaz on 8/21/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN_MAX (100 + 1 + 1)

// trims newline char from the string
void trim_newline(char str[LEN_MAX]){
    int index = 0;
    while(str[index] != '\0' && str[index] != '\n')
        index++;
    if(str[index] == '\n')
        str[index] = '\0';
}

int LongerString(char* str1, char* str2){
    // if str1 is longer
    if(strlen(str1) > strlen(str2))
        return 1;
    // otherwise
    else
        return 2;
}

int getAllSpells(char ***Spells) {
    *Spells = malloc(100 * sizeof(char*));
    if (*Spells == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    char *Spell = malloc(LEN_MAX * sizeof(char));
    if (Spell == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    int i = 0;
    while (i < 100) {
        if (fgets(Spell, LEN_MAX, stdin) == NULL) {
            break;
        }
        trim_newline(Spell);
        if (strcmp(Spell, "END") == 0) {
            break;
        }
        (*Spells)[i] = malloc(sizeof(char) * (100+2));
        if ((*Spells)[i] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        strcpy((*Spells)[i], Spell);
        i++;
    }
    free(Spell);
    return i;
}

int Count(bool *Subornot, int lastindex){
    int count = 0;
    for (int i = 0; i < lastindex; i++) {
        if (Subornot[i] == false) {
            count++;
        }
    }
    return count;
}

int main(void){
    char **SpellBook = NULL;
    int lastindex = getAllSpells(&SpellBook);
    
    // Create a bool array to mark redundant spells.
    bool *Subornot = malloc(sizeof(bool) * lastindex);
    if (Subornot == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    // Initialize Subornot array to false
    for (int k = 0; k < lastindex; k++) {
        Subornot[k] = false;
    }
    
    // Compare each pair only once
    for (int i = 0; i < lastindex; i++) {
        for (int j = i + 1; j < lastindex; j++) {
            // If spells are identical, mark both as redundant
            if (strcmp(SpellBook[i], SpellBook[j]) == 0) {
                Subornot[i] = true;
            } else {
                // If SpellBook[j] is a substring of SpellBook[i], mark j as redundant
                if (!Subornot[j] && strstr(SpellBook[i], SpellBook[j]) != NULL) {
                    Subornot[j] = true;
                }
                // If SpellBook[i] is a substring of SpellBook[j], mark i as redundant
                if (!Subornot[i] && strstr(SpellBook[j], SpellBook[i]) != NULL) {
                    Subornot[i] = true;
                }
            }
        }
    }
    
    int result = Count(Subornot, lastindex);
    printf("%d\n", result);
    
    // Free
    for (int k = 0; k < lastindex; k++) {
        free(SpellBook[k]);
    }
    free(SpellBook);
    free(Subornot);
    
    return 0;
}
