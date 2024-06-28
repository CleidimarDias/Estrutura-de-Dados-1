#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Fun��o para criptografar uma �nica letra usando a cifra de C�sar
char encrypt_char(char letter, int key) {
    if (isupper(letter)) {
        return 'A' + (letter - 'A' + key) % 26;
    } else if (islower(letter)) {
        return 'a' + (letter - 'a' + key) % 26;
    } else {
        return letter; // Caracteres n�o alfab�ticos n�o s�o modificados
    }
}

// Fun��o para verificar se uma string cont�m apenas d�gitos
bool is_valid_key(char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Fun��o principal
int main(int argc, char *argv[]) {
    // Verificar se o n�mero de argumentos est� correto
    if (argc != 2 || !is_valid_key(argv[1])) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Converter o argumento da chave para um n�mero inteiro
    int key = atoi(argv[1]);

    // Ler a entrada do usu�rio
    printf("plaintext:  ");
    char plaintext[1000]; // Assumindo que o comprimento m�ximo do texto � 1000
    fgets(plaintext, sizeof(plaintext), stdin);

    // Criptografar e imprimir o texto cifrado
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", encrypt_char(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

