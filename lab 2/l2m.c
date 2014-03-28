#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../src/l2.h"

int main() {
    // Determine current time
    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    // Get FICA numbers from file
    float FICARate;
    int FICALimit;
    FILE *inFICA;
    char inFICAName[25];

    while(1) {
        printf("Enter filename containing FICA values (\"exit\" to terminate): ");
        scanf("%s", &inFICAName);
        if (strcmp(inFICAName, "exit") == 0)
            exit(-1);
        inFICA = fopen(inFICAName, "r");
        if (inFICA != NULL)
            break;
        printf("File not found. Try again.\n");
    }

    fscanf(inFICA, "%f %d", &FICARate, &FICALimit);
    fclose(inFICA);

    // Get maximum number of lines per page
    int linesPerPage;
    FILE *inLines;
    char inLinesName[25];
    while(1) {
        printf("Enter filename containing value for lines per page (\"exit\" to terminate): ");
        scanf("%s", &inLinesName);
        if (strcmp(inLinesName, "exit") == 0)
            exit(-1);
        inLines = fopen(inLinesName, "r");
        if (inLines != NULL)
            break;
        printf("File not found. Try again.\n");
    }

    fscanf(inLines, "%d", &linesPerPage);
    fclose(inLines);

    // Input data file
    FILE *inFile;
    char inFileName[35];
    while(1) {
        printf("Enter filename containing record data (\"exit\" to terminate): ");
        scanf("%s", &inFileName);
        if (strcmp(inFileName, "exit") == 0)
            exit(-1);
        inFile = fopen(inFileName, "r");
        if (inFile != NULL)
            break;
        printf("File not found. Try again.\n");
    }

    // Output report file
    FILE *outFile;
    char outFileName[40];
    while(1) {
        printf("Enter filename for the final report (\"exit\" to terminate): ");
        scanf("%s", &outFileName);
        if (strcmp(outFileName, "exit") == 0)
            exit(-1);
        outFile = fopen(outFileName, "r");

        if (outFile != NULL) {
            char overwrite;
            printf("Existing output file found. Overwrite? (Y/N) ");
            scanf(" %c", &overwrite);
            if (overwrite == 'N' || overwrite == 'n') {
                fclose(outFile);
                printf("File will not be overwritten. Terminating.\n");
                exit(1);
            } else {
                printf("File will be overwritten.\n");
                fclose(outFile);
                outFile = fopen(outFileName, "w");
                break;
            }
        }

        if (outFile == NULL) {
            printf("Existing file not found, creating new report file with new name.\n");
            outFile = fopen(outFileName, "w");
            break;
        }
    }


    // Header text
    fprintf(outFile, "%50s\n", "ACME Sports Inc.");
    fprintf(outFile, "%59s\n", "We are the best, you use the best!");
    fprintf(outFile, "%55s\n", c_time_string);

    // Declaration and initialization
    employee emp;
    double totalGross = 0;
    double pageGross = 0;
    double totalFICA = 0;
    double pageFICA = 0;
    double totalNet = 0;
    double pageNet = 0;
    double deptGrossTotal = 0;
    double deptFICATotal = 0;
    double deptNetTotal = 0;
    double gross, FICA, net;
    char prevDept[8], currDept[8], printStr1[15], printStr2[15], printStr3[15], printStr4[15];
    int lineCount = 1;
    int lineCountSum = 0;
    int pageCount = 1;

    // Print header for first page
    fprintf(outFile, "%20s\n", "ACME");
    fprintf(outFile, "%-4s %6s %17s %12s %14s %13s %11s %12s\n\n", "Emp #", "Given", "Surname", "Dept", "New YTD" , "Gross", "FICA", "Net");

    // Scan for records
    while (fscanf(inFile, "%d %s %s %s %f %f %f", &emp.empNum, &emp.fname, &emp.lname, &emp.dept, &emp.ytd, &emp.payRate, &emp.hours) != EOF) {

        // Compare current and previous departments to see if department totals need to be printed
        strcpy(prevDept, currDept);
        strcpy(currDept, emp.dept);
        if (lineCount != 1 && strcmp(prevDept, currDept) != 0) {
            fprintf(outFile, "%73s %11s %12s\n", "--------", "--------", "--------");
            prettyPrint(printStr1, deptGrossTotal);
            prettyPrint(printStr2, deptFICATotal);
            prettyPrint(printStr3, deptNetTotal);
            fprintf(outFile, "%51s totals: %14s %11s %12s\n\n", prevDept, printStr1, printStr2, printStr3);
            deptGrossTotal = deptFICATotal = deptNetTotal = 0;
        }

        // Print headers and footers for a new page if lines exceed specified number
        if (lineCount > linesPerPage) {
            newPage(&pageCount, &lineCount, &pageGross, &pageFICA, &pageNet, outFile);
        }

        // Calculate gross, FICA and net numbers
        gross = calcGross(emp.hours, emp.payRate);
        FICA = calcFICA(emp.ytd, gross, FICARate, FICALimit);
        net = gross - FICA;

        // Print each employee record
        prettyPrint(printStr1, emp.ytd);
        prettyPrint(printStr2, gross);
        prettyPrint(printStr3, FICA);
        prettyPrint(printStr4, net);
        fprintf(outFile, "%-6d %-15s %-15s %-6s %14s %13s %11s %12s\n", emp.empNum, emp.fname, emp.lname, emp.dept, printStr1, printStr2, printStr3, printStr4);

        // Tally values
        pageGross += gross;
        totalGross += gross;
        pageFICA += FICA;
        totalFICA += FICA;
        pageNet += net;
        totalNet += net;
        deptGrossTotal += gross;
        deptFICATotal += FICA;
        deptNetTotal += net;
        lineCount++;
        lineCountSum++;
    }

    // Print department totals on last page
    fprintf(outFile, "%73s %11s %12s\n", "--------", "--------", "--------");
    prettyPrint(printStr1, deptGrossTotal);
    prettyPrint(printStr2, deptFICATotal);
    prettyPrint(printStr3, deptNetTotal);
    fprintf(outFile, "%51s totals: %14s %11s %12s\n\n", prevDept, printStr1, printStr2, printStr3);
    deptGrossTotal = deptFICATotal = deptNetTotal = 0;

    // Print page totals on last page
    prettyPrint(printStr1, pageGross);
    prettyPrint(printStr2, pageFICA);
    prettyPrint(printStr3, pageNet);
    fprintf(outFile, "\nPage totals: %61s %11s %12s\n", printStr1, printStr2, printStr3);
    fprintf(outFile, "\n%92s %d\n\n\f", "Page", pageCount++);

    // Print report summary
    fprintf(outFile, "\n%49s\n\n", "Report Summary");
    fprintf(outFile, "Records processed: %d\n", lineCountSum);
    prettyPrint(printStr1, totalGross);
    prettyPrint(printStr2, totalFICA);
    prettyPrint(printStr3, totalNet);
    fprintf(outFile, "Total gross: %10s\n", printStr1);
    fprintf(outFile, "Total FICA:  %11s\n", printStr2);
    fprintf(outFile, "Total net:   %10s\n", printStr3);
    fprintf(outFile, "\n%92s %d\n\n", "Page", pageCount);

    // Close files
    fclose(inFile);
    fclose(outFile);

    printf("Report successfully written. Program terminating.\n");

    return(0);
}
