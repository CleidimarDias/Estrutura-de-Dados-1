#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_coleman_liau(int letters, int words, int sentences);


// Conta o número de letras no texto
int count_letters(string text) {
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (isalpha(text[i])) {
            count++;
        }
    }
    return count;
}

// Conta o número de palavras no texto
int count_words(string text) {
    int count = 1; // começa com 1 porque a primeira palavra começa no início do texto
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (isspace(text[i])) {
            count++;
        }
    }
    return count;
}

// Conta o número de frases no texto
int count_sentences(string text) {
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            count++;
        }
    }
    return count;
}

// Calcula o índice Coleman-Liau
float calculate_coleman_liau(int letters, int words, int sentences) {
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    return 0.0588 * L - 0.296 * S - 15.8;
}


int main(void) {
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float index = calculate_coleman_liau(letters, words, sentences);
    int grade = round(index);

    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", grade);
    }

    return 0;
}



