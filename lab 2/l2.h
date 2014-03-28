#ifndef L2_H
#define L2_H

#include <stdio.h>

typedef struct {
    int empNum;
    char lname[15];
    char fname[15];
    char dept[8];
    float ytd;
    float payRate;
    float hours;
} employee;

extern double calcFICA(float ytd, float gross, double FICARate, double FICALimit);
extern void newPage(int *pageCount, int *lineCount, double *pageGross, double *pageFICA, double *pageNet, FILE *outFile);
extern double calcGross(double hours, double rate);
extern void prettyPrint(char string[], float value);

#endif /* L2_H */