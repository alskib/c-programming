#include <stdio.h>

int gcd(int m, int n);
int mul(int m, int n);
int div(int m, int n);
int exp(int m, int n);

int main() {

    printf("GCD: %d\n", gcd(25, 15));
    printf("GCD: %d\n", gcd(27, 81));
    printf("GCD: %d\n", gcd(9, 15));
    printf("GCD: %d\n", gcd(625, 300));
    printf("GCD: %d\n", gcd(625, 0));
    printf("GCD: %d\n\n", gcd(7, 15));
    
    printf("Mul: %d\n", mul(77, 13));
    printf("Mul: %d\n", mul(5, 25));
    printf("Mul: %d\n", mul(17, 1));
    printf("Mul: %d\n\n", mul(256, 0));
    
    printf("Exp: %d\n", exp(10, 0));
    printf("Exp: %d\n", exp(3, 5));
    printf("Exp: %d\n", exp(5, 4));
    printf("Exp: %d\n\n", exp(763, 0));
    
    printf("Div: %d\n", div(25, 4));
    printf("Div: %d\n", div(25, 5));
    printf("Div: %d\n", div(0, 32));
    printf("Div: %d\n", div(25, 4));
    printf("Div: %d\n", div(40, 80));
    
    return 0;
}

int gcd(int m, int n) {
    // C = A % B;
    //   = A - B * (A / B);
    return (n != 0) ? gcd(n, m - mul(n, div(m, n))) : m;
}

int mul(int m, int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return m;
    return m + mul(m, --n);
}

int div(int m, int n) {
    if (n == 0)
        exit(1);
    if (n == 1)
        return m;
    return (m >= n) ? 1 + div(m - n, n) : 0;
}

int exp(int m, int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return m;
    return mul(m, exp(m, --n));
}