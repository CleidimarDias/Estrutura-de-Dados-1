#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    float reais;
    int centavos, moedas = 0;

    // Solicita ao usuário uma quantia válida não negativa
    do {
        reais = get_float("Dinheiro devido: ");
    } while (reais < 0);

    // Converte reais para centavos, arredondando corretamente
    centavos = round(reais * 100);

    // Calcula o número mínimo de moedas
    moedas += centavos / 25;     // Quantidade de moedas de 25 centavos
    centavos %= 25;              // Restante em centavos

    moedas += centavos / 10;     // Quantidade de moedas de 10 centavos
    centavos %= 10;              // Restante em centavos

    moedas += centavos / 5;      // Quantidade de moedas de 5 centavos
    centavos %= 5;               // Restante em centavos

    moedas += centavos / 1;      // Quantidade de moedas de 1 centavo
    centavos %= 1;               // Restante em centavos (deve ser 0)

    // Imprime o número mínimo de moedas
    printf("%d\n", moedas);

    return 0;
}

