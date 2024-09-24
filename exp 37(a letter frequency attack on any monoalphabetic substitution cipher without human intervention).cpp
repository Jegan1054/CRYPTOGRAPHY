#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000
#define MAX_PLAINTEXTS 10

void calculateFrequency(const char *text, int frequency[ALPHABET_SIZE]) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = tolower(text[i]);
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }
}

void sortByFrequency(int frequency[ALPHABET_SIZE], char letters[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = 'a' + i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[i] < frequency[j]) {
                int tempFreq = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = tempFreq;

                char tempLetter = letters[i];
                letters[i] = letters[j];
                letters[j] = tempLetter;
            }
        }
    }
}

void generatePlaintexts(const char *ciphertext, char possiblePlaintexts[MAX_PLAINTEXTS][MAX_CIPHERTEXT_LENGTH], int *count) {
    int frequency[ALPHABET_SIZE];
    char letters[ALPHABET_SIZE];

    calculateFrequency(ciphertext, frequency);
    sortByFrequency(frequency, letters);

    const char *frequencyOrder = "etaoinshrdlcumwfgypbvkjxqz";
    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        if (i >= ALPHABET_SIZE) break;
        char mapping[ALPHABET_SIZE] = {0};
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[letters[j] - 'a'] = frequencyOrder[i];
        }

        for (int k = 0; ciphertext[k] != '\0'; k++) {
            char ch = tolower(ciphertext[k]);
            if (ch >= 'a' && ch <= 'z') {
                possiblePlaintexts[i][k] = mapping[ch - 'a'];
            } else {
                possiblePlaintexts[i][k] = ciphertext[k];
            }
        }
        possiblePlaintexts[i][strlen(ciphertext)] = '\0';
    }
    *count = MAX_PLAINTEXTS;
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    char possiblePlaintexts[MAX_PLAINTEXTS][MAX_CIPHERTEXT_LENGTH];
    int count;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    generatePlaintexts(ciphertext, possiblePlaintexts, &count);

    printf("Top possible plaintexts:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, possiblePlaintexts[i]);
    }

    return 0;
}

