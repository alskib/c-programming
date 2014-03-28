#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "l4.h"

int main() {
    FILE *inFile;
    char fileInName[] = "data.txt";
    FILE *outFile;
    char fileOutName[] = "l4.B.txt";

    inFile = fopen(fileInName, "r");
    outFile = fopen(fileOutName, "w");

    char a, b, c, d;
    float o;
    int numEntries = 0;
    while(fscanf(inFile, "%s %s %s %f %s", &a, &b, &c, &o, &d) != EOF)
        numEntries++;
    rewind(inFile);

    employee empUnsorted[numEntries], emp[numEntries];
    int ptrArray[numEntries];
    int i;

    fprintf(outFile, "INITIAL SCAN (UNSORTED DATA)\n");
    for (i = 0; i < numEntries; i++) {
        fscanf(inFile, "%s %s %s %f %s", empUnsorted[i].lname, empUnsorted[i].fname, empUnsorted[i].dept, &empUnsorted[i].payRate, empUnsorted[i].eyeColor);
        fprintf(outFile, "%-10s %-10s %-20s %6.2f\t%-8s\n", empUnsorted[i].lname, empUnsorted[i].fname, empUnsorted[i].dept, empUnsorted[i].payRate, empUnsorted[i].eyeColor);
        ptrArray[i] = i;
    }

    // emp will become the working set to be sorted while empUnsorted will be kept for pointer sort so the file won't have to be read in again
    copyStruct(emp, empUnsorted, numEntries);

    // Perform normal sort
    sort(empUnsorted, numEntries);
    fprintf(outFile, "\nSORTED DATA USING NORMAL SORT\n");
    printData(empUnsorted, numEntries, outFile);

    // Initialize emp with unsorted data
    copyStruct(emp, empUnsorted, numEntries);

    // Perform pointer sort
    psort(emp, ptrArray, numEntries);
    fprintf(outFile, "\nSORTED DATA USING POINTER SORT\n");
    printDataPtr(emp, ptrArray, numEntries, outFile);

    // Initialize emp with unsorted data
    copyStruct(emp, empUnsorted, numEntries);

    // Perform arithmetic sort
    arithmeticSort(emp, numEntries);
    fprintf(outFile, "\nSORTED DATA USING RELATIVE ADDRESSING SORT\n");
    printDataArith(emp, numEntries, outFile);

    fclose(inFile);
    fclose(outFile);

    printf("Program execution complete. Terminating.\n");

    return 0;
}
