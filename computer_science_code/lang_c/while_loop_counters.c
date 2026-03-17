/*Assingnment 5*/

#include <stdio.h>
#include <math.h>

int main()
{

	//Variables
	float fGrade = 0;
	int iEnteredGrades = 0;
	int iPassinggrades = 0;
	int ipercentagepassing = 0;

	while (fGrade != -1) // loop for entering grades decides if grade entered equal to -1 or not
	{
		printf("Please enter a grade:\t");
		scanf_s("%f", &fGrade);

		if (fGrade > 100 || fGrade < -1) // Decides if its valid grade
		{
			printf("\t Not a valid Grade!\n");
		}
		else if (fGrade >= 70) // decides if passing
		{
			iPassinggrades++;
			iEnteredGrades++;
		}
		else if (fGrade < 70 && fGrade >= 0 ) // decides if not passing
		{
			iEnteredGrades++;
		}
	}
	// Calculation and Print
	ipercentagepassing = (iPassinggrades * 100) / iEnteredGrades;
	printf("You have entered %d passing Grades\n%d Percentage of the grades entered between 100 - 0 is passing\n", iPassinggrades, ipercentagepassing);

	system("pause");
	return 0;
}