#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {

    char fileName[] = "Safe.txt";
    char log[] = "log.txt";
    FILE * fp = NULL;
    long balance = 0;
    char get[100];  // Increased buffer size
    int add = 0;
    long long TotalNumberofEntries = 0;
    char *endptr;

    // Attempt to open the file for reading
    fp = fopen(fileName, "r");
    
    if (fp != NULL) {
        // Reading the TotalNumberofEntries
        if (fgets(get, sizeof(get), fp) != NULL) {
            TotalNumberofEntries = strtoll(get, &endptr, 10);
            if (endptr == get || *endptr != '\n') {  // Ensure successful conversion
                printf("Error: Invalid data format for TotalNumberofEntries.\n");
                fclose(fp);
                return 1;
            }
            printf("Read TotalNumberofEntries: %llu\n", TotalNumberofEntries);  // Debugging output
        } else {
            printf("Error reading TotalNumberofEntries from file\n");
            fclose(fp);
            return 1;
        }

        // Reading the balance
        if (fgets(get, sizeof(get), fp) != NULL) {
            balance = strtol(get, &endptr, 10);
            if (endptr == get || *endptr != '\n') {  // Ensure successful conversion
                printf("Error: Invalid data format for balance.\n");
                fclose(fp);
                return 1;
            }
            printf("Read Balance: %lu\n", balance);  // Debugging output
        } else {
            printf("Error reading balance from file\n");
            fclose(fp);
            return 1;
        }

        fclose(fp);
    } else {
        // If the file doesn't exist or can't be opened, initialize values
        printf("File not found. Initializing new data...\n");
        TotalNumberofEntries = 0;
        balance = 0;
    }

    printf("Current Balance: %lu\n", balance);

    // Prompt user to add an amount
    printf("Please Enter Amount in $ to add to safe:\n");
    if (scanf("%d", &add) != 1) {
        printf("Error: Invalid input for amount.\n");
        return 1;
    }

    balance += add;
    TotalNumberofEntries++;

    // Write the updated data to the file
    fp = fopen(fileName, "w");
    if (fp != NULL) {
        fprintf(fp, "%llu\n", TotalNumberofEntries);
        fprintf(fp, "%lu\n", balance);
        fclose(fp);
    } else {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // Log the transaction
        printf("Attempting to open log file: %s\n", log);
        fp = fopen(log, "a");
        if (fp != NULL) {
            printf("Log file opened successfully.\n");
            fprintf(fp, "Entry - %llu - Balance == [%lu]\n", TotalNumberofEntries, balance);
            fclose(fp);
            printf("Transaction logged successfully.\n");
        } else {
            printf("Error: Could not open log file: %s\n", log);
            return 1;
        }

    printf("New Balance: %lu\n", balance);

    return 0;
}
