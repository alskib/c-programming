#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct {
    int empNum;
    char lname[15];
    char fname[15];
    char dept[8];
    float ytd;
    float payRate;
    float hours;
} employee;

double calcFICA(float ytd, float gross, double FICARate, double FICALimit);
void newPage(int *pageCount, int *lineCount, double *pageGross, double *pageFICA, double *pageNet);
double calcGross(double hours, double rate);
void prettyPrint(char string[], float value);

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
    inFICA = fopen("FICA.txt", "r");
    // char inFICAName[25];
    
    // while(1) {
        // printf("Enter filename containing FICA values (\"exit\" to terminate): ");
        // scanf("%s", &inFICAName);
        // if (strcmp(inFICAName, "exit") == 0)
            // exit(-1);
        // inFICA = fopen(inFICAName, "r");
        // if (inFICA != NULL)
            // break;
        // printf("File not found. Try again.\n");
    // }
    
    fscanf(inFICA, "%f %d", &FICARate, &FICALimit);
    fclose(inFICA);
    
    // Get maximum number of lines per page
    int linesPerPage;
    FILE *inLines;
    inLines = fopen("lines.txt", "r");
    // char inLinesName[25];
    // while(1) {
        // printf("Enter filename containing value for lines per page (\"exit\" to terminate): ");
        // scanf("%s", &inLinesName);
        // if (strcmp(inLinesName, "exit") == 0)
            // exit(-1);
        // inLines = fopen(inLinesName, "r");
        // if (inLines != NULL)
            // break;
        // printf("File not found. Try again.\n");
    // }
    
    fscanf(inLines, "%d", &linesPerPage);
    fclose(inLines);
    
    // Input data file
    FILE *inFile;
    inFile = fopen("data.txt", "r");
    // char inFileName[25];
    // while(1) {
        // printf("Enter filename containing record data (\"exit\" to terminate): ");
        // scanf("%s", &inFileName);
        // if (strcmp(inFileName, "exit") == 0)
            // exit(-1);
        // inFile = fopen(inFileName, "r");
        // if (inFile != NULL)
            // break;
        // printf("File not found. Try again.\n");
    // }
    
    // Output report file
    FILE *outFile;
    outFile = fopen("out.txt", "w");
    // while(1) {
        // printf("Enter filename for the final report (\"exit\" to terminate): ");
        // scanf("%s", &outFileName);
        // if (strcmp(outFileName, "exit") == 0)
            // exit(-1);
        // outFile = fopen(outFileName, "r");
        
        // if (outFile != NULL) {
            // char overwrite;
            // printf("Existing output file found. Overwrite? (Y/N) ");
            // scanf(" %c", &overwrite);
            // if (overwrite == 'N' || overwrite == 'n') {
                // fclose(outFile);
                // printf("File will not be overwritten. Terminating.");
                // exit(1);
            // } else {
                // printf("File will be overwritten.\n");
                // fclose(outFile);
                // outFile = fopen(outFileName, "w");
                // break;
            // }
        // }
        
        // if (outFile == NULL) {
            // printf("Existing file not found, creating new report file with new name.\n");
            // fclose(outFile);
            // outFile = fopen(outFileName, "w");
            // break;
        // }
    // }
    
    // Header text
