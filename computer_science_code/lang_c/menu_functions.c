//Menu Function Array.
//Programmed by Akin Korkmaz.
//5/16/2023.

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

float getdeposit();
float sumalldeposits(float deposits[],int icount);
void bubbleSort(float deposits[], int icount);
float depositsaverage(float deposits[], int icount);
float lowestdeposit(float deposits[], int icount);



int main()
{
    //variables to display the returned values, from the functions.
    int icount = 0;
    float deposits[10000] = {0.0};
    char choice;
    float ftotal;
    float fAverage;
    float fLowest;
    
    do // loop ends when Q entered.
    {

        //menu print.
        printf("********************* Banking Menu *********************\n");
        printf("[G]et a new deposit\n");
        printf("[S]um of all deposits\n");
        printf("[D]eposits will be displayed from highest to lowest\n");
        printf("[A]verage of all deposits\n");
        printf("[L]owest deposit will be displayed\n");
        printf("[Q]uit\n");
        printf("********************************************************\n");

        printf("Please enter your choice\n"); // takes the menu choice input.
        scanf(" %c", &choice);
        getchar();

        switch (choice) // switch statement for menu navigation.
        {
        case 'G': // case G to make a new deposit.

            system("cls");

            deposits[icount] = getdeposit(); // getdeposit function gets the deposit amount and sets it equal to deposits[icount]th element of the deposits array.

            icount++; // keeps track of the size of the array.

            system("cls");
            break;


        case 'S': // sum of all deposits

            system("cls");

            ftotal = sumalldeposits(deposits, icount); // uses the deposits array and icount(size) and calculates the total of all the elements in the array.

            printf("Sum of all deposits is %f\n", ftotal); //prints the results.
            
            
            system("cls");
            break;


        case 'D': // sorts higest to lowest and displayes

            system("cls");

            printf("Deposits displayed from highest to lowest:\n");

            bubbleSort(deposits, icount); //sorts the deposits array with the deposits array and icount(size).

            for (int i = 0; i < icount; i++) //prints the sorted array from highest to lowest.
            {
                printf("%f\n", deposits[i]);
            }

            system("pause");
            system("cls");

            break;


        case 'A': // calculates and displayes average

            system("cls");

            printf("Average of all deposits\n");

            fAverage = depositsaverage(deposits, icount); // calculates the average of all the elements in the deposits array and sets it equal to fAverage.

            printf("%f\n", fAverage); //prints the average.

            system("pause");
            system("cls");

            break;


        case 'L': //decides and prints the lowest value of the array

            system("cls");

            fLowest = lowestdeposit(deposits, icount); // decides which of the elements of the array is the lowest and sets it equal to fLowest.

            printf("Lowest deposit is %f\n", fLowest); //prints the lowest value of the array.

            system("pause");
            system("cls");
            
            break;


        case 'Q':// quits

            system("cls");
            printf("Exiting the program. Goodbye!\n"); // exit goodbye.
            system("pause");
            break;


        default: //if anything other than given options is entered.
            system("cls");

            printf("Invalid choice. Please try again.\n"); 

            system("pause");
            system("cls");
            break;


        }
    } while (choice != 'Q');

    return 0;
}

void bubbleSort(float deposits[], int icount)
{
    for (int i = 0; i < icount - 1; i++)
    {
        for (int j = 0; j < icount - i - 1; j++)
        {
            if (deposits[j] < deposits[j + 1])
            {
                // Swap elements if they are in the wrong order to sort.
                float temp = deposits[j];
                deposits[j] = deposits[j + 1];
                deposits[j + 1] = temp;
            }
        }
    }
}


float depositsaverage(float deposits[], int icount) // calculates average.
{
    float average = 0;
    float total = 0;

    total = sumalldeposits(deposits, icount); // uses sumalldeposits function to get the total of all the elements of the array.

    average = total / icount; // calculates the average.

    return average;// returns average
}


float getdeposit() // takes a deposit from the user.
{
    float depositamount = 0.0;

    printf("Please enter amount to deposit\n");

    scanf("%f", &depositamount); // gets the deposit amount


    return depositamount; // returns the deposit amount.

}


float lowestdeposit(float deposits[], int icount) //finds the lowest value and returns it to the main function.
{
    float lowest = 1000000000;

    for (int i = 0; i < icount - 1; i++) //loop to check the lowest.
    {
        if (lowest > deposits[i]) {
            lowest = deposits[i];
        }

    }


    return lowest; // returns lowest.
}


float sumalldeposits(float deposits[], int icount)// calculate the total.
{
    float total = 0;

    for (int i = 0; i < icount; i++) // loop to add all the elements in the array.
    {
        total = total + deposits[i];

    }
    return total; // returns total
}


