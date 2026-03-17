#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define clear system("cls");
#define pause system("pause");
#define FILENAME "automobile_records.bin"

typedef struct {
    char make[50];
    char model[50];
    int year_built;
    int cost;
} Automobiles;


void Add_Auto(Automobiles** Autos, int array_size, int* count);
void Display_auto(Automobiles** Autos, int array_size, int count);
void SaveToFile(Automobiles** Autos, int array_size, int count);
void LoadFromFile(Automobiles** Autos, int* array_size, int* count);
void main_menu(Automobiles** Autos, int array_size, int* count);

int main() 
{
    int array_size = 0;
    Automobiles** Autos = NULL;
    int count = 0;

    FILE* file = fopen("automobile_records.bin", "rb");

    if (file != NULL) //Checks if there is a save file
    {
        fclose(file);
        LoadFromFile(Autos, &array_size, &count);
    }
    else 
    {
        

        printf("How many automobile records are available: ");
        scanf("%d", &array_size);

        Autos = calloc(array_size, sizeof(Automobiles*));

        if (Autos == NULL) { // Check if the memory allocation failed
            printf("Memory allocation failed.\n");
            return 1;
        }

        main_menu(Autos, array_size, &count); // Pass the array_size as an argument

        free(Autos); // free allocated memory

    }
    return 0;
}



void Add_Auto(Automobiles** Autos, int array_size, int* count)
{
    // Check if the array is already full
    if (*count >= array_size)
    {
        printf("Cannot add more automobiles. Array is full.\n");
        return;
    }

    // Allocate memory for each Automobile struct
    Autos[*count] = malloc(sizeof(Automobiles));
    if (Autos[*count] == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter the make of the automobile %d: ", *count + 1);
    scanf("%s", Autos[*count]->make);

    printf("Enter the model of the automobile %d: ", *count + 1);
    scanf("%s", Autos[*count]->model);

    printf("Enter the year of the build of the automobile %d: ", *count + 1);
    scanf("%d", &Autos[*count]->year_built);

    printf("Enter the cost of the automobile %d: ", *count + 1);
    scanf("%d", &Autos[*count]->cost);

    (*count)++; // Update the count of added automobiles
}


void Display_auto(Automobiles** Autos, int array_size, int count) 
{
    char sub_choice;

    printf("[C]ost low to high\n[M]ake ascending order\n");
    printf("Please enter your choice of display: ");
    scanf(" %c", &sub_choice);

    switch (sub_choice) 
    {
    case 'C':
        // Sort automobiles by cost in ascending order (using bubble sort algorithm)
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (Autos[j]->cost > Autos[j + 1]->cost)
                {
                    // Swap the pointers to rearrange the automobiles
                    Automobiles* temp = Autos[j];
                    Autos[j] = Autos[j + 1];
                    Autos[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("Automobile %d:\n", i + 1);
            printf("Make: %s\n", Autos[i]->make);
            printf("Model: %s\n", Autos[i]->model);
            printf("Year Built: %d\n", Autos[i]->year_built);
            printf("Cost: %d\n", Autos[i]->cost);
            printf("------------------------\n");
        }
        break;
    case 'M':
        // Sort automobiles by make in ascending order (using bubble sort algorithm)
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (strcmp(Autos[j]->model, Autos[j + 1]->model) > 0)
                {
                    // Swap the pointers to rearrange the automobiles
                    Automobiles* temp = Autos[j];
                    Autos[j] = Autos[j + 1];
                    Autos[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("Automobile %d:\n", i + 1);
            printf("Make: %s\n", Autos[i]->make);
            printf("Model: %s\n", Autos[i]->model);
            printf("Year Built: %d\n", Autos[i]->year_built);
            printf("Cost: %d\n", Autos[i]->cost);
            printf("------------------------\n");
        }
        break;
    default:
        printf("Invalid choice of display.\n");
        break;
    }
}
void SaveToFile(Automobiles** Autos, int array_size, int count) {
    FILE* file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(&array_size, sizeof(int), 1, file);

    for (int i = 0; i < count; i++) {
        fwrite(Autos[i], sizeof(Automobiles), 1, file);
    }

    fclose(file);

    printf("Automobile records saved to '%s' successfully.\n", FILENAME);
}

void LoadFromFile(Automobiles** Autos, int* array_size, int* count)
{

    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return;
    }


    fread(count, sizeof(int), 1, file);
    fread(array_size, sizeof(int), 1, file);

    
    printf("%d\n%d", *count, *array_size);
    
    Autos = calloc(*array_size, sizeof(Automobiles*));
  
    if (Autos == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }


    for (int i = 0; i < *count; i++)
    {
        Autos[i] = malloc(sizeof(Automobiles));
        fread(Autos[i], sizeof(Automobiles), 1, file);
    }



    fclose(file);

    printf("Automobile records loaded from '%s' successfully.\n", FILENAME);
    main_menu(Autos, *array_size, &*count); 


}




void main_menu(Automobiles** Autos, int array_size, int* count) 
{
    char choice = 'e';

    do {
        clear;
        printf("======== Main Menu =========\n");
        printf("[A]dd one automobile\n");
        printf("[D]isplay all automobiles\n\t[C]ost low to high\n\t[M]ake ascending order\n");
        printf("[Q]uit\n");
        printf("Please enter your choice: ");
        scanf(" %c", &choice); // Add a space before %c to consume any leftover newline character

        switch (choice)
        {
        case 'A':
            // Add automobile logic
            clear;
            Add_Auto(Autos, array_size, &*count);
            pause;
            break;
        case 'D':
            // Display automobiles logic
            clear;
            Display_auto(Autos, array_size, *count);
            pause;
            break;
        case 'Q':
            SaveToFile(Autos, array_size, *count);
            break;
        default:
            printf("Please enter A, D, or Q.\n");
        }

    } while (choice != 'Q');
}