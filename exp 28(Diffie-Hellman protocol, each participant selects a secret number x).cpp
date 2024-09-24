#include <stdio.h>
#include <math.h>
long long int mod_exp(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long int a, q, x_A, x_B, A, B, key_A, key_B;
    printf("Enter the public base (a): ");
    scanf("%lld", &a);
    
    printf("Enter the public prime modulus (q): ");
    scanf("%lld", &q);
    printf("Enter Alice's private secret (x_A): ");
    scanf("%lld", &x_A);
    
    printf("Enter Bob's private secret (x_B): ");
    scanf("%lld", &x_B);
    A = mod_exp(a, x_A, q);
    B = mod_exp(a, x_B, q);
    key_A = mod_exp(B, x_A, q);  
    key_B = mod_exp(A, x_B, q);  
    
    printf("Alice's computed shared key: %lld\n", key_A);
    printf("Bob's computed shared key: %lld\n", key_B);
    
    if (key_A == key_B) {
        printf("Key exchange successful! Shared secret key: %lld\n", key_A);
    } else {
        printf("Key exchange failed.\n");
    }
    
    return 0;
}

