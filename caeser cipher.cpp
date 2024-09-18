#include <stdio.h>
#include <ctype.h>
void caesarCipher(char *text, int k) {
    char ch;
    int i = 0;
    while (text[i] != '\0') {
        ch = text[i];
        if (isupper(ch)) {	
            text[i] = (ch - 'A' + k) % 26 + 'A';
        }
        else if (islower(ch)) {
            text[i] = (ch - 'a' + k) % 26 + 'a';
        }
        i++;
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }
    caesarCipher(text, k);
    printf("Encrypted text: %s\n", text);
    return 0;
}