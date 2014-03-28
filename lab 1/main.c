#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Declaration and initialization
    float grossPay, ytd;
    int employeeNumber;
    
    double totalGross = 0;
    double totalFICATaxed = 0;
    double FICATaxedAmt;
    char FICATaxedAmtStr[10];
    char totalFICATaxedStr[10];
    double FICA = 0.0678;
    double FICALimit = 69782;
    char processAnswer = 'Y';
    int lineCount = 0;
    
    // Determine current time
    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    
    // Input file
    FILE *inFile;
    char inFileName[] = "L2COSC2347CtlBrkDataSp13.txt";
    
    // Output file
    FILE *outFile;
    char fileOutName[] = "lab2out.txt";
    
//    char overwrite;
//    
//    outFile = fopen(fileOutName, "w");
//    
//    // Test if output file already exists
//    if (outFile != NULL) {
//        printf("Existing output file found. Overwrite? (Y/N) ");
//        scanf("%c", &overwrite);
//        if (overwrite == 'N' || overwrite == 'n') {
//            fclose(outFile);
//            printf("File will not be overwritten. Terminating.");
//            exit(1);
//        } else {
//            printf("File will be overwritten.\n");
//        }
//    }
    
    // Header text
    fprintf(outFile, "\t\t\t\t\t\tLab 1\n");
    fprintf(outFile, "\t\t\t\t\tFranklin Leung\n");
    fprintf(outFile, "\t\t\t\tDue: February 17, 2012\n");
    fprintf(outFile, "\t\t\tSubmitted: February 17, 2012\n\n");
    fprintf(outFile, "%23s %s %37s\n", "", "ACME", c_time_string);
    
    // Headers for columns
    fprintf(outFile, "%-6s %6s  %-8s %-8s %10s %10s %10s\n\n", "Line #", "Emp #", "Given", "Surname" , "YTD($)  ", "Gross($) ", "FICA Tax ");
    
    
    int empNum;
    char fName[15];
    char lName[15];
    char dept[6];
    float ytd;
    float payRate;
    float hours;
    
    while(fscanf(inFile, "%d %s %s %s %f %%f %f", &empNum, &fName, &lName, &dept, &ytd, &payRate, &hours) != EOF) {
        fprintf(outFile, "%d %s %s %s %f %%f %f\n", empNum, fName, lName, dept, ytd, payRate, hours);
    }
    
    // Prompt user for input
    while (processAnswer == 'Y' || processAnswer == 'y') {
        lineCount++;
        
        printf("Enter employee number: ");
        scanf("%d", &employeeNumber);
        
        printf("Enter first name: ");
        scanf("%s", &fName);
        
        printf("Enter last name: ");
        scanf("%s", &lName);
        
        printf("Enter YTD: ");
        scanf("%f", &ytd);
        
        printf("Enter gross pay: ");
        scanf("%f", &grossPay);
        
        if (ytd >= FICALimit) {
            FICATaxedAmt = 0;
        } else if (ytd + grossPay <= FICALimit) {
            FICATaxedAmt = grossPay * FICA;
        } else {
            FICATaxedAmt = FICA * (FICALimit - ytd);
        }
        
        totalGross += grossPay;
        totalFICATaxed += FICATaxedAmt;
        // To solve the $ issue without using money.h (which doesn't exist?) or having to manipulate character arrays, I used sprintf to print the double as a string, prefixed the string with a $ sign, then saved that as a new string.
        // That new string (FICATaxedAmtStr) is used in fprintf below, and I use fprintf to right-justify the number (which is in string format).
        // The float output is limited to .2 to present it as money (in cents) without a number to the left of the decimal point to keep the $ sign right next to the number. It would otherwise print out something like $   0.00.
        sprintf(FICATaxedAmtStr, "$%.2f", FICATaxedAmt);
        
        // Print info for each employee
        fprintf(outFile, "%-6d %6d  %-8s %-8s %10.2f %10.2f %10s\n", lineCount, employeeNumber, fName, lName, ytd, grossPay, FICATaxedAmtStr);
        // To answer part B: C rounds the numbers, rather than truncate.
        
        printf("Process new employee? (Y/N) ");
        scanf(" %c", &processAnswer);
    }
    
    // Print totals
    sprintf(totalFICATaxedStr, "$%.2f", totalFICATaxed);
    fprintf(outFile, "\n%34s %-8s %10.2f %10s", "", "Totals", totalGross, totalFICATaxedStr);
    
    // Close files
    fclose(inFile);
    fclose(outFile);
    
    return(0);
}

