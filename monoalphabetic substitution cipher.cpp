#include <stdio.h>
#include <ctype.h>
#include <string.h>
void monoalphabeticCipher(char *plaintext, char *ciphertextAlphabet) {
    char ch;
    int i = 0;
    char plaintextAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (plaintext[i] != '\0') {
        ch = plaintext[i];
        if (isupper(ch)) {
            for (int j = 0; j < 26; j++) {
                if (plaintextAlphabet[j] == ch) {
                    plaintext[i] = ciphertextAlphabet[j];
                    break;
                }
            }
        }
        else if (islower(ch)) {
            for (int j = 0; j < 26; j++) {
                if (tolower(plaintextAlphabet[j]) == ch) {
                    plaintext[i] = tolower(ciphertextAlphabet[j]);
                    break;
                }
            }
        }       
        i++;
    }
}
int main() {
    char plaintext[100];
    char ciphertextAlphabet[27]; 
    printf("Enter a string to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }
    printf("Enter the 26-letter substitution ciphertext alphabet: ");
    fgets(ciphertextAlphabet, sizeof(ciphertextAlphabet), stdin);
    len = strlen(ciphertextAlphabet);
    if (len > 0 && ciphertextAlphabet[len - 1] == '\n') {
        ciphertextAlphabet[len - 1] = '\0';
    }
    if (strlen(ciphertextAlphabet) != 26) {
        printf("Error: The substitution alphabet must be exactly 26 letters long.\n");
        return 1;
    }
    monoalphabeticCipher(plaintext, ciphertextAlphabet);
    printf("Encrypted text: %s\n", plaintext);    
    return 0;
}
