  /* Assignment 2*/
#include<stdio.h>


int main()
{
//Variables
int intFirstinteger = 0;
int intSecondinteger = 0;
int intAddition = 0;
int intMultiplication = 0;
int intIntegerONEsquare = 0;
int intIntegerTWOsquare = 0;
int intDivision = 0;
     // Introduce
	 printf("\n\t This is Very Basic Calculator. Enter your integers in the right order to get the correct division at the end\n\t This Calculator can only take integer inputs and give integer outputs\n ");
     //Collecting
	 printf("\nPlease enter the first integer: ");
	 scanf_s("%d", &intFirstinteger);
	 printf("\nPlease enter the second integer: ");
	 scanf_s("%d", &intSecondinteger);
	 //Variables Defined
	 intAddition = intFirstinteger + intSecondinteger;
	 intMultiplication = intFirstinteger * intSecondinteger;
	 intIntegerONEsquare = intFirstinteger * intFirstinteger;
	 intIntegerTWOsquare = intSecondinteger * intSecondinteger;
	 intDivision = intFirstinteger / intSecondinteger;
//Results
	 printf("\n\tAddition of these two integers is: %d", intAddition);
	 printf("\n\tMultiplication of these two integers is: %d", intMultiplication);
	 printf("\n\tSquare of the first integer is: %d", intIntegerONEsquare);
	 printf("\n\tSquare of the second integer is: %d", intIntegerTWOsquare);
	 printf("\n\tDivision of these integers is: %d\n", intDivision);

	 system("pause");
    return 0;
}