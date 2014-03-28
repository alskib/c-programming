#include <stdlib.h>
#include "l4.h"

void psort(employee *emp, int ptr[], int numEntries) {
    int i, j;
    for (i = 1; i < numEntries; i++) {
        for (j = i; j > 0 && strcmp(emp[ptr[j-1]].dept, emp[ptr[j]].dept) > 1; j--) {
            employee temp = emp[ptr[j]];
            emp[ptr[j]] = emp[ptr[j-1]];
            emp[ptr[j-1]] = temp;
        }
    }
}
