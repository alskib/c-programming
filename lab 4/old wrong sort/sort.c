#include <stdlib.h>
#include <stdio.h>
#include "l4.h"

void sort(employee *emp, int numEntries) {   
    int i, j;
    for (i = 1; i < numEntries; i++) {
        for (j = i; j > 0 && strcmp(emp[j-1].dept, emp[j].dept) > 1; j--) {
            employee temp = emp[j];
            emp[j] = emp[j-1];
            emp[j-1] = temp;
        }
    }
}