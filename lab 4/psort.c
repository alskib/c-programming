#include <stdlib.h>
#include "l4.h"

void psort(employee *emp, int ptr[], int numEntries) {
    int i = 0;
    int j = 0;
    employee tempK, tempR;
    
    for (j = 1; j < numEntries; j++) {
        i = j-1;
        tempK = tempR = emp[ptr[j]];
        while (1) {
            if (strcmp(tempK.dept, emp[ptr[i]].dept) >= 0) {
                emp[ptr[i+1]] = tempR;
                break;
            } else {
                emp[ptr[i+1]] = emp[ptr[i]];
                i--;
                if (i < 0) {
                    emp[ptr[0]] = tempR;
                    break;
                }
            }
        }
    }
}