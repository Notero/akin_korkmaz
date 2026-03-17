// 2D Array Assignment


#include<stdio.h>
#include<stdlib.h>
#define clear system("cls")
#define pause system("pause");

//function declerations
void entergrades(int Gradegrid[1000][5], int irow);
void displaygrid(int Gradegrid[1000][5], int irow);
void examaverage(int Gradegrid[1000][5], int irow);
void studentaverage(int Gradegrid[1000][5], int irow);

int main()
{
	//main variables
	int Choice = 0;
	int icol = 0;
	int irow = 0;
	int Gradegrid[1000][5] = { 0 , 0 };

	do //loop until option 5 choosen
	{
		//menu print
		printf("********** Main Menu **********\n");
		printf("1. Add grades for next student.\n");
		printf("2. Display all grades.\n");
		printf("3. Show average by Exam.\n");
		printf("4. Show average by Student.\n");
		printf("5. Quit the program.\n");

		printf("\nEnter Selection:  ");

		scanf_s("%d", &Choice);//choce input
	

		switch (Choice) //switch for menu navigation
		{
		case 1: // gets the grades
			clear;
			printf("Please Enter the four exam scores for the %d. student:\n", irow + 1);
			

			entergrades(Gradegrid, irow); //registers the grades onto the 1000 by 5 grid

			for (int i = 1; i <= 4; i++)// makes sure that all grades are between 100 and 0
			{
				printf("student didnt register");
				if (Gradegrid[irow][i] > 100) {
					irow--;
					pause;
				}
			}

			irow++;
			clear;
			break;
		case 2: // displays all the grades
			clear;

			printf("2. Display all grades:\n");
			displaygrid(Gradegrid, irow);

			pause;
			clear;
			break;
		case 3: // displayes the exam averages
			clear;

			printf("1. Exam\t2.Exam\t3.Exam\t4.Exam\n");
			examaverage(Gradegrid, irow);

			pause;
			clear;
			break;
		case 4: // displayes the student averages
			clear;
			printf("VID:\tAverage:\n");
			studentaverage(Gradegrid, irow);

			pause;
			clear;

			break;
		case 5: // exits
			clear;
			printf("Thanks and bye.\n");
			pause;
			break;
		default: // invalid choice
			clear;
			printf("\nInvalid Choice!\n");
			pause;
			break;
		}
	} while (Choice != 5);

	return 0;
}

void entergrades(int Gradegrid[1000][5], int irow)
{
	int grade = 0;

	printf("if you enter any number other than those numbers between 100 - 0 student wont register to the grid");

	for (int i = 1; i <= 4; i++) //register the grades to every coulm of a row
	{
		scanf_s("%d", &grade);
		Gradegrid[irow][i] = grade;
	}
	

}
void displaygrid(int Gradegrid[1000][5], int irow) 
{
	//prints out all of the grid
	for (int x = 0; x < irow; x++) {
		for (int y = 1; y <= 4; y++) {
			printf("%d\t", Gradegrid[x][y]);
		}
		printf("\n");
	}
}

void examaverage(int Gradegrid[1000][5], int irow)
{
	//variables for examaverage
	int examaverage[5] = { 0 };
	int examsums[5] = { 0 };

	//calculation of the exam averages
	for (int y = 1; y <= 4; y++) {
		for (int x = 0; x < irow; x++){
			examsums[y] = examsums[y] + Gradegrid[x][y];
		
		}
		examaverage[y] = examsums[y] / irow;
		
	}
	//display of the exam averages
	for (int z = 1; z <= 4; z++) 
	{
		printf(" %d\t", examaverage[z]);
	}
	printf("\n");
}

void studentaverage(int Gradegrid[1000][5], int irow)
{
	//variables for studentaverage
	int rowsum[1000] = { 0 };
	int rowaverage[1000] = { 0 };

	//calculates student averages
	for (int x = 0; x < irow; x++) {
		for (int y = 1; y <= 4; y++) {
			rowsum[x] = Gradegrid[x][y] + rowsum[x];
		}
		rowaverage[x] = rowsum[x] / 4;
	}
	//displayes the student averages
	for (int z = 0; z < irow; z++) {
		printf("%d\t%d%\n", z, rowaverage[z]);
	}

}