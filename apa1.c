#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAXIMO 10

// Estrutura para representar um aluno
struct aluno {
    int matricula;
    float notas[2];
};

// Estrutura para a lista estática de alunos
struct lista {
    int qtd; // Quantidade atual de elementos na lista
    struct aluno dados[MAXIMO]; // Array para armazenar os alunos
};

typedef struct lista Lista;

// Função para criar uma lista vazia
Lista* cria_lista() {
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

// Função para liberar a lista
void libera_lista(Lista* li) {
    free(li);
    printf("Destruindo a lista!");
}

// Função para retornar o tamanho da lista
int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1; // Lista não existe
    else
        return li->qtd;
}

// Função para verificar se a lista está cheia
int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1; 
    return (li->qtd == MAXIMO);
}

// Função para verificar se a lista está vazia
int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1; 
    return (li->qtd == 0);
}

// Função para inserir um aluno no início da lista
int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0; 

    // Desloca os elementos para a direita
    for (int i = li->qtd; i > 0; i--)
        li->dados[i] = li->dados[i - 1];

    // Insere o novo aluno no início
    li->dados[0] = al;
    li->qtd++;
    return 1; 
}

// Função para inserir um aluno no final da lista
int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0; 

    // Insere o novo aluno no final
    li->dados[li->qtd] = al;
    li->qtd++;
    return 1; 
}

// Função para inserir um aluno de forma ordenada na lista (por matrícula)
int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0; 

    int i = 0;
    while (i < li->qtd && li->dados[i].matricula < al.matricula)
        i++;

    // Desloca os elementos para a direita
    for (int j = li->qtd; j > i; j--)
        li->dados[j] = li->dados[j - 1];

    // Insere o novo aluno na posição correta
    li->dados[i] = al;
    li->qtd++;
    return 1; 
}

// Função para remover o primeiro elemento da lista
int remove_lista_inicio(Lista* li) {
    if (li == NULL || lista_vazia(li))
        return 0; // Falha na remoção

    // Desloca os elementos para a esquerda
    for (int i = 0; i < li->qtd - 1; i++)
        li->dados[i] = li->dados[i + 1];

    li->qtd--;
    return 1; 
}

// Função para remover o último elemento da lista
int remove_lista_final(Lista* li) {
    if (li == NULL || lista_vazia(li))
        return 0; 

    li->qtd--;
    return 1;
}

// Função para remover um aluno da lista por matrícula
int remove_lista(Lista* li, int mat) {
    if (li == NULL || lista_vazia(li))
        return 0;

    int pos = -1;
    for (int i = 0; i < li->qtd; i++) {
        if (li->dados[i].matricula == mat) {
            pos = i;
            break;
        }
    }

    if (pos == -1)
        return 0; 

    // Desloca os elementos para a esquerda
    for (int i = pos; i < li->qtd - 1; i++)
        li->dados[i] = li->dados[i + 1];

    li->qtd--;
    return 1;
}

// Função para buscar a posição de uma matrícula na lista
int busca_posicao_matricula(Lista* li, int mat) {
    if (li == NULL || lista_vazia(li))
        return -1; // Lista vazia

    for (int i = 0; i < li->qtd; i++) {
        if (li->dados[i].matricula == mat) {
            return i + 1; // Retorna a posição (começando de 1)
        }
    }

    return -1; // Matrícula não encontrada na lista
}

// Função para imprimir os elementos da lista em ordem decrescente de matrícula
void imprime_lista_decrescente(Lista* li) {
    if (li == NULL || lista_vazia(li)) {
        printf("Lista vazia!\n");
        return;
    }

    for (int i = li->qtd - 1; i >= 0; i--) {
        struct aluno al = li->dados[i];
        float media = ((al.notas[0]*4 + al.notas[1]*6) / 10.0);
        printf("Matrícula: %d, N1: %.1f, N2: %.1f, Média: %.1f\n", 
               al.matricula, al.notas[0], al.notas[1], media);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    float notas[][2] = {{8.0, 9.0}, {5.0, 6.0}, {8.0, 7.0}, {4.0, 9.0}, 
                        {2.0, 6.0}, {7.5, 6.0}, {3.0, 5.0}, {2.0, 1.0}, 
                        {9.0, 8.0}, {8.0, 6.0}};
    int matriculas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


    Lista *li = cria_lista();
    printf("Lista vazia!\nInserindo elementos na lista!\n");
    for (int i = 0; i < 10; i++) {
        struct aluno al;
        al.matricula = matriculas[i];
        al.notas[0] = notas[i][0];
        al.notas[1] = notas[i][1];
        insere_lista_ordenada(li, al);
    }
    printf("Foram inseridos %d elementos na lista!\n", tamanho_lista(li));
    printf("Elementos da lista com média:\n");

    imprime_lista_decrescente(li);


    printf("Inserindo a matrícula 11!\n");
    if (!insere_lista_ordenada(li, (struct aluno){11, {10.0, 10.0}}))
        printf("Lista cheia! A lista contem %d elementos\n", tamanho_lista(li));
    else
        printf("Elemento inserido com sucesso!\n");


    printf("\nRemovendo o primeiro e último elemento da lista!\n");
    remove_lista_inicio(li);
    remove_lista_final(li);
    printf("Lista após a remoção dos dois elementos! A lista contém %d elementos\n", tamanho_lista(li));


    imprime_lista_decrescente(li);
    printf("\n");
    
    struct aluno al11 = {11, {10.0, 10.0}};
    insere_lista_inicio(li, al11);
    printf("Inserindo a matrícula %d!\n", al11.matricula);
    printf("\n");
    
    printf("A lista contém %d elementos\n", tamanho_lista(li));
    
    imprime_lista_decrescente(li);
    

    int pos = busca_posicao_matricula(li, 5);
    if (pos != -1)
        printf("\nBuscando a posição da matrícula 5 na lista!\nA matrícula 5 está na posição %d da lista!\n", pos - 1);
    else
        printf("\nMatrícula 5 não encontrada na lista!\n");

    // Liberando a lista
    libera_lista(li);

}
