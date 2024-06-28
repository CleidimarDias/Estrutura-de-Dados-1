#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Função para criptografar uma única letra usando a cifra de César
char encrypt_char(char letter, int key) {
    if (isupper(letter)) {
        return 'A' + (letter - 'A' + key) % 26;
    } else if (islower(letter)) {
        return 'a' + (letter - 'a' + key) % 26;
    } else {
        return letter; // Caracteres não alfabéticos não são modificados
    }
}

// Função para verificar se uma string contém apenas dígitos
bool is_valid_key(char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Função principal
int main(int argc, char *argv[]) {
    // Verificar se o número de argumentos está correto
    if (argc != 2 || !is_valid_key(argv[1])) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Converter o argumento da chave para um número inteiro
    int key = atoi(argv[1]);

    // Ler a entrada do usuário
    printf("plaintext:  ");
    char plaintext[1000]; // Assumindo que o comprimento máximo do texto é 1000
    fgets(plaintext, sizeof(plaintext), stdin);

    // Criptografar e imprimir o texto cifrado
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", encrypt_char(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

