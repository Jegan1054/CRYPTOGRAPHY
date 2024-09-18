#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define SIZE 5
char matrix[SIZE][SIZE];
void createMatrix(char *key) {
    int used[26] = {0};
    int k = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!used[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
            }
        }
    }
}
void encrypt(char *message, char *encryptedMessage) {
    int i = 0, k = 0;
    while (message[i] != '\0') {
        char a = toupper(message[i++]);
        char b = toupper(message[i]);
        if (a == b || b == '\0') {
            b = 'X'; 
            i--;
        }
        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);
        if (row1 == row2) {
            encryptedMessage[k++] = matrix[row1][(col1 + 1) % SIZE];
            encryptedMessage[k++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encryptedMessage[k++] = matrix[(row1 + 1) % SIZE][col1];
            encryptedMessage[k++] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            encryptedMessage[k++] = matrix[row1][col2];
            encryptedMessage[k++] = matrix[row2][col1];
        }
        i++;
    }
    encryptedMessage[k] = '\0';
}
int main() {
    char key[MAX];
    char message[MAX];
    char encryptedMessage[MAX];
    printf("Enter the key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = '\0'; 
    createMatrix(key);
    printf("Enter the message to encrypt: ");
    fgets(message, MAX, stdin);
    message[strcspn(message, "\n")] = '\0'; 
    encrypt(message, encryptedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);
    return 0;
}