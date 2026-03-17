// Review Assingment

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main() 
{
	//array
	long iSales[10000];

	//random number
	srand(time(NULL));
	int eSize = rand() % 9501 + 500;

	//Variables for biggest smallest average and sum
	int Big = -6;
	int Small = 999;
	int Average = 0;
	int sum = 0;

	//loop to populate the iSales array
	for (int size = eSize; size >= 0; size--)
	{
		int iSale = rand() % 1005 - 5;

		iSales[size] = iSale;
	}

	//loop to sum all the numbers up decide the biggest and smallest number and print all the values in the array in rows of 10 numbers
	for (int x = 0; x <= eSize - 1; x++)
	{
		if (iSales[x] < Small) {
			Small = iSales[x];
		}

		if (iSales[x] > Big) {
			Big = iSales[x];
		}
		

		if (x % 10 == 0 && x != 0)
		{
			printf("\n");
		}
		sum = iSales[x] + sum;
		printf("%d\t", iSales[x]);

	}

	//calculate average
	Average = sum / eSize;

	//prints the largest smallest and average
	printf("\nThe Largest Value = %d\n", Big);
	printf("The Smallest Value = %d\n", Small);
	printf("The Average of Values = %d", Average);

	return 0;
}