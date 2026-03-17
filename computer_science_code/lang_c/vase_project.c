#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AUTOS 100

typedef struct Automobiles {
    char brand[20];
    char model[20];
    int year;
    double price;
} AUTO;

void addauto(AUTO* pautospecs);
void saveData(const AUTO* pautospecs, int numAutos);
void loadData(AUTO* pautospecs, int* numAutos);

int main()
{
    int Choice;
    int numAutos = 0;

    AUTO autospecs[MAX_AUTOS];

    do {
        printf("============================\n");
        printf("Valencia Auto Sales Enterprice (VASE)\n");
        printf("============================\n");

        printf("1 - Add auto\n");
        printf("2 - Delete auto\n");
        printf("3 - Display autos\n");
        printf("4 - Quit menu\n");

        printf("Please enter your choice: ");
        scanf("%d", &Choice);

        switch (Choice) {
        case 1:
            addauto(&autospecs[numAutos]);
            numAutos++;
            saveData(autospecs, numAutos);
            break;
        case 2:
            break;
        case 3:
            loadData(autospecs, &numAutos);
            for (int i = 0; i < numAutos; i++) {
                printf("Brand: %s\n", autospecs[i].brand);
                printf("Model: %s\n", autospecs[i].model);
                printf("Year: %d\n", autospecs[i].year);
                printf("Price: %.2lf\n", autospecs[i].price);
                printf("\n");
            }
            break;
        case 4:
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    } while (Choice != 4);

    return 0;
}

void addauto(AUTO* pautospecs) {
    printf("Enter the brand: ");
    scanf("%s", pautospecs->brand);

    printf("Enter the model: ");
    scanf("%s", pautospecs->model);

    printf("Enter the year: ");
    scanf("%d", &(pautospecs->year));

    printf("Enter the price: ");
    scanf("%lf", &(pautospecs->price));
}

void saveData(const AUTO* pautospecs, int numAutos) {
    FILE* file = fopen("autos.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(pautospecs, sizeof(AUTO), numAutos, file);

    fclose(file);
}

void loadData(AUTO* pautospecs, int* numAutos) {
    FILE* file = fopen("autos.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    *numAutos = fileSize / sizeof(AUTO);
    fseek(file, 0, SEEK_SET);

    fread(pautospecs, sizeof(AUTO), *numAutos, file);

    fclose(file);
}
