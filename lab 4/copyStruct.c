#include <stdlib.h>
#include "l4.h"

void copyStruct(employee *empDest, employee *empSrc, int numEntries) {
    int i;
    for (i = 0; i < numEntries; i++) {
        strcpy(empDest[i].lname, empSrc[i].lname);
        strcpy(empDest[i].fname, empSrc[i].fname);
        strcpy(empDest[i].dept, empSrc[i].dept);
        empDest[i].payRate = empSrc[i].payRate;
        strcpy(empDest[i].eyeColor, empSrc[i].eyeColor);
    }
}
