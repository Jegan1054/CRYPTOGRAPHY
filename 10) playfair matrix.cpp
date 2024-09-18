#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt(char *message, char *encryptedMessage) {
    int i = 0, k = 0;
    while (message[i] != '\0') {
        char a = toupper(message[i++]);
        char b = toupper(message[i]);
        if (!isalpha(a)) continue;
        if (b == '\0' || !isalpha(b)) {
            b = 'X'; 
            i--;
        } else if (a == b) {
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
    char message[256] = "Must see you over Cadogan West. Coming at once.";
    char encryptedMessage[512];
    encrypt(message, encryptedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);
    return 0;
}
