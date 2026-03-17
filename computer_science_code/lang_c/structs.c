#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pause system("pause")
#define clear system("cls")

struct Automobiles {
    char brand[20];
    char model[20];
    int year;
    double price;
    int ID;
};

void addauto();
void deleteauto();
void displayautolist();

int main()
{
    int Choice;
    
    do {
        printf("============================\n");
        printf("Valencia Auto Sales Enterprice (VASE)\n");
        printf("============================\n");
        printf("1 - Add auto\n");
        printf("2 - Delete auto\n");
        printf("3 - Display autos\n");
        printf("4 - Quit menu\n");

        printf("Please enter your choice: ");
        scanf_s("%d", &Choice);

        switch (Choice) {
        case 1:
            clear;
            addauto();
            pause;
            clear;
            break;
        case 2:
            deleteauto();
            pause;
            clear;
            break;
        case 3:
            clear;
            displayautolist();
            pause;
            clear;
            break;
        case 4:
            clear;
            printf("\nAll the data have been saved for Future Use Thanks For using\n");
            pause;
            clear;
            break;
        default:
            clear;
            printf("Invalid Choice\n");
            pause;
            clear;
            break;
        }
    } while (Choice != 4);

    return 0;
}

void addauto() {
    struct Automobiles addauto;

    

    printf("Enter Brand: ");
    scanf_s("%19s", addauto.brand, (unsigned int)sizeof(addauto.brand));
   
    printf("Enter Model: ");
    scanf_s("%19s", addauto.model, (unsigned int)sizeof(addauto.model));
 
    printf("Enter Year of Production: ");
    scanf_s("%d", &addauto.year);

    printf("Enter Price: ");
    scanf_s("%lf", &addauto.price);

    printf("Enter Auto_ID: ");
    scanf_s("%d", &addauto.ID);



    // Open the file in append mode (create if it doesn't exist)
    FILE* file = fopen("autos.txt", "a");
    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    // Write the data to the file
    
    fprintf(file, "Brand: %s\n", addauto.brand);
    fprintf(file, "Model: %s\n", addauto.model);
    fprintf(file, "Year: %d\n", addauto.year);
    fprintf(file, "Price: %.2f\n", addauto.price);
    fprintf(file, "Auto ID: %d\n\n", addauto.ID);
   

    // Close the file
    fclose(file);
    printf("Data saved successfully.\n");
   
}

void deleteauto() {
    int idToDelete;
    printf("Enter the Auto ID to delete: ");
    scanf("%d", &idToDelete);

    FILE* inputFile = fopen("autos.txt", "r");
    FILE* outputFile = fopen("temp.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open files for reading/writing.\n");
        return;
    }

    struct Automobiles autoData = { "", "", 0, 0.0, 0 };  // Initialize with default values
    int found = 0;

    // Read the input file line by line and copy the contents to the output file, excluding the entry to delete
    while (fscanf(inputFile, "Brand: %s\n", autoData.brand) != EOF) {
        fscanf(inputFile, "Model: %s\n", autoData.model);
        fscanf(inputFile, "Year: %d\n", &autoData.year);
        fscanf(inputFile, "Price: %lf\n", &autoData.price);
        fscanf(inputFile, "Auto ID: %d\n\n", &autoData.ID);


        // Check if the Auto ID matches the one to delete
        if (autoData.ID != idToDelete) {
            // Write the entry to the output file
            fprintf(outputFile, "Brand: %s\n", autoData.brand);
            fprintf(outputFile, "Model: %s\n", autoData.model);
            fprintf(outputFile, "Year: %d\n", autoData.year);
            fprintf(outputFile, "Price: %.2f\n", autoData.price);
            fprintf(outputFile, "Auto ID: %d\n\n", autoData.ID);
        }
        else {
            found = 1;  // Mark that the entry was found and deleted
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    if (found) {
        // Replace the original file with the modified file
        remove("autos.txt");
        rename("temp.txt", "autos.txt");
        printf("Auto with ID %d deleted successfully.\n", idToDelete);
    }
    else {
        remove("temp.txt");  // Delete the temporary file
        printf("Auto with ID %d not found.\n", idToDelete);
    }
}

void displayautolist() 
{
    FILE* poi = fopen("autos.txt", "r");

    if (poi == NULL) {
        printf("Failed to open files for reading/writing.\n");
        return;
    }
    struct Automobiles autoData = { "", "", 0, 0.0, 0 };  // Initialize with default values

    while (fscanf(poi, "Brand: %s\n", autoData.brand) != EOF) {
        fscanf(poi, "Brand: %s\n", &autoData.brand);
        printf("\n%s\n", autoData.brand);
        fscanf(poi, "Model: %s\n", &autoData.model);
        printf("%s\n", autoData.model);
        fscanf(poi, "Year: %d\n", &autoData.year);
        printf("%d\n", autoData.year);
        fscanf(poi, "Price: %lf\n", &autoData.price);
        printf("%lf\n", autoData.price);
        fscanf(poi, "Auto ID: %d\n\n", &autoData.ID);
        printf("%d\n", autoData.ID);
    }
}