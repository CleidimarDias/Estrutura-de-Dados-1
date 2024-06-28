#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool validate_luhn(long number);
int get_length(long number);
bool check_amex(long number, int length);
bool check_mastercard(long number, int length);
bool check_visa(long number, int length);

int main(void)
{
    // Solicita o número do cartão de crédito ao usuário
    long card_number = get_long("Número: ");

    // Verifica o comprimento do número do cartão
    int length = get_length(card_number);

    // Verifica a validade do número do cartão usando o algoritmo de Luhn
    if (validate_luhn(card_number))
    {
        // Determina o tipo do cartão
        if (check_amex(card_number, length))
        {
            printf("AMEX\n");
        }
        else if (check_mastercard(card_number, length))
        {
            printf("MASTERCARD\n");
        }
        else if (check_visa(card_number, length))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

bool validate_luhn(long number)
{
    int sum = 0;
    bool alternate = false;

    while (number > 0)
    {
        int digit = number % 10;
        number /= 10;

        if (alternate)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;
        alternate = !alternate;
    }

    return (sum % 10) == 0;
}

int get_length(long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    return length;
}

bool check_amex(long number, int length)
{
    return length == 15 && (number / 10000000000000 == 34 || number / 10000000000000 == 37);
}

bool check_mastercard(long number, int length)
{
    int start = number / 100000000000000;
    return length == 16 && (start >= 51 && start <= 55);
}

bool check_visa(long number, int length)
{
    int start = number / (long)pow(10, length - 1);
    return (length == 13 || length == 16) && start == 4;
}

