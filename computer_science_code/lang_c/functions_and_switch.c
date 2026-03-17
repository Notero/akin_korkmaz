
/*assisnment 09*/

/*
Celsius to Fahrenheit Formula: (°C * 1.8) + 32 = °F

Fahrenheit to Celsius Formula: (°F - 32) / 1.8 = °C
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float CelciustoFahrenheit();//Function Decleration
float FahrenheittoCelcius();//Function Decleration

int main() 
{
	int iMenuChoice = 0;
	printf("\n Hello, please choose one of the options to convert.");
	//Menu Print
	printf("\n\t 1 - Convert, Celsius to Fahrenheit.");
	printf("\n\t 2 - Convert, Fahrenheit to Celsius.");
	printf("\n\t 3 - Exit.\n Enter :");

	scanf("%d", &iMenuChoice);

	switch (iMenuChoice) // Switch for Menu Choice
	{
	case 1:
		CelciustoFahrenheit(); //Calls Function 1 for Celcius to Fahrenheit Conversion
		break;
	case 2:
		FahrenheittoCelcius(); //Calls Function 2 for Fahrenheit to Celcius Conversion
		break;
	case 3:
		//exit
		break;
	}
	system("pause");
	return 0;
}

float CelciustoFahrenheit()
{
	// Variables
	float fCelciusValue = 0;
	float fFahrenheitValue = 0;
	//Collection
	printf("\nPlease Enter the Celcius Value:\n");
	scanf("%f", &fCelciusValue);
	//Calculation
	fFahrenheitValue = fCelciusValue * 1.8;
	fFahrenheitValue = fFahrenheitValue + 32;
	//Results Print
	printf("%.2f Celcius = %.2f Fahrenheit\n", fCelciusValue,fFahrenheitValue);

	return 0;
}

float FahrenheittoCelcius()
{
	//Variable	
	float fFahrenheitValue = 0;
	float fCelciusValue = 0;
	//Collection
	printf("\nPlease Enter the Fahrenheit Value:\n");
	scanf("%f", &fFahrenheitValue);
	//Calculation
	fCelciusValue = fFahrenheitValue - 32;
	fCelciusValue = fCelciusValue / 1.8;
	//Results Print
	printf("%.2f Fahrenheit = %.2f Celcius\n", fFahrenheitValue,fCelciusValue);

	return 0;
}
