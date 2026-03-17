 /* Assignment 7 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>


int main()
{
	//Variables

	double dValue = 0.1;
	double dlowest = 9999 ;
	double dhighest = 0;
	int icount = 0;
	double daverage = 0;
	double dtotal = 0;

	printf("Please enter the values that are GREATER THAN 0\nIf you want to calculate (Total, Average, Amount entered, Highest value and Lowest value) \nEnter a value lower than or equal to 0\n");
	
	while (icount >= 0)
	{
		icount++;
		printf("%d - ", icount);
		scanf_s("%lf", &dValue);

		if (dValue > 0)
		{
			dtotal = dValue + dtotal; // calculates total

			if (dValue <= dlowest && dValue >= 0) //checks for lowest
			{
				dlowest = dValue;
			}

			if (dValue >= dhighest) //checks for highest
			{
				dhighest = dValue;
			}
		}else if (dValue <= 0) //stops loop when 0 entered
		{
			printf("\n\n\t Calculations:");
			break;
		}
	}

	icount--;

	daverage = dtotal / (double)icount; //calculates average

	
	printf("\nSummation is : %lf\n", dtotal);
	printf("Average is : %lf\n", daverage);
	printf("Amount of numbers entered : %d\n", icount);
	printf("Highest number is : %lf\n", dhighest);
	printf("Lowest number is : %lf\n", dlowest);

	system("pause");
	return 0;
}