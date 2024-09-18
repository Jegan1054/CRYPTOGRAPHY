#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 512
#define TOP_N 10
void calculate_frequency(char *ciphertext, int frequency[ALPHABET_SIZE]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}
void sort_frequencies(int frequency[ALPHABET_SIZE], int shifts[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        shifts[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (frequency[shifts[j]] < frequency[shifts[j + 1]]) {
                int temp_freq = frequency[shifts[j]];
                frequency[shifts[j]] = frequency[shifts[j + 1]];
                frequency[shifts[j + 1]] = temp_freq;
                int temp_shift = shifts[j];
                shifts[j] = shifts[j + 1];
                shifts[j + 1] = temp_shift;
            }
        }
    }
}
void decrypt(char *ciphertext, int shift, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0'; 
}
int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int frequency[ALPHABET_SIZE] = {0};
    int shifts[ALPHABET_SIZE];
    char possible_plaintexts[TOP_N][MAX_TEXT_LENGTH];
    
    printf("Enter the ciphertext (in uppercase): ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    calculate_frequency(ciphertext, frequency);
    sort_frequencies(frequency, shifts);

    for (int i = 0; i < TOP_N; i++) {
        int shift = shifts[i];
        decrypt(ciphertext, shift, possible_plaintexts[i]);
    }
    printf("\nTop %d Possible Plaintexts:\n", TOP_N);
    for (int i = 0; i < TOP_N; i++) {
        printf("Shift %d: %s\n", shifts[i], possible_plaintexts[i]);
    }

    return 0;
}
