#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//for pause and clear
#define pause system("pause")
#define clear system("cls")


//Programmed by Akin Korkmaz
//15/06/2023

int main();

//Function Declaration
//-------------------------------ETC.-----------------------------------------------------------
void PutCords(int row);
void ShipStatus(char SunkShips[5], int row, int column);
//-------------------------------Ship Placement------------------------------------------------
int Victory(int iBoard[10][10]);
int Western(int iBoard[10][10]);
int Yellow(int iBoard[10][10]);
int Xray(int iBoard[10][10]);
int Zebra(int iBoard[10][10]);
//-------------------------------Game Simulation------------------------------------------------
void ShipSunk(int iBoard[10][10], char cDummyBoard[10][10], char SunkShips[5]);
int missilesim(int iBoard[10][10], char cDummyBoard[10][10], int count, char SunkShips[5]);
//-------------------------------Save and Load--------------------------------------------------
void SaveGame(int iBoard[10][10], char cDummyBoard[10][10], int count, char SunkShips[5]);
int LoadGame(int iBoard[10][10], char cDummyBoard[10][10], int* count, char SunkShips[5]);
//-------------------------------Game Core------------------------------------------------------
void GameCore(int load);



int main() 
{
    //Basic Variables to save and for menu
    int load = 0;
	int choice = 0;
    FILE* file = fopen("Save.txt", "r");

    if (file != NULL) //Checks if there is a save file
    {
        load = 1;
        fclose(file);
    }
    else {
        load = 0;
    }

    //Prints the menu
    printf("=============== Battle Ships ====================\n");
    printf("                           \\ \\        / /      ||\n");
    printf("                            \\ \\_    _/ /       ||\n");
    printf("                             \\| \\__/ |/        ||\n");
    printf("|| 1 - New Game  ||           |      |         ||\n");
    if (load) //printf's load game if there is a save
    {
        printf("|| 2 - Load Game ||          /        \\        ||\n");
    }
    else {
        printf("||               ||          /        \\        ||\n");
    }
    printf("|| 3 - Quit      ||         |  Battle  |       ||\n");
    printf("                             \\ Ships  /        ||\n");
    printf("                              \\      /         ||\n");
    printf("                               \\____/          ||\n");
    printf("=================================================\n");
    printf("Choice => ");
    //Scans the choice from keyboard
    scanf("%d", &choice);

    
		switch (choice) // Switch statement for menu
		{
		case 1:
			GameCore(load); // Starts a new game (Fresh save if closed by entering QQ)
            break;
		case 2:
            GameCore(load); // Loads the last game if it exists
            break;
        case 3:
            clear; // Quit
            printf("Bye....");
            break;
        }
        return 0;
}
void PutCords(int row) // Puts char cords in every lines begining
{
    switch (row) 
    {
            case 0:
                printf("A\t");
                break;
            case 1:
                printf("B\t");
                break;
            case 2:
                printf("C\t");
                break;
            case 3:
                printf("D\t");
                break;
            case 4:
                printf("E\t");
                break;
            case 5:
                printf("F\t");
                break;
            case 6:
                printf("G\t");
                break;
            case 7:
                printf("H\t");
                break;
            case 8:
                printf("I\t");
                break;
            case 9:
                printf("J\t");
                break;

            }
}
void ShipStatus(char SunkShips[5], int row, int column) // prints the status of ships
{
    if (column == 9 && row == 0) 
    {
        printf("-----------------------------"); //prints the upper status page boundry in the first row of the board print
    }
    if (SunkShips[0] == 'V' && column == 9 && row == 1) // checks if the ship Victory has sunk or floating and changes prints on the status menu
    {
        printf("Ship Victory ----- Down!");
    }
    else if (SunkShips[0] != 'V' && column == 9 && row == 1)
    {
        printf("Ship Victory ----- Floating");
    }
    if (SunkShips[1] == 'W' && column == 9 && row == 2) // checks if the ship Western has sunk or floating and changes prints on the status menu
    {
        printf("Ship Western ----- Down!");
    }
    else if (SunkShips[0] != 'W' && column == 9 && row == 2)
    {
        printf("Ship Western ----- Floating");
    }
    if (SunkShips[2] == 'Y' && column == 9 && row == 3) // checks if the ship Yellow has sunk or floating and changes prints on the status menu
    {
        printf("Ship Yellow ----- Down!");
    }
    else if (SunkShips[0] != 'Y' && column == 9 && row == 3)
    {
        printf("Ship Yellow ----- Floating");
    }
    if (SunkShips[3] == 'X' && column == 9 && row == 4)// checks if the ship Xray has sunk or floating and changes prints on the status menu
    {
        printf("Ship Xray ----- Down!");
    }
    else if (SunkShips[0] != 'X' && column == 9 && row == 4)
    {
        printf("Ship Xray ----- Floating");
    }
    if (SunkShips[4] == 'Z' && column == 9 && row == 5) // checks if the ship Zebra has sunk or floating and changes prints on the status menu
    {
        printf("Ship Zebra ----- Down!");
    }
    else if (SunkShips[0] != 'Z' && column == 9 && row == 5)
    {
        printf("Ship Zebra ----- Floating");
    }
    if (column == 9 && row == 6)
    {
        printf("-----------------------------"); //prints the bottom status page boundry in the first row of the board print
    }
}
int Victory(int iBoard[10][10])
{

    srand((unsigned int)time(NULL)); // So the numbers are always different from one another

    //Variables for boat placement on the board
    int Row;
    int Column;
    int Allignment;

    do //Loop to place the ship on the board correctly
    {
        Row = rand() % 10; // Creates a random number for the y cordinate of the point to start to place the Victory Ship 
        Column = rand() % 10; // Creates a random number for the x cordinate of the point to start to place the Victory Ship
        Allignment = rand() % 4 + 1; // Creates a random number for decision purpouses for which direction the Ship will be placed towards

        switch (Allignment) // Switch to check if the boat is possible to be placed towards that direction and if so places the Ship towards
        {                   // That allignment, if Allignment generates the random number 1 its up 2 is down 3 is left and 4 is right.
        case 1: // up
            if (Row >= 4) 
            {
                int valid = 1;
                for (int x = 0; x < 5; x++) // Loop to scan and check if its possible to place the Ship in the desired direction
                {
                    if (iBoard[Row - x][Column] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) // Checks if possible and if possible places the Ship
                {
                    for (int x = 0; x < 5; x++) //Loop to place the boat upwards
                    {
                        iBoard[Row - x][Column] = 1;
                    }
                    return 1;  // Ship successfully placed
                }
            }
            break;
        case 2: // Places and checks toward the desired direction same as case 1 (Downwards)
            if (Row <= 5) {
                int valid = 1;
                for (int x = 0; x < 5; x++) {
                    if (iBoard[Row + x][Column] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 5; x++) {
                        iBoard[Row + x][Column] = 1;
                    }
                    return 1;
                }
            }
            break;
        case 3: // Places and checks toward the desired direction same as case 1 (Left)
            if (Column >= 4) {
                int valid = 1;
                for (int x = 0; x < 5; x++) {
                    if (iBoard[Row][Column - x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 5; x++) {
                        iBoard[Row][Column - x] = 1;
                    }
                    return 1;
                }
            }
            break;
        case 4: // Places and checks toward the desired direction same as case 1 (Right)
            if (Column <= 5) {
                int valid = 1;
                for (int x = 0; x < 5; x++) {
                    if (iBoard[Row][Column + x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 5; x++) {
                        iBoard[Row][Column + x] = 1;
                    }
                    return 1;
                }
            }
            break;
        }
    } while (1);

    return 0;  // Pattern not placed
}
int Western(int iBoard[10][10]) // Similar code with Ship Victory but the boat lenght is 4 and the function is adjusted accordingly
{

    srand((unsigned int)time(NULL)); //For better number generation

    //Variables
    int Row;
    int Column;
    int Allignment;

    do {
        //Generates a random location
        Row = rand() % 10;
        Column = rand() % 10;
        Allignment = rand() % 4 + 1;

        switch (Allignment) //Checks and if possible to place places in the random decided direction
        {
        case 1: // up
            if (Row >= 3) {
                int valid = 1;
                for (int x = 0; x < 4; x++) //Checks if there is a Ship
                {
                    if (iBoard[Row - x][Column] != 0) 
                    {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 4; x++) //Places the Ship
                    {
                        iBoard[Row - x][Column] = 2;
                    }
                    return 1;  
                }
            }
            break;
        case 2: // down
            if (Row <= 6) {
                int valid = 1;
                for (int x = 0; x < 4; x++) //Checks if there is a Ship
                {
                    if (iBoard[Row + x][Column] != 0) 
                    {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 4; x++) //Places the Ship
                    {
                        iBoard[Row + x][Column] = 2;
                    }
                    return 1;  
                }
            }
            break;
        case 3: // left
            if (Column >= 3) {
                int valid = 1;
                for (int x = 0; x < 4; x++) //Checks if there is a Ship
                {
                    if (iBoard[Row][Column - x] != 0)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 4; x++) //Places the Ship
                    {
                        iBoard[Row][Column - x] = 2;
                    }
                    return 1;  
                }
            }
            break;
        case 4: // right
            if (Column <= 6) {
                int valid = 1;
                for (int x = 0; x < 4; x++) //Checks if there is a Ship
                {
                    if (iBoard[Row][Column + x] != 0) 
                    {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 4; x++) //Places the Ship
                    {
                        iBoard[Row][Column + x] = 2;
                    }
                    return 1;  
                }
            }
            break;
        }
    } while (1);


    return 0;
}
int Yellow(int iBoard[10][10]) 
{

    srand((unsigned int)time(NULL)); // Better number generation
    //Variables for placement of the Ship
    int Row;
    int Column;
    int Allignment;

        do {
            //Random generated location for the Ship
            Row = rand() % 10;
            Column = rand() % 10;
            Allignment = rand() % 4 + 1;

            switch (Allignment) //Checks and if possible to place places in the random decided direction
            {
            case 1: // up
                if (Row >= 2) {
                    int valid = 1;
                    for (int x = 0; x < 3; x++) // Check if there is a Ship
                    {
                        if (iBoard[Row - x][Column] != 0) {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) {
                        for (int x = 0; x < 3; x++) //Places the Ship
                        {
                            iBoard[Row - x][Column] = 3;
                        }
                        return 1;
                    }
                }
                break;
            case 2: // down
                if (Row <= 7) {
                    int valid = 1;
                    for (int x = 0; x < 3; x++) // Check if there is a Ship
                    {
                        if (iBoard[Row + x][Column] != 0)
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) {
                        for (int x = 0; x < 3; x++) //Places the Ship
                        {
                            iBoard[Row + x][Column] = 3;
                        }
                        return 1;
                    }
                }
                break;
            case 3: // left
                if (Column >= 2) {
                    int valid = 1;
                    for (int x = 0; x < 3; x++) // Check if there is a Ship
                    {
                        if (iBoard[Row][Column - x] != 0) {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) {
                        for (int x = 0; x < 3; x++) //Places the Ship
                        {
                            iBoard[Row][Column - x] = 3;
                        }
                        return 1;
                    }
                }
                break;
            case 4: // right
                if (Column <= 7) {
                    int valid = 1;
                    for (int x = 0; x < 3; x++) // Check if there is a Ship
                    {
                        if (iBoard[Row][Column + x] != 0) {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) {
                        for (int x = 0; x < 3; x++) //Places the Ship
                        {
                            iBoard[Row][Column + x] = 3;
                        }
                        return 1;
                    }
                }
                break;
            }
        } while (1);


    return 0;
}
int Xray(int iBoard[10][10]) {

    srand((unsigned int)time(NULL)); // Better number generation
    //Variables for placement of the Ship
    int Row;
    int Column;
    int Allignment;


    do {
        //Random generated location for the Ship
        Row = rand() % 10;
        Column = rand() % 10;
        Allignment = rand() % 4 + 1;

        switch (Allignment) //Checks and if possible to place places in the random decided direction
        {
        case 1: // up
            if (Row >= 2) {
                int valid = 1;
                for (int x = 0; x < 3; x++) // Check if there is a Ship
                {
                    if (iBoard[Row - x][Column] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 3; x++) //Places the Ship
                    {
                        iBoard[Row - x][Column] = 4;
                    }
                    return 1;
                }
            }
            break;
        case 2: // down
            if (Row <= 7) {
                int valid = 1;
                for (int x = 0; x < 3; x++) // Check if there is a Ship
                {
                    if (iBoard[Row + x][Column] != 0)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 3; x++) //Places the Ship
                    {
                        iBoard[Row + x][Column] = 4;
                    }
                    return 1;
                }
            }
            break;
        case 3: // left
            if (Column >= 2) {
                int valid = 1;
                for (int x = 0; x < 3; x++) // Check if there is a Ship
                {
                    if (iBoard[Row][Column - x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 3; x++) //Places the Ship
                    {
                        iBoard[Row][Column - x] = 4;
                    }
                    return 1;
                }
            }
            break;
        case 4: // right
            if (Column <= 7) {
                int valid = 1;
                for (int x = 0; x < 3; x++) // Check if there is a Ship
                {
                    if (iBoard[Row][Column + x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 3; x++) //Places the Ship
                    {
                        iBoard[Row][Column + x] = 4;
                    }
                    return 1;
                }
            }
            break;
        }
    } while (1);
}
int Zebra(int iBoard[10][10]) //code 5
{

    srand((unsigned int)time(NULL)); // Better number generation

    int Row;
    int Column;
    int Allignment;

    do {
        //Generates a random location on the board
        Row = rand() % 10;
        Column = rand() % 10;
        Allignment = rand() % 4 + 1;

        switch (Allignment) //Checks if possible to place and if so place the ship in the desired direction
        {
        case 1: // up
            if (Row >= 1) {
                int valid = 1;
                for (int x = 0; x < 2; x++) // Check if there is a Ship
                {
                    if (iBoard[Row - x][Column] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 2; x++) //Places the Ship
                    {
                        iBoard[Row - x][Column] = 5;
                    }
                    return 1;  
                }
            }
            break;
        case 2: // down
            if (Row <= 8) {
                int valid = 1;
                for (int x = 0; x < 2; x++) // Check if there is a Ship
                {
                    if (iBoard[Row + x][Column] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 2; x++) //Places the Ship
                    {
                        iBoard[Row + x][Column] = 5;
                    }
                    return 1; 
                }
            }
            break;
        case 3: // left
            if (Column >= 1) {
                int valid = 1;
                for (int x = 0; x < 2; x++) // Check if there is a Ship
                {
                    if (iBoard[Row][Column - x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 2; x++) //Places the Ship
                    {
                        iBoard[Row][Column - x] = 5;
                    }
                    return 1;  
                }
            }
            break;
        case 4: // right
            if (Column <= 8) {
                int valid = 1;
                for (int x = 0; x < 2; x++) // Check if there is a Ship
                {
                    if (iBoard[Row][Column + x] != 0) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    for (int x = 0; x < 2; x++) //Places the Ship
                    {
                        iBoard[Row][Column + x] = 5;
                    }
                    return 1;  
                }
            }
            break;
        }
    } while (1);


    return 0;
}
void ShipSunk(int iBoard[10][10], char cDummyBoard[10][10],char SunkShips[5])
{
    // Checks if Ship Victory Down and changes corresponding elements of the char array to 'V'
    int VictoryDown = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 1)
            {
                VictoryDown++;
            }
        }
    }

    if (VictoryDown >= 5)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 1)
                {
                    cDummyBoard[row][column] = 'V';
                }
            }
        }
        SunkShips[0] = 'V';
    }

    // Checks if Ship Western Down and changes corresponding elements of the char array to 'W'
    int WesternDown = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 2)
            {
                WesternDown++;
            }
        }
    }

    if (WesternDown >= 4)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 2)
                {
                    cDummyBoard[row][column] = 'W';
                }
            }
        }
        SunkShips[1] = 'W';
    }

    // Checks if Ship Yellow Down and changes corresponding elements of the char array to 'Y'
    int YellowDown = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 3)
            {
                YellowDown++;
            }
        }
    }

    if (YellowDown >= 3)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 3)
                {
                    cDummyBoard[row][column] = 'Y';
                }
            }
        }
        SunkShips[2] = 'Y';
    }

    // Checks if Ship Xray Down and changes corresponding elements of the char array to 'X'
    int XrayDown = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 4)
            {
                XrayDown++;
            }
        }
    }

    if (XrayDown >= 3)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 4)
                {
                    cDummyBoard[row][column] = 'X';
                }
            }
        }
        SunkShips[3] = 'X';
    }

    // Checks if Ship Zebra Down and changes corresponding elements of the char array to 'Z'
    int ZebraDown = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 5)
            {
                ZebraDown++;
            }
        }
    }

    if (ZebraDown >= 2)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (cDummyBoard[row][column] == 'H' && iBoard[row][column] == 5)
                {
                    cDummyBoard[row][column] = 'Z';
                }
            }
        }
        SunkShips[4] = 'Z';
    }
}
int missilesim(int iBoard[10][10], char cDummyBoard[10][10], int count, char SunkShips[5]) {

    
    char input[3]; // Missile Shot Cordinates input
    int cord[2] = { 0 }; // Intiger Cordinate version of the input
    int hit = 0; //Hit amount to determine if all ships are down
    

    do  // Loop to print the board after each shot and take input and check if hit or miss
    {
        clear; //Clears after everyshot
        printf("\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n\n"); // prints the top of the board for easy cordinates
        for (int row = 0; row < 10; row++) // Prints abcdefghj letters in front of every row for easy cordinates
        { 
            PutCords(row); //Puts letter cordinates
            for (int column = 0; column < 10; column++)
            {
                    printf("%c\t", cDummyBoard[row][column]); // Prints the player board 1 by 1
                    ShipStatus(SunkShips, row, column);
                    if (column == 9 && row == 7) {
                        printf("You Have Made %d Shots", count);
                    }
                    if (column == 9 && row == 8)
                    {
                        printf("-----------------------------");
                    }

            }
            printf("\n\n"); // Move to the next line after printing each row
        }
        printf("Please Enter Your The Desired Cordinates (QQ to leave and save)\nRow(A-J) - Column(0-9) Example (A5)\n");
        scanf("%2s", input);// Gets The Shots Cordinates

        cord[1] = input[1] - '0';

        if (strcmp(input, "QQ") == 0) {
            break; // Exit the loop if "QQ" is entered and save
        }

        switch (input[0]) //change the letter input into an intiger according to the rank
        {
        case 'A': // A is first element
            cord[0] = 0; // 0 because its 0 - 9 and 10 elements
            break;
        case 'B': // B is second element
            cord[0] = 1;
            break;
        case 'C':
            cord[0] = 2;
            break;
        case 'D':
            cord[0] = 3;
            break;
        case 'E':
            cord[0] = 4;
            break;
        case 'F':
            cord[0] = 5;
            break;
        case 'G':
            cord[0] = 6;
            break;
        case 'H':
            cord[0] = 7;
            break;
        case 'I':
            cord[0] = 8;
            break;
        case 'J':
            cord[0] = 9;
            break;
        default:
            cord[0] = 10;
            break;
        }
       
        if (cord[0] > 9 || cord[1] > 9 || cord[1] < 0)
        {
            
            printf("You have not entered a Valid cordinate\n");
            pause;
        }
        else if (cDummyBoard[cord[0]][cord[1]] != '~') {
          
            printf("You have shot there before please enter another cordinate\n");
            pause;
        }  else {
            if (iBoard[cord[0]][cord[1]] != 0) //Checks if the shot cordinate is a hit
            {
                cDummyBoard[cord[0]][cord[1]] = 'H'; // If so puts a H on the spot on the player board
                hit++;
                ShipSunk(iBoard, cDummyBoard, SunkShips); // checks if the ships has been sunk
            }
            else if (iBoard[cord[0]][cord[1]] == 0) //Checks if the shot is a miss
            {
                cDummyBoard[cord[0]][cord[1]] = 'M'; // If so puts a M on the spot on the player board
                

            }

            if (hit == 17) //Checks if all ships are sunk
            {
                break;
            }

            
           

            count++; // Keeps the shot count
        }

       
    } while (1);

    return count;
}
void SaveGame(int iBoard[10][10], char cDummyBoard[10][10], int count, char SunkShips[5]) {

    FILE* ptr = fopen("Save.txt", "w"); //Opens a new save file or open an already existing one

    if (ptr == NULL) // Checks if file is open
    {
        printf("Failed to open files for writing.\n");
        return;
    }

    for (int row = 0; row < 10; row++) //Prints the ship placement data to the text file
    {
        for (int column = 0; column < 10; column++)
        {
            fprintf(ptr, "%d", iBoard[row][column]);
        }
        fprintf(ptr, "\n"); // Move to the next line after printing each row
    }

    fprintf(ptr, "\n"); // a space between data for easier read on the save file

    for (int row = 0; row < 10; row++) // Saves the player board with hit or miss information
    {
        for (int column = 0; column < 10; column++)
        {
            fprintf(ptr, "%c", cDummyBoard[row][column]);
        }
        fprintf(ptr, "\n"); // Move to the next line after printing each row
    }
    fprintf(ptr, "\n");
    fprintf(ptr, "Shots: %d\n", count); // Saves the count for how many missiles were shot
    fprintf(ptr, "\n");
    for (int x = 0; x <= 4; x++)
    {
        fprintf(ptr, "%c", SunkShips[x]);
    }


    fclose(ptr); // Close file
}
int LoadGame(int iBoard[10][10], char cDummyBoard[10][10], int* count, char SunkShips[5])
{
    FILE* point = fopen("Save.txt", "r"); // Opens file for reading

    if (point == NULL) // Checks if file opened for reading
    {
        printf("Failed to open the file for reading.\n");
        return 0;
    }

    for (int row = 0; row < 10; row++) //Retrieves the data of the last saved game for the Board with Ship Information
    {
        for (int column = 0; column < 10; column++)
        {
            fscanf(point, "%1d", &iBoard[row][column]);
        }
        fscanf(point, "\n"); // Move to the next line after reading each row
    }

    fscanf(point, "\n");

    for (int row = 0; row < 10; row++) //Retrieves the data of the last saved game for the Player Board Information
    {
        for (int column = 0; column < 10; column++)
        {
            fscanf(point, "%c", &cDummyBoard[row][column]);
        }
        fscanf(point, "\n"); // Move to the next line after reading each row
    }

    fscanf(point, "\n");
    fscanf(point, "Shots: %d", count);// reads the shot count
    fscanf(point, "\n");
    for (int x = 0; x <= 4; x++) 
    {
        fscanf(point, "%c", &SunkShips[x]);
    }

    fclose(point); // Close File
}
void GameCore(int load)
{
    
    //Varibles for Main Board, Player Board and count
    char cDummyBoard[10][10]; // To Keep track where did the player have already shot a shot
    int iBoard[10][10] = { 0 , 0 }; // To keep track where the boats are placed and place the boats without collision
    int count = 0; // To keep shot count
    char SunkShips[5] = {'-'};

    int Choice = 0;
    do{
        count = 0;

        for (int x = 0; x < 5; x++) 
        {
            SunkShips[x] = '-';
        }

        if (load) //Checks if load or not load
        {
            LoadGame(iBoard, cDummyBoard, &count, SunkShips); // loads information for last game
            load = 0;
        }
        else {

            for (int row = 0; row < 10; row++) {
                for (int col = 0; col < 10; col++) {
                    iBoard[row][col] = 0;
                }
            }

            // Start a new game and populate the Main Board with 5 ships 
            Victory(iBoard);   // 5 lenght ship
            Western(iBoard);  // 4 lenght ship
            Yellow(iBoard);  // 3 lenght ship
            Xray(iBoard);   // 3 lenght ship
            Zebra(iBoard); // 2 lenght ship

            for (int row = 0; row < 10; row++) // Populates the Player Board with symbol like water
            {
                for (int column = 0; column < 10; column++) {
                    cDummyBoard[row][column] = '~';
                }
            }
        }
        count = missilesim(iBoard, cDummyBoard, count, SunkShips); // Start the game and return count of how many shots were shot

        if (SunkShips[0] == 'V' && SunkShips[1] == 'W' && SunkShips[2] == 'Y' && SunkShips[3] == 'X' && SunkShips[4] == 'Z')
        {
            clear;
            const char* message = "Congratulations! You have sunk all the ships. You are the winner!";
            int messageLength = strlen(message);
            int boxWidth = messageLength + 4;

            printf("+");
            for (int i = 0; i < boxWidth; i++) {
                printf("-");
            }
            printf("+\n");

            printf("|");
            for (int i = 0; i < boxWidth; i++) {
                printf(" ");
            }
            printf("|\n");

            printf("| %s |\n", message);

            printf("|");
            for (int i = 0; i < boxWidth; i++) {
                printf(" ");
            }
            printf("|\n");

            printf("+");
            for (int i = 0; i < boxWidth; i++) {
                printf("-");
            }
            printf("+\n\n");
            printf("Would you like to start a new game\n1- Yes\t2- Quit\n");
            scanf("%d", &Choice);
        }
        else {
            Choice = 2;
        }
        

    } while (Choice != 2);

   

    SaveGame(iBoard,cDummyBoard,count, SunkShips); // Saves the information to a txt file for future use
    printf("Game is Saved for future.\n"); // Prints the game saved
}