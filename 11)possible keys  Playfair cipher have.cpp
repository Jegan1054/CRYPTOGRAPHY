#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
int main() {
    int letters = 26; 
    int choose = 25;  
    unsigned long long fact_25 = factorial(25);
    unsigned long long total_keys = letters * fact_25;
    double log2_total_keys = log2(total_keys);
    unsigned long long unique_keys = total_keys / 2;
    double log2_unique_keys = log2(unique_keys);
    printf("Total possible keys: %llu\n", total_keys);
    printf("Approximate power of 2 for total possible keys: 2^%.1f\n", log2_total_keys);
    printf("Estimated unique keys: %llu\n", unique_keys);
    printf("Approximate power of 2 for unique keys: 2^%.1f\n", log2_unique_keys);
    return 0;
}
