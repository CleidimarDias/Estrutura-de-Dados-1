#include <stdio.h>

int main(void) {
    int altura;

    // Solicita a altura da pirâmide ao usuário, garantindo que esteja entre 1 e 8
    do {
        printf("Altura: ");
        scanf("%d", &altura);

        // Limpa a entrada padrão em caso de entrada não numérica
        while (getchar() != '\n');
        
    } while (altura < 1 || altura > 8);

    // Gera as pirâmides duplas
    for (int i = 1; i <= altura; i++) {
        // Imprime os espaços em branco
        for (int j = 0; j < altura - i; j++) {
            printf(" ");
        }
        // Imprime os hashes da primeira pirâmide
        for (int k = 0; k < i; k++) {
            printf("#");
        }
        // Imprime a lacuna
        printf("  ");
        // Imprime os hashes da segunda pirâmide
        for (int k = 0; k < i; k++) {
            printf("#");
        }
        // Move para a próxima linha
        printf("\n");
    }

    return 0;
}
