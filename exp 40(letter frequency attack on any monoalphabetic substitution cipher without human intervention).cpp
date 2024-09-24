#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

void frequency_analysis(const char *ciphertext, int *freq);
void generate_plaintexts(const char *ciphertext, const int *freq, char plaintexts[MAX_PLAINTEXTS][256]);
void print_plaintexts(char plaintexts[MAX_PLAINTEXTS][256], int count);

int main() {
    char ciphertext[256];
    int freq[ALPHABET_SIZE] = {0};
    char plaintexts[MAX_PLAINTEXTS][256];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    frequency_analysis(ciphertext, freq);
    generate_plaintexts(ciphertext, freq, plaintexts);
    print_plaintexts(plaintexts, MAX_PLAINTEXTS);

    return 0;
}

void frequency_analysis(const char *ciphertext, int *freq) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        char ch = tolower(ciphertext[i]);
        if (ch >= 'a' && ch <= 'z') {
            freq[ch - 'a']++;
        }
    }
}

void generate_plaintexts(const char *ciphertext, const int *freq, char plaintexts[MAX_PLAINTEXTS][256]) {
    const char *common_letters = "etaoinshrdlu";
    char substitution[ALPHABET_SIZE];
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[i] = (i < strlen(common_letters)) ? common_letters[i] : ' ';
    }

    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        strcpy(plaintexts[i], ciphertext);
        for (int j = 0; j < strlen(ciphertext); j++) {
            char ch = tolower(ciphertext[j]);
            if (ch >= 'a' && ch <= 'z') {
                plaintexts[i][j] = substitution[ch - 'a'];
            }
        }
    }
}

void print_plaintexts(char plaintexts[MAX_PLAINTEXTS][256], int count) {
    printf("Possible plaintexts:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, plaintexts[i]);
    }
}

