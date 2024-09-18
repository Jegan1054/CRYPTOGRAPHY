#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 512
#define TOP_N 10
char english_freq[ALPHABET_SIZE + 1] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void calculate_frequency(char *ciphertext, int frequency[ALPHABET_SIZE]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

void generate_substitution_key(int frequency[ALPHABET_SIZE], char *key) {
    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (frequency[sorted_indices[j]] < frequency[sorted_indices[j + 1]]) {
                int temp_freq = frequency[sorted_indices[j]];
                frequency[sorted_indices[j]] = frequency[sorted_indices[j + 1]];
                frequency[sorted_indices[j + 1]] = temp_freq;
                int temp_idx = sorted_indices[j];
                sorted_indices[j] = sorted_indices[j + 1];
                sorted_indices[j + 1] = temp_idx;
            }
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[sorted_indices[i]] = english_freq[i];
    }
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int frequency[ALPHABET_SIZE] = {0};
    char key[ALPHABET_SIZE] = {0};
    char possible_plaintexts[TOP_N][MAX_TEXT_LENGTH];

    printf("Enter the ciphertext (in uppercase): ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    calculate_frequency(ciphertext, frequency);
    generate_substitution_key(frequency, key);

    for (int i = 0; i < TOP_N; i++) {
        decrypt(ciphertext, key, possible_plaintexts[i]);
        char temp = key[0];
        for (int j = 0; j < ALPHABET_SIZE - 1; j++) {
            key[j] = key[j + 1];
        }
        key[ALPHABET_SIZE - 1] = temp;
    }

    printf("\nTop %d Possible Plaintexts:\n", TOP_N);
    for (int i = 0; i < TOP_N; i++) {
        printf("%d: %s\n", i + 1, possible_plaintexts[i]);
    }

    return 0;
}
