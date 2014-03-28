#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char lname[15];
    char fname[15];
    char dept[20];
    float payRate;
    char eyeColor[10];
} employee;

void sort(employee *emp, int numEntries);
void psort(employee *emp, int ptr[], int numEntries);
void arithmeticSort(employee *emp, int numEntries);
void printData(employee *emp, int numEntries);
void printDataPtr(employee *emp, int ptr[], int numEntries);
void printDataArith(employee *emp, int numEntries);
void copyStruct(employee *emp1, employee *emp2, int numEntries);

int main() {

    FILE *inFile;
    char fileInName[] = "data.txt";
    //FILE *outFile;
    //char fileOutName[] = "lab4out.txt";
    
    inFile = fopen(fileInName, "r");
    //outFile = fopen(fileOutName, "w");
    
    char a, b, c, d;
    float o;
    int numEntries = 0;
    while(fscanf(inFile, "%s %s %s %f %s", &a, &b, &c, &o, &d) != EOF)
        numEntries++;
    rewind(inFile);

    employee empUnsorted[numEntries], emp[numEntries];
    int ptrArray[numEntries];
    int i;
    
    printf("INITIAL SCAN (UNSORTED DATA)\n");
    for (i = 0; i < numEntries; i++) {
        fscanf(inFile, "%s %s %s %f %s", empUnsorted[i].lname, empUnsorted[i].fname, empUnsorted[i].dept, &empUnsorted[i].payRate, empUnsorted[i].eyeColor);
        printf("%-10s %-10s %-20s %6.2f\t%-8s\n", empUnsorted[i].lname, empUnsorted[i].fname, empUnsorted[i].dept, empUnsorted[i].payRate, empUnsorted[i].eyeColor);
        ptrArray[i] = i;
    }

    // emp will become the working set to be sorted while empUnsorted will be kept for pointer and relative addressing sorts so the file won't have to be read in again
    copyStruct(emp, empUnsorted, numEntries);
    
    // Perform normal sort
    sort(emp, numEntries);
    printf("\nSORTED DATA USING NORMAL SORT\n");
    printData(emp, numEntries);
    
    // Initialize emp with unsorted data
    copyStruct(emp, empUnsorted, numEntries);
    
    // Perform pointer sort
    psort(emp, ptrArray, numEntries);
    printf("\nSORTED DATA USING POINTER SORT\n");
    printDataPtr(emp, ptrArray, numEntries);
    
    // Initialize emp with unsorted data
    copyStruct(emp, empUnsorted, numEntries);
    
    // Perform arithmetic sort
    arithmeticSort(emp, numEntries);
    printf("\nSORTED DATA USING RELATIVE ADDRESSING SORT\n");
    printDataArith(emp, numEntries);
    
    //fclose(inFile);
    
    return 0;
}

void sort(employee *emp, int numEntries) {   
    int i = 0;
    int j = 0;
    employee tempK, tempR;
    
    for (j = 1; j < numEntries; j++) {
        i = j-1;
        tempK = tempR = emp[j];
        while (1) {
            if (strcmp(tempK.dept, emp[i].dept) >= 0) {
                emp[i+1] = tempR;
                break;
            } else {
                emp[i+1] = emp[i];
                i--;
                if (i < 0) {
                    emp[0] = tempR;
                    break;
                }
            }
        }
    }
}

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

void printData(employee *emp, int numEntries) {
    int i;
    for (i = 0; i < numEntries; i++) {
        printf("%-10s %-10s %-20s %6.2f\t%-8s\n", emp[i].lname, emp[i].fname, emp[i].dept, emp[i].payRate, emp[i].eyeColor);
    }
}

void printDataPtr(employee *emp, int ptr[], int numEntries) {
    int i;
    for (i = 0; i < numEntries; i++) {
        printf("%-10s %-10s %-20s %6.2f\t%-8s\n", emp[ptr[i]].lname, emp[ptr[i]].fname, emp[ptr[i]].dept, emp[ptr[i]].payRate, emp[ptr[i]].eyeColor);
    }
}

void printDataArith(employee *emp, int numEntries) {
    int i;
    for (i = 0; i < numEntries; i++) {
        printf("%-10s %-10s %-20s %6.2f\t%-8s\n", (emp + i)->lname, (emp + i)->fname, (emp + i)->dept, (emp + i)->payRate, (emp + i)->eyeColor);
    }
}

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