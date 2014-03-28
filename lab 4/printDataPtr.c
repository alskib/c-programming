#include <stdlib.h>
#include <stdio.h>
#include "l4.h"

void printDataPtr(employee *emp, int ptr[], int numEntries, FILE *outFile) {
    int i;
    for (i = 0; i < numEntries; i++) {
        fprintf(outFile, "%-10s %-10s %-20s %6.2f\t%-8s\n", emp[ptr[i]].lname, emp[ptr[i]].fname, emp[ptr[i]].dept, emp[ptr[i]].payRate, emp[ptr[i]].eyeColor);
    }
}