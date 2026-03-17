                  /*Assignment 4*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Programmed by Akin Korkmaz
// 10 March 2023

// Step 1: Collect the Weight and Miles
// Step 2: Convert miles into rate
// Step 3: Check if package is 50 or more
// Step 4: Create 4 diffrent outcomes for price to be calculated
// Step 5: Print the price on screen

int main() {

    //Variables
    float fMiles;
    float fWeight;
    float fMilerate;
    int iroundedMilerate;
    int iprice;

    //Collecting Weight and Miles
    printf("\nPlease enter the weight of the package.(in Pounds): ");
    scanf_s("%f", &fWeight);
    printf("\nPlease enter how far are you going to send the package (in Miles): ");
    scanf_s("%f", &fMiles);
    //Calculating rate
    fMilerate = fMiles / 500;
    iroundedMilerate = ceil(fMilerate);
    //Weight Check
    if (fWeight >= 50)
    {
        printf("\nYour package weighs %.1f. It should be less than 50 to be shipped\n", fWeight);
    }
    else {
        if (fMiles <= 1000 && fWeight <= 10)
        {
            iprice = 3 * iroundedMilerate;
            printf("\nYour shipping charge is %d\n", iprice);
        }
        else {
            if (fMiles >= 1000 && fWeight <= 10)
            {
                iprice = 3 * iroundedMilerate + 10;
                printf("\nYour shipping charge is %d\n", iprice);
            }
            else {
                if (fMiles <= 1000 && fWeight >= 10)
                {
                    iprice = 5 * iroundedMilerate;
                    printf("\nYour shipping charge is %d\n", iprice);
                }
                else {
                    if (fMiles >= 1000 && fWeight >= 10)
                    {
                        iprice = 5 * iroundedMilerate + 10;
                        printf("\nYour shipping charge is %d\n", iprice);
                    }
                }//if end
            }//if end
        }//if end
    }//if end
    system("pause");
    return 0;
}