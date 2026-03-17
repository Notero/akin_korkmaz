
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct {
	char itemName[100]; // Name of an item in Inventory
	float itemCost; // Cost of the item
	float itemPrice; // Price of the item
	int quantity; // Quantity of available items in Inventory
}Inventory;


void AddItem(Inventory** inventory, int size);
void DisplayAll(Inventory** inventory, int size);
void Stats(Inventory** inventory, int size);


int main()
{
    int size;//To be determined size of the array by the user

    printf("Enter the size of the inventory: ");
    scanf("%d", &size); // gets the size of the array

    // Creates a pointer array called inventory and Allocates memory for the inventory array
    Inventory** inventory = malloc(size * sizeof(Inventory*));

    if (inventory == NULL) //checks if the memory allocation failed
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    AddItem(inventory, size); // Takes all the information from the user about the inventories contents
    DisplayAll(inventory, size); // Displays all of the information stored in the array
    Stats(inventory, size); // Puts the inventory stats (TotalQuantity)(Name of the most expensive item)(Estimated total profit)

    // Clean up memory
    for (int i = 0; i < size; i++) {
        free(inventory[i]);
    }
    free(inventory);

    return 0;
}



void DisplayAll(Inventory** inventory, int size) //Prints out the whole array from the memory
{
    printf("Inventory:\n");
    for (int i = 0; i < size; i++) {
        printf("Item %d:\n", i + 1);
        printf("Name: %s\n", inventory[i]->itemName);
        printf("Cost: %.2f\n", inventory[i]->itemCost);
        printf("Price: %.2f\n", inventory[i]->itemPrice);
        printf("Quantity: %d\n", inventory[i]->quantity);
        printf("\n");
    }
}

void Stats(Inventory** inventory, int size) 
{
    int totalquantity = 0;
    int mostexpensive = 0;
    int place = 0;
    int TotalProfit = 0;

    for (int i = 0; i < size; i++) // Calculates the total number of items within the inventory
    {
        totalquantity += inventory[i]->quantity;
    }
    printf("Number of Items in the inventory: %d\n", totalquantity); // Prints the total number  of items in the inventory

    for (int i = 0; i < size; i++)// Finds the place of the most expensive item
    {
        if (inventory[i]->itemPrice > mostexpensive)
        {
            place = i;
        }
    }

    printf("%s\n", inventory[place]->itemName); // uses the place of the highest price to acces the struct from the memory and printing its name

    for (int i = 0; i < size; i++)// Calculates the total profit of the whole inventory if everything were sold
    {
        TotalProfit += inventory[i]->itemPrice * inventory[i]->quantity;
    }


    printf("Estimated Total Profit is : %d\n", TotalProfit); // prints the estimated total profit
}