#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int extended_euclidean(int a, int m, int* x, int* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }
    int x1, y1;
    int gcd = extended_euclidean(m % a, a, &x1, &y1);

    *x = y1 - (m / a) * x1;
    *y = x1;
    return gcd;
}
int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_euclidean(e, phi, &x, &y);
    if (g != 1) {
        return -1;
    } else {
        return (x % phi + phi) % phi;
    }
}
int main() {
    int e = 31;
    int n = 3599;
    int p = 59; 
    int q = 61;
    int phi = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("No modular inverse found.\n");
    } else {
        printf("Private key (d) is: %d\n", d);
    }
    return 0;
}