//    fprintf(outFile, "\t\t\t\t\tACME Sports Inc.\n");
//    fprintf(outFile, "\t\t\tWe are the best, you use the best!\n");
//    fprintf(outFile, "\t\t\t\t %s\n", c_time_string);
//    fprintf(outFile, "\t\tACME\n");
    printf("\t\t\t\t\tACME Sports Inc.\n");
    printf("\t\t\tWe are the best, you use the best!\n");
    printf("\t\t\t\t %s\n", c_time_string);
    
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
    printf("\t\tACME\n");
    printf("%-4s %6s %17s %12s %14s %13s %11s %12s\n\n", "Emp #", "Given", "Surname", "Dept", "New YTD" , "Gross", "FICA", "Net");
    
    // Scan for records
    while (fscanf(inFile, "%d %s %s %s %f %f %f", &emp.empNum, &emp.fname, &emp.lname, &emp.dept, &emp.ytd, &emp.payRate, &emp.hours) != EOF) {
        
        // Compare current and previous departments to see if department totals need to be printed
        strcpy(prevDept, currDept);
        strcpy(currDept, emp.dept);
        if (lineCount != 1 && strcmp(prevDept, currDept) != 0) {
            printf("%73s %11s %12s\n", "--------", "--------", "--------");
            prettyPrint(printStr1, deptGrossTotal);
            prettyPrint(printStr2, deptFICATotal);
            prettyPrint(printStr3, deptNetTotal);
            printf("\t\t\t\t %18s totals: %14s %11s %12s\n\n", prevDept, printStr1, printStr2, printStr3);
            deptGrossTotal = deptFICATotal = deptNetTotal = 0;
        }
        
        // Print headers and footers for a new page if lines exceed specified number
        if (lineCount > linesPerPage)
            newPage(&pageCount, &lineCount, &pageGross, &pageFICA, &pageNet);
        
        // Calculate gross, FICA and net numbers
        gross = calcGross(emp.hours, emp.payRate);
        FICA = calcFICA(emp.ytd, gross, FICARate, FICALimit);
        net = gross - FICA;
        
        // Print each employee record
        prettyPrint(printStr1, emp.ytd);
        prettyPrint(printStr2, gross);
        prettyPrint(printStr3, FICA);
        prettyPrint(printStr4, net);
        printf("%-6d %-15s %-15s %-6s %14s %13s %11s %12s\n", emp.empNum, emp.fname, emp.lname, emp.dept, printStr1, printStr2, printStr3, printStr4);
        
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
    printf("%73s %11s %12s\n", "--------", "--------", "--------");
    prettyPrint(printStr1, deptGrossTotal);
    prettyPrint(printStr2, deptFICATotal);
    prettyPrint(printStr3, deptNetTotal);
    printf("\t\t\t\t %18s totals: %14s %11s %12s\n\n", prevDept, printStr1, printStr2, printStr3);
    deptGrossTotal = deptFICATotal = deptNetTotal = 0;
    
    // Print page totals on last page
    prettyPrint(printStr1, pageGross);
    prettyPrint(printStr2, pageFICA);
    prettyPrint(printStr3, pageNet);
    printf("\nPage totals: %61s %11s %12s\n", printStr1, printStr2, printStr3);
    printf("\n%92s %d\n\n", "Page", pageCount++);
    
    // Print report summary
    printf("\t\t\t Report Summary\n\n");
    printf("Records processed: %d\n", lineCountSum);
    prettyPrint(printStr1, totalGross);
    prettyPrint(printStr2, totalFICA);
    prettyPrint(printStr3, totalNet);
    printf("Total gross: %10s\n", printStr1);
    printf("Total FICA:  %11s\n", printStr2);
    printf("Total net:   %10s\n", printStr3);
    printf("\n%92s %d\n\n", "Page", pageCount);

    // Close files
    fclose(inFile);
    fclose(outFile);
    
    printf("Report successfully written. Program terminating.\n");
    
    return(0);
}

double calcFICA(float ytd, float gross, double FICARate, double FICALimit) {
    // Calculate amount of FICA owed depending on gross income and federal rates
    if (ytd >= FICALimit)
        return 0;
    if (ytd + gross <= FICALimit)
        return gross * FICARate;
    return FICARate * (FICALimit - ytd);
}

void newPage(int *pageCount, int *lineCount, double *pageGross, double *pageFICA, double *pageNet) {
    // Print footer for previous page and header for new page and all necessary totals
    char str1[15], str2[15], str3[15];
    prettyPrint(str1, *pageGross);
    prettyPrint(str2, *pageFICA);
    prettyPrint(str3, *pageNet);
    
    printf("\nPage totals: %61s %11s %12s\n", str1, str2, str3);
    printf("\n%92s %d\n\n\f", "Page", *pageCount);
    printf("\t\tACME\n");
    printf("%-4s %6s %17s %12s %14s %13s %11s %12s\n\n", "Emp #", "Given", "Surname", "Dept", "New YTD" , "Gross", "FICA", "Net");
    *pageCount += 1;
    *pageGross = *pageFICA = *pageNet = 0;
    *lineCount = 1;
}

double calcGross(double hours, double rate) {
    // Return normal rate if < 40, or normal rate for 40 hours and 1.5x each extra hour for > 40
    return (hours <= 40) ? (hours * rate) : (40 * rate) + (1.5 * (hours - 40) * rate);
}

void prettyPrint(char string[], float value) {
    // Insert commas and dollar sign where appropriate for values (only valid for < 1 million)
    if (value >= 1000) {
        sprintf(string, "$%d,%03d.%02.0f ", (int)value/1000, (int)value % 1000, (value-floor(value))*100);
    } else {
        sprintf(string, "$%d.%02.0f ", (int)value % 1000, (value-floor(value))*100);
    }
}






    
//      PREV STUFF
//    while(1) {
//        
//        
//        strcpy(currDept, emp.dept);
//        if (fscanf(inFile, "%d %s %s %s %f %f %f", &emp.empNum, &emp.fname, &emp.lname, &emp.dept, &emp.ytd, &emp.payRate, &emp.hours) != EOF) {
//            
//            //printf("currDept: %s emp.dept: %s\n", currDept, emp.dept);
//            
//            lineCount++;
//            
//            totalGross += emp.ytd;
//            pageGross += emp.ytd;
//            totalFICA += emp.payRate;
//            pageFICA += emp.payRate;
//            deptGrossTotal += emp.ytd;
//            deptFICATotal += emp.payRate;
//            
//            if (lineCountSum != 0) {
//                if (strcmp(currDept, emp.dept) != 0) {
//                    printf("\t\tDepartment Totals: %13.2f %10.2f %10.2f\n", deptGrossTotal, deptFICATotal, deptNetTotal);
//                }
//            }
//            
//            printf("%-6d %-10s %-10s %-8s %10.2f %10.2f %10.2f\n", emp.empNum, emp.fname, emp.lname, emp.dept, emp.ytd, emp.payRate, emp.hours);
//        } else {
//            break;
//        }
//        
//        if (lineCount == LINES_PER_PAGE) {
//            lineCountSum += lineCount;
//            //printf("Linecount: %d LineCountSum: %d", lineCount, lineCountSum);
//            if (lines - lineCountSum == 0) {
//                break;
//            } else {
//                printf("\n\t\tACME\n");
//                printf("%-4s %5s %21s %12s %11s %10s %9s\n\n", "Emp #", "Name", "Dept", "New YTD" , "Gross", "FICA", "Net");
//            }
//            
//            lineCount = 0;
//        }
//        
//    }
    
    
//      OLD STUFF
//    while(dobreak != 1) {
//        //fprintf(outFile, "%-4s %5s %21s %12s %11s %10s %9s\n\n", "Emp #", "Name", "Dept", "New YTD" , "Gross", "FICA", "Net");
//        
//
//        //while(fscanf(inFile, "%d %s %s %s %f %f %f", &emp.empNum, &emp.fname, &emp.lname, &emp.dept, &emp.ytd, &emp.payRate, &emp.hours) != EOF) {
//        for (i = 0; i < LINES_PER_PAGE; i++) {
//            strcpy(prevDept, emp.dept);
//            if (fscanf(inFile, "%d %s %s %s %f %f %f", &emp.empNum, &emp.fname, &emp.lname, &emp.dept, &emp.ytd, &emp.payRate, &emp.hours) != EOF) {
//                
//                if (i == 0) {
//                    printf("\t\tACME\n");
//                    printf("%-4s %5s %21s %12s %11s %10s %9s\n\n", "Emp #", "Name", "Dept", "New YTD" , "Gross", "FICA", "Net");
//                }
//                if (strcmp(prevDept, emp.dept) != 0 && *prevDept != '\0') {
//                    printf("\t\tDepartment Totals: %13.2f %10.2f %10.2f\n", deptGrossTotal, deptFICATotal, deptNetTotal);
//                    deptGrossTotal = 0;
//                    deptFICATotal = 0;
//                    deptNetTotal = 0;
//                }
//                
//                lineCount++;
//                totalGross += emp.ytd;
//                pageGross += emp.ytd;
//                totalFICA += emp.payRate;
//                pageFICA += emp.payRate;
//                deptGrossTotal += emp.ytd;
//                deptFICATotal += emp.payRate;
//                
//                //fprintf(outFile, "%-6d %-10s %-10s %-8s %10.2f %10.2f %10.2f\n", emp.empNum, emp.fname, emp.lname, emp.dept, emp.ytd, emp.payRate, emp.hours);
//                //printf("%-6d %-10s %-10s %-8s %10.2f %10.2f %10.2f\n", emp.empNum, emp.fname, emp.lname, emp.dept, emp.ytd, emp.payRate, emp.hours);
//                printf("%-6d %-10s %-10s %-8s %10.2f %10.2f %10.2f\n", emp.empNum, emp.fname, emp.lname, emp.dept, emp.ytd, emp.payRate, emp.hours);
//                
//                
//            } else {
//                if (i == 0)
//                    skipPageTotals = 1;
//                dobreak = 1;
//                break;
//            }
//            
//        }
//        if (skipPageTotals == 0) {
//            lineCountSum += lineCount;
//            lineCount = 0;
//            printf("\nPage Totals: \t\t\t\t%.2f %.2f\n", pageGross, pageFICA);
//            printf("\t\t\t\tPAGE %d\n\n", ++pageCount);
//            pageGross = 0;
//            pageFICA = 0;
//        }
//    }
    
    
    // Report Summary
//    printf("\t\t\tReport Summary\n");
//    printf("Records processed: %d\n", lineCountSum);
//    printf("Total gross: $%10.2f\n", totalGross);
//    printf("Total FICA:  $%10.2f\n", totalFICA);
//    printf("Total Net:   $%10.2f\n", totalNet);
//    printf("\n\t\tPAGE %d\n\n", ++pageCount);