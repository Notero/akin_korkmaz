// PlayingwithStrings Assignment

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define clear system("cls")
#define pause system("pause");

void stringenter();

int main() 
{	
	//main variables
	int choice = 0;
	

	do // loop until 2 entered to quit
	{


		printf("Please Choose\n1- Continue\n2- Quit\n");

		scanf_s("%d", &choice);

		switch (choice) 
		{
		case 1: // to continue
			clear;

			stringenter();
			pause;
			break;
		case 2: // to quit
			clear;
			printf("Bye...");
			break;
		default: // if anything other than 1 or 2 entered
			clear;
			printf("\nPlease Choose 1 or 2\n");
			break;

		}

	} while (choice != 2);


	return 0;
}

#include <stdio.h>

void stringenter() 
{
	//string variables
	char inputstring[100];
	int length = 0;

	scanf_s(" %[^\n]", &inputstring, sizeof(inputstring)); // gets the string
	printf("You entered:\n\t%s\n", inputstring); // echo

	length = strlen(inputstring); // gets the lenght

	printf("Forward :  %s", inputstring); // prints forwards

	printf("\nBackward :  ");
	for (int i = length - 1; i >= 0; i--) //prints backwards
	{
		printf("%c", inputstring[i]);
	}

	printf("\nVertical :  \n");
	for (int i = 0; i <= length; i++) //prints in a vertical pattern
	{
		printf("\t%c\n", inputstring[i]);
	}
	printf("\nTriangle :  \n");
	
	int row = 1;
	int index = 0;

	while (index < length) //prints in a triangle
	{
		for (int i = 0; i < row; i++) {
			printf("%c", inputstring[index]);
			index++;

			if (index == length)
				break;
		}
		printf("\n");
		row++;
	}

	printf("This many characters in the string : %d\n", length); // prints the length of the string


}


