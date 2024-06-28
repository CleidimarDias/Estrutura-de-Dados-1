#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_LENGTH 26

// Fun��o para cifrar o texto
void encrypt_text(const char *plain_text, const char *key);

int main(int argc, char *argv[]) {
    // Verifica se foi fornecido um argumento (a chave)
    if (argc != 2) {
        printf("Uso: %s chave_de_substituicao\n", argv[0]);
        return 1;
    }

    // Verifica se a chave tem exatamente 26 caracteres
    char *key = argv[1];
    int key_length = strlen(key);
    if (key_length != ALPHABET_LENGTH) {
        printf("A chave deve conter 26 caracteres.\n");
        return 1;
    }

    // Verifica se todos os caracteres da chave s�o alfab�ticos e �nicos
    int freq[ALPHABET_LENGTH] = {0};
    for (int i = 0; i < key_length; i++) {
        if (!isalpha(key[i])) {
            printf("A chave deve conter apenas caracteres alfab�ticos.\n");
            return 1;
        }
        int index = toupper(key[i]) - 'A';
        if (freq[index] > 0) {
            printf("A chave deve conter cada letra exatamente uma vez.\n");
            return 1;
        }
        freq[index]++;
    }

    // L� o texto simples do usu�rio
    char plain_text[1000];  // Tamanho arbitr�rio, ajust�vel conforme necessidade
    printf("texto simples: ");
    fgets(plain_text, sizeof(plain_text), stdin);

    // Remove a quebra de linha do final da entrada
    plain_text[strcspn(plain_text, "\n")] = '\0';

    // Chama a fun��o para criptografar o texto
    encrypt_text(plain_text, key);

    return 0;
}

void encrypt_text(const char *plain_text, const char *key) {
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain_text); i < n; i++) {
        char c = plain_text[i];
        if (isalpha(c)) {
            char plain_char = islower(c) ? 'a' : 'A';
            int index = toupper(c) - plain_char;
            char encrypted_char = islower(key[index]) ? tolower(key[index]) : toupper(key[index]);
            printf("%c", encrypted_char);
        } else {
            printf("%c", c);  // Mant�m caracteres n�o alfab�ticos
        }
    }
    printf("\n");
}

