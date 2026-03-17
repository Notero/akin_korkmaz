//Programmed By Akin Korkmaz

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "reciperion.h" //.h header file for printing the genre list for user to select from

//CLEAR and PAUSE definitions
#define pause system("pause")
#define clear system("cls")

//struct for Tv Shows specifications
typedef struct {
    char title[30];
    char director[30];
    char genre[30];
    int genren;
    int release_year;
    int IMDB_rating;
} Series;

//Initialtes a new Collection or Load an existing one
void New_or_Load(int* load);
//changes the int value entered by the user to its corresponding genre type
void Name_Genre(Series** tv_series, int* count);
//Functions TO fill the Newly initiated Collection 
void Name_default(Series** tv_series, int* addhelp);
void Add_default(Series** tv_series, int* count, int* addhelp);
//SAVE AND LOAD FUNCTIONS
void saveToFile(Series** tv_series, int count, char filename[20]);
void loadFromFile(Series*** tv_series, int* count, char filename[20]);
//ADD,DELETE,SEARCH
void Add_Series(Series** tv_series, int* count);
void Delete_Series(Series** tv_series, int* count);
void Search_Series(Series** tv_series, int* count);
void displayAllSeries(Series** tv_series, int* count);
//SORT SECTION
void sort_by(Series** tv_series, int* count);
void title_alphabetical(Series** tv_series, int* count);
void IMBD_score(Series** tv_series, int* count);
void new_to_old(Series** tv_series, int* count);
//STATS
void stat(Series** tv_series, int* count);




int main()
{
    //Variables
    int selection = 0;
    int load = 0;
    int count = 0;
    int addhelp = 0;
    char filename[20];
    
    Series** tv_series = NULL;

    printf("Welcome to The TV Series Collection\n\n");


    New_or_Load(&load); // decision to create a new collection or load a previous one

    //switch to create a new collection or load a previous one from a bin file
    switch (load) 
    {
    case 1:
        clear;
        printf("Please enter the size of your current Collection\n");
        //takes the initial size of the Collection from the user
        scanf("%d", &count);
        printf("Please enter the name of your collection\n");
        //takes the name of the save file from the user
        scanf("%s", &filename);
        strcat(filename, ".bin");
        //allocates memory to the tv_series array
        tv_series = calloc(count, sizeof(Series*));
        for (addhelp; addhelp < count; addhelp++)
        {
            Add_default(tv_series, &count, &addhelp); // adds tv shows as many as the initial size determined by the user
        }
        break;
    case 2:
        clear;
       
        //checks if the a file with entered name exist if so loads
        bool exist = false;

        while (!exist) {
            printf("Please enter the name of your collection");
            scanf("%s", &filename);
            strcat(filename, ".bin");


            FILE* file = fopen(filename, "rb");
            if (file) {
                // File exists, so load the data
                fclose(file); // Close the file immediately after checking
                loadFromFile(&tv_series, &count, filename);
                printf("Collection loaded successfully.\n");
                exist = true;
            }
            else {
                printf("File with the specified name does not exist.\n");
            }
        }
        printf("%s Opened Succesfully!\n", filename);
        break;
    }

   
    pause;
    do {
        clear;
        //Menu for tv_show add,delete,search,sort, and stats
        printf("==========Main Menu==========\n");
        printf("1- Add a Tv Series to the Collection\n");
        printf("2- Delete a Tv Series from the Collection\n");
        printf("3- Search a Tv Series from the Collection\n");
        printf("4- Sort by...\n");
        printf("5- Stats of the Collection\n");
        printf("6- Quit\n");

        printf("Please enter your selection: ");
        //Take input
        scanf("%d", &selection);

        switch (selection) {
        case 1:

            tv_series = realloc(tv_series, (1 + count) * sizeof(Series*)); //reallocates 1 more memory slot to the tv_series array when user wants to add another tv show

            Add_Series(tv_series, &count); // call the add_series function to add a new series to the array
            
            break;
        case 2:
            Delete_Series(tv_series, &count); //Deletes the entered series from the collection
            break;
        case 3:
            Search_Series(tv_series, &count); // Searches series from the collection
            break;
        case 4:
            sort_by(tv_series, &count); // sorts the tv shows by given spesifications
            break;
        case 5:
            stat(tv_series, &count); // calls the stats function
            break;
        case 6:
            printf("Collection Saved and Closed.\n");
            printf("See you Later..\n");
            saveToFile(tv_series, count, filename); // saves the information to a .bin file
            break;
        default:
            printf("Not a valid selection from the menu\n"); // if selection is not between 1 - 6
            break;
        }
    } while (selection != 6);

    // Free the memory allocated for each series
    for (int i = 0; i < count; i++) 
    {
        free(tv_series[i]);
    }

    // Free the memory allocated for the array of pointers
    free(tv_series);

    return 0;
}

