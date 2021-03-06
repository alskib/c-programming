#include <stdlib.h>
#include "l4.h"

void printData(employee *emp, int numEntries, FILE *outFile) {
    int i;
    for (i = 0; i < numEntries; i++) {
        fprintf(outFile, "%-10s %-10s %-20s %6.2f\t%-8s\n", emp[i].lname, emp[i].fname, emp[i].dept, emp[i].payRate, emp[i].eyeColor);
    }
}