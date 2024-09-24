#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LEN 1000
#define ALPHABET_SIZE 26
double englishFreq[ALPHABET_SIZE] = {
    8.167,  
    1.492,  
    2.782,  
    4.253, 
    12.702, 
    2.228,  
    2.015,  
    6.094,  
    6.966, 
    0.153,  
    0.772,  
    4.025,  
    2.406,  
    6.749,  
    7.507,  
    1.929,  
    0.095,  
    5.987,  
    6.327,  
    9.056, 
    2.758,  
    0.978, 
    2.360,  
    0.150,  
    1.974, 
    0.074   
};
void countFrequencies(const char *text, double freq[ALPHABET_SIZE]) {
    int count[ALPHABET_SIZE] = {0};
    int totalLetters = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[toupper(text[i]) - 'A']++;
            totalLetters++;
        }
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / totalLetters * 100.0;
    }
}
void decryptWithShift(const char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  
}
double calculateChiSquared(double observed[ALPHABET_SIZE], double expected[ALPHABET_SIZE]) {
    double chiSquared = 0.0;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (expected[i] > 0) {
            double diff = observed[i] - expected[i];
            chiSquared += (diff * diff) / expected[i];
        }
    }
    
    return chiSquared;
}
void rankDecryptionPossibilities(const char *ciphertext, int topN) {
    double ciphertextFreq[ALPHABET_SIZE];
    char possiblePlaintext[MAX_TEXT_LEN];
    double chiSquaredValues[ALPHABET_SIZE];
    countFrequencies(ciphertext, ciphertextFreq);
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        double shiftedFreq[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            shiftedFreq[i] = ciphertextFreq[(i + shift) % ALPHABET_SIZE];
        }
        chiSquaredValues[shift] = calculateChiSquared(shiftedFreq, englishFreq);
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (chiSquaredValues[i] > chiSquaredValues[j]) {
                double temp = chiSquaredValues[i];
                chiSquaredValues[i] = chiSquaredValues[j];
                chiSquaredValues[j] = temp;
            }
        }
    }
    printf("Top %d possible plaintexts:\n", topN);
    for (int rank = 0; rank < topN && rank < ALPHABET_SIZE; rank++) {
        decryptWithShift(ciphertext, possiblePlaintext, rank);
        printf("Shift %2d: %s\n", rank, possiblePlaintext);
    }
}
int main() {
    char ciphertext[MAX_TEXT_LEN];
    int topN;
    printf("Enter ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LEN, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  
    printf("How many top possible plaintexts to display? ");
    scanf("%d", &topN);
    rankDecryptionPossibilities(ciphertext, topN);
    return 0;
}