void New_or_Load(int* load)
{
    //tried a new thing I know I can use switch to check wheather if user entered a valid option
    bool valid_option = false;
    while (!valid_option)
    {
        printf("1- Start a New Collection\n2- Load a Collection\n");
        scanf("%d", &*load);


        if (*load < 3 || *load > 0)
        {
            valid_option = true;
        }
        else {
            printf("Not a Valid Choice\n");
        }
    }
}

void Name_Genre(Series** tv_series, int* count)
{
 //add the name of the genre to the struct after user enters their intiger equilivalent of the words.
    switch (tv_series[*count]->genren) {
    case 1:
        strcpy(tv_series[*count]->genre, "Drama");
        break;
    case 2:
        strcpy(tv_series[*count]->genre, "Comedy");
        break;
    case 3:
        strcpy(tv_series[*count]->genre, "Science Fiction");
        break;
    case 4:
        strcpy(tv_series[*count]->genre, "Fantasy");
        break;
    case 5:
        strcpy(tv_series[*count]->genre, "Mystery");
        break;
    case 6:
        strcpy(tv_series[*count]->genre, "Thriller");
        break;
    case 7:
        strcpy(tv_series[*count]->genre, "Horror");
        break;
    case 8:
        strcpy(tv_series[*count]->genre, "Romance");
        break;
    case 9:
        strcpy(tv_series[*count]->genre, "Action");
        break;
    case 10:
        strcpy(tv_series[*count]->genre, "Adventure");
        break;
    case 11:
        strcpy(tv_series[*count]->genre, "Documentary");
        break;
    case 12:
        strcpy(tv_series[*count]->genre, "Animation");
        break;
    case 13:
        strcpy(tv_series[*count]->genre, "Family");
        break;
    case 14:
        strcpy(tv_series[*count]->genre, "Reality TV");

    }
}
void Name_default(Series** tv_series, int* addhelp)
{
    switch (tv_series[*addhelp]->genren) {
    case 1:
        strcpy(tv_series[*addhelp]->genre, "Drama");
        break;
    case 2:
        strcpy(tv_series[*addhelp]->genre, "Comedy");
        break;
    case 3:
        strcpy(tv_series[*addhelp]->genre, "Science Fiction");
        break;
    case 4:
        strcpy(tv_series[*addhelp]->genre, "Fantasy");
        break;
    case 5:
        strcpy(tv_series[*addhelp]->genre, "Mystery");
        break;
    case 6:
        strcpy(tv_series[*addhelp]->genre, "Thriller");
        break;
    case 7:
        strcpy(tv_series[*addhelp]->genre, "Horror");
        break;
    case 8:
        strcpy(tv_series[*addhelp]->genre, "Romance");
        break;
    case 9:
        strcpy(tv_series[*addhelp]->genre, "Action");
        break;
    case 10:
        strcpy(tv_series[*addhelp]->genre, "Adventure");
        break;
    case 11:
        strcpy(tv_series[*addhelp]->genre, "Documentary");
        break;
    case 12:
        strcpy(tv_series[*addhelp]->genre, "Animation");
        break;
    case 13:
        strcpy(tv_series[*addhelp]->genre, "Family");
        break;
    case 14:
        strcpy(tv_series[*addhelp]->genre, "Reality TV");

    }
}

