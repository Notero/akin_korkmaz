    /*Assignment 3*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

// 1- take 4 inputs as grade 1,2,3,4.
// 2- calculate average grades
// 3- outputs the outcome of the average grades and Letter Grade

int main(void) 
{
//Variables
float fGrade1 = 0;
float fGrade2 = 0;
float fGrade3 = 0;
float fGrade4 = 0;
float fAverage = 0;
    //Intro
    printf("\n\t Grade Calculator\n");
    printf("\nPlease enter the four grades needed");
    //Collection
    printf("\n 1: ");
    scanf_s("%f", &fGrade1);
    printf(" 2: ");       
    scanf_s("%f", &fGrade2);
    printf(" 3: ");
    scanf_s("%f", &fGrade3);
    printf(" 4: ");
    scanf_s("%f", &fGrade4);
    //DefineVariables
    fAverage = (fGrade1 + fGrade2 + fGrade3 + fGrade4) / 4;
    //Output
    printf("Your Average is %.2f\n", fAverage);
    
    if (fAverage >= 0 && fAverage <= 59)//F Condition
    {
        printf("\n\tLetterGrade : F\n");
    }
    else
    {
        if (fAverage > 59 && fAverage <= 69)//D condition
        {
            printf("\n\tLetterGrade : D\n");
        }
        else
        {
            if (fAverage > 69 && fAverage <= 79)//C Condition
            {
                printf("\n\tLetterGrade : C\n");
            }
            else
            {
                if (fAverage > 79 && fAverage <= 89)//B Condition
                {
                    printf("\n\tLetterGrade : B\n");
                }
                else
                {
                    if (fAverage > 89 && fAverage <= 100)//A Condition
                    {
                        printf("\n\tLetterGrade : A\n");
                    }
                }//if end
            }//if end
        }//if end
    }//if end


        system("pause");
    return 0;
}