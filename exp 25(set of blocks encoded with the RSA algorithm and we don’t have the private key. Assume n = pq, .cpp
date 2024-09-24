#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {
    int n = 33; 
    int m = 21; 
    int d = gcd(n, m);
    if (d > 1 && d < n) {
        printf("Found a non-trivial factor of n: %d\n", d);
        printf("The other factor is: %d\n", n / d);
    } else {
        printf("No common factor found or the factor is trivial.\n");
    }
    return 0;
}