void Add_default(Series** tv_series, int* count, int* addhelp)
{
    clear;
    // Allocate memory for the new series
    tv_series[*addhelp] = calloc(1, sizeof(Series));

    if (tv_series[*count] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Input series details
    printf("Enter the title of the series: ");
    scanf(" %s", tv_series[*addhelp]->title);

    printf("Enter the director of the series: ");
    scanf(" %s", tv_series[*addhelp]->director);


    bool validGenre = false;
    while (!validGenre) {
        genres();
        printf("Enter the genre of the series (0-14): ");
        scanf("%d", &tv_series[*addhelp]->genren);

        if (tv_series[*addhelp]->genren >= 0 && tv_series[*addhelp]->genren <= 14) {
            validGenre = true; // Exit the loop if a valid genre is entered
        }
        else {
            printf("Invalid genre. Please enter a number between 0 and 14.\n");
            // You can choose to continue the loop to ask for the genre again
        }
    }

    Name_default(tv_series, addhelp);

    printf("Enter the release year of the series: ");
    scanf("%d", &tv_series[*addhelp]->release_year);

    printf("Enter the IMDB rating of the series: ");
    scanf("%d", &tv_series[*addhelp]->IMDB_rating);

}

void saveToFile(Series** tv_series, int count, char filename[20])
{

    FILE* file = fopen(filename, "wb"); // opens the fire writing mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the count to the file
    fwrite(&count, sizeof(count), 1, file); // writes the count

    // Write the entire array of Series to the file

    for (int i = 0; i < count; i++) {
        fwrite(tv_series[i], sizeof(Series), 1, file); // writes the whole array
    }

    // Close the file
    fclose(file);
}
void loadFromFile(Series*** tv_series, int* count, char filename[20])
{
    FILE* file = fopen(filename, "rb"); // opens the file reading mode

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read the count from the file
    fread(count, sizeof(int), 1, file);

    // Allocate memory for the array of pointers based on the count
    *tv_series = calloc(*count, sizeof(Series*));

    // Read the entire array of Series from the file
    for (int i = 0; i < *count; i++) {
        (*tv_series)[i] = malloc(sizeof(Series));
        fread((*tv_series)[i], sizeof(Series), 1, file);
    }

    // Close the file
    fclose(file);
}

void Add_Series(Series** tv_series, int* count)
{
    clear;
    // Allocate memory for the new series
    tv_series[*count] = calloc(1, sizeof(Series));

    if (tv_series[*count] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Input series details
    printf("Enter the title of the series: ");
    scanf(" %s", tv_series[*count]->title);

    printf("Enter the director of the series: ");
    scanf(" %s", tv_series[*count]->director);


    bool validGenre = false;
    while (!validGenre) {
        genres();
        printf("Enter the genre of the series (0-14): ");
        scanf("%d", &tv_series[*count]->genren);

        if (tv_series[*count]->genren >= 0 && tv_series[*count]->genren <= 14) {
            validGenre = true; // Exit the loop if a valid genre is entered
        }
        else {
            printf("Invalid genre. Please enter a number between 0 and 14.\n");
        }
    }
    
    Name_Genre(tv_series, count);

    printf("Enter the release year of the series: ");
    scanf("%d", &tv_series[*count]->release_year);

    printf("Enter the IMDB rating of the series: ");
    scanf("%d", &tv_series[*count]->IMDB_rating);

    // Increment the count of series
    (*count)++;
}

void Delete_Series(Series** tv_series, int* count)
{
    clear;
    char to_be_deleted[31]; // Increase the size to accommodate the null terminator

    printf("Please enter the Title of the Series you would like to delete: ");
    scanf(" %30s", to_be_deleted); // Read at most 30 characters to leave room for null terminator

    // Null-terminate the input manually
    to_be_deleted[30] = '\0';

    int found = 0;



    for (int i = 0; i < *count; i++) {
        if (strcmp(tv_series[i]->title, to_be_deleted) == 0) {
            found = 1;
            // Free memory for the found series
            free(tv_series[i]);

            // Move the remaining elements to close the gap
            for (int j = i; j < *count - 1; j++) {
                tv_series[j] = tv_series[j + 1];
            }

            // Decrement the count to reflect the removal of one series
            (*count)--;
            break;
        }
    }

    if (found) {
        printf("Series '%s' has been deleted from the collection.\n", to_be_deleted);
    }
    else {
        printf("Series with the title '%s' not found in the collection.\n", to_be_deleted);
    }
}

void Search_Series(Series** tv_series, int* count)
{
    clear;
    char searched_item[30] = "";

    printf("Please enter the Title of the Series you would like to search: ");
    scanf(" %30s", searched_item);

    //takes the title name of the tv show and searches it among everything.
    for (int i = 0; i < *count; i++) {
        if (strcmp(tv_series[i]->title, searched_item) == 0) {

                printf("Series %d:\n", i + 1);
                printf("Title: %s\n", tv_series[i]->title);
                printf("Director: %s\n", tv_series[i]->director);
                printf("Genre: %s\n", tv_series[i]->genre);
                printf("Release Year: %d\n", tv_series[i]->release_year);
                printf("IMDB Rating: %d\n", tv_series[i]->IMDB_rating);
                printf("\n");

            pause;
            break;
        }
    }
}

// Function to display all TV series in the array
void displayAllSeries(Series** tv_series, int* count) 
{

    

    for (int i = 0; i < *count; i++) {
        printf("Series %d:\n", i + 1);
        printf("Title: %s\n", tv_series[i]->title);
        printf("Director: %s\n", tv_series[i]->director);
        printf("Genre: %s\n", tv_series[i]->genre);
        printf("Release Year: %d\n", tv_series[i]->release_year);
        printf("IMDB Rating: %d\n", tv_series[i]->IMDB_rating);
        printf("\n");
    }
}



void sort_by(Series** tv_series, int* count)
{
    clear;
    int select = 0;
    //menu to decide what to sort by
    printf("sort by:\n1- Alphabetical Order (Title)\n2- IMBD score (high to low)\n3- Most recent to old\n4-Back");
    scanf("%d", &select);

    switch (select) 
    {
    case 1:
        title_alphabetical(tv_series, count); // sorts alphabetical
        break;
    case 2:
        IMBD_score(tv_series, count); // sorts by IMDB
        break;
    case 3:
        new_to_old(tv_series, count);// sort newest to oldest
        break;
    case 4 :
        return;
    default:
        printf("Not a Valid Selection");
        break;

    }


}

void title_alphabetical(Series** tv_series, int* count)
{
    clear;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = 0; j < *count - i - 1; j++)
        {
            if (strcmp(tv_series[j]->title, tv_series[j + 1]->title) > 0)
            {
                // Swap the pointers to rearrange the series
                Series* temp = tv_series[j];
                tv_series[j] = tv_series[j + 1];
                tv_series[j + 1] = temp;
            }
        }
    }
    displayAllSeries(tv_series, count);
    pause;

}

void IMBD_score(Series** tv_series, int* count)
{
    clear;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = 0; j < *count - i - 1; j++)
        {
            if (tv_series[j]->IMDB_rating < tv_series[j + 1]->IMDB_rating) 
            {
                // Swap the pointers to rearrange the series
                Series* temp = tv_series[j];
                tv_series[j] = tv_series[j + 1];
                tv_series[j + 1] = temp;
            }
        }
    }
    displayAllSeries(tv_series, count);
    pause;
}

void new_to_old(Series** tv_series, int* count)
{
    clear;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = 0; j < *count - i - 1; j++)
        {
            if (tv_series[j]->release_year < tv_series[j + 1]->release_year)
            {
                // Swap the pointers to rearrange the series
                Series* temp = tv_series[j];
                tv_series[j] = tv_series[j + 1];
                tv_series[j + 1] = temp;
            }
        }
    }
    displayAllSeries(tv_series, count);
    pause;

}

void stat(Series** tv_series, int* count)
{
    clear;
    printf("There are %d shows in the Collection\n", *count);

    int shows_in_genre[14] = {0};

    for (int i = 0; i < *count; i++) 
    {
        switch (tv_series[i]->genren) 
        {
        case 1:
            shows_in_genre[0]++;
            break;
        case 2:
            shows_in_genre[1]++;
            break;
        case 3:
            shows_in_genre[2]++;
            break;
        case 4:
            shows_in_genre[3]++;
            break;
        case 5:
            shows_in_genre[4]++;
            break;
        case 6:
            shows_in_genre[5]++;
            break;
        case 7:
            shows_in_genre[6]++;
            break;
        case 8:
            shows_in_genre[7]++;
            break;
        case 9:
            shows_in_genre[8]++;
            break;
        case 10:
            shows_in_genre[9]++;
            break;
        case 11:
            shows_in_genre[10]++;
            break;
        case 12:
            shows_in_genre[11]++;
            break;
        case 13:
            shows_in_genre[12]++;
            break;
        case 14:
            shows_in_genre[13]++;
        }
    }
    //prints the genre by how many it had in them
    const char* genres[] = {
        "Drama", "Comedy", "Science Fic.", "Fantasy", "Mystery",
        "Thriller", "Horror", "Romance", "Action", "Adventure", "Documentary",
        "Animation", "Family", "Reality TV"
    };

    int numGenres = sizeof(genres) / sizeof(genres[0]);

    printf("Number of TV Series within each Genre:\n");
    for (int i = 0; i < numGenres; i++) {
        printf("%d. %s\t %d\n", i + 1, genres[i], shows_in_genre[i]);
        
    }

    // Your code to calculate Shannon Entropy
    double total = 0.0;
    for (int i = 0; i < 14; i++) {
        total += (((double)shows_in_genre[i] / 14) * log2((double)shows_in_genre[i] / 14));
    }

    // Display the Shannon Entropy value
    printf("Variation: %f\n", -total);
    printf("Higher the Variation value Higher the variation\n");// Negate the total to get the final result

    //calculates the average age of the collection
    double yearaverage = 0 ;
    for (int i = 0; i < *count; i++) 
    {
        yearaverage =+ tv_series[i]->release_year;
    }
    yearaverage = yearaverage / *count;

    printf("Average year of the Tv Shows in The Collection %f\n", yearaverage);


    //calculates IMBD average
    double IMBDaverage = 0;
    for (int i = 0; i < *count; i++)
    {
        IMBDaverage = +tv_series[i]->IMDB_rating;
    }
    IMBDaverage = IMBDaverage / *count;

    printf("Average IMDB of the Tv Shows in The Collection %f\n", IMBDaverage);

    pause;

}


