#include <stdlib.h>
#include "l4.h"

void arithmeticSort(employee *emp, int numEntries) {
    int i = 0;
    int j = 0;
    employee tempK, tempR;
    
    for (j = 1; j < numEntries; j++) {
        i = j-1;
        tempK = tempR = *(emp + j);
        while (1) {
            if (strcmp(tempK.dept, (emp + i)->dept) >= 0) {
                *(emp + (i+1)) = tempR;
                break;
            } else {
                *(emp + (i+1)) = *(emp + i);
                i--;
                if (i < 0) {
                    *(emp) = tempR;
                    break;
                }
            }
        }
    }
}