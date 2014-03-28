#include <stdio.h>
#include <stdlib.h>
//#include "l3.h"
#include <math.h>

const double EPSILON = 0.00000001;

double computeSine(float angle);
int factorial(int x);

int main() {

    //float radius = 7.583;
    //float *surface, *volume;

    //sphere(radius, &surface, &volume);
    //printf("%f %f", surface, volume);
    //printLine();
    printf("Sine of angle 45 is: %g\n", computeSine(45));
    printf("Sine of angle 30 is: %g\n", computeSine(30));
    printf("Sine of angle 0.345 is: %g\n", computeSine(0.345));
    
    FILE *outFile;
    char fileOutName[] = "lab3out.txt";
    outFile = fopen(fileOutName, "w");
    
    fprintf(stdout, "blah blah");
    
    fclose(outFile);
    return 0;
}

double computeSine(float angle) {
    double radian = angle * (M_PI / 180);
    double prevGuess;
    double currGuess = 0;
    int i = 0;

    while(1) {
        prevGuess = currGuess;
        currGuess += (pow(-1, i) / factorial(2 * i + 1)) * (pow(radian, 2 * i + 1));
        if (fabs(currGuess - prevGuess) < EPSILON)
            break;
        i++;
    }
    
    return currGuess;
}

int factorial(int n) {
    int i, x = 1;
    for (i = 2; i <= n; i++) {
        x *= i;
    }
    return x;
}