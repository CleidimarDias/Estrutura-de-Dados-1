#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Defini��o da estrutura aluno
struct aluno {
    int matricula;
    float n1, n2, media;
};

// Defini��o da estrutura elemento
struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

// Defini��o do tipo Lista
typedef Elem* Lista;

// Prot�tipos das fun��es de manipula��o da lista
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

// Fun��o principal
int main() {
    setlocale(LC_ALL, "");

    Lista* li = cria_lista();

    // Dados de entrada
    float notas[10][2] = {{8.0, 9.0}, {5.0, 6.0}, {8.0, 7.0}, {4.0, 9.0}, {2.0, 6.0}, {7.5, 6.0}, {3.0, 5.0}, {2.0, 1.0}, {9.0, 8.0}, {8.0, 6.0}};
    int matriculas[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Lista vazia!\nInserindo elementos na lista!\n");

    // Inserindo elementos na lista
    int i;
    for (i = 9; i >= 0; i--) { // Inserir de tr�s para frente para come�ar com a matr�cula 10
        struct aluno al;
        al.matricula = matriculas[i];
        al.n1 = notas[i][0];
        al.n2 = notas[i][1];
        al.media = (((al.n1) *2) + ((al.n2)*3))  / 5;
        insere_lista_final(li, al);
    }

    printf("Foram inseridos 10 elementos na lista!\n");

    // Exibindo os elementos da lista
    printf("Elementos da lista com m�dia:\n");
    Elem* no = *li;
    while (no != NULL) {
        printf("Matr�cula: %d, N1: %.1f, N2: %.1f, M�dia: %.1f\n", no->dados.matricula, no->dados.n1, no->dados.n2, no->dados.media);
        no = no->prox;
    }

    // Inserindo um elemento adicional
    printf("\nInserindo a matr�cula 11!\n");
    struct aluno al;
    al.matricula = 11;
    al.n1 = 10.0;
    al.n2 = 10.0;
    al.media = (((al.n1) *2) + ((al.n2)*3))  / 5;
    insere_lista_final(li, al);

    printf("A lista cont�m %d elementos\n", tamanho_lista(li));
    printf("Elementos da lista ap�s inser��o:\n");
    no = *li;
    while (no != NULL) {
        printf("Matr�cula: %d, N1: %.1f, N2: %.1f, M�dia: %.1f\n", no->dados.matricula, no->dados.n1, no->dados.n2, no->dados.media);
        no = no->prox;
    }

    // Removendo o primeiro e �ltimo elementos
    printf("\nRemovendo o primeiro e �ltimo elemento da lista!\n");
    remove_lista_inicio(li);
    remove_lista_final(li);

    printf("Lista ap�s a remo��o dos dois elementos!\n");
    printf("A lista cont�m %d elementos\n", tamanho_lista(li));
    printf("Elementos da lista ap�s remo��o:\n");
    no = *li;
    while (no != NULL) {
        printf("Matr�cula: %d, N1: %.1f, N2: %.1f, M�dia: %.1f\n", no->dados.matricula, no->dados.n1, no->dados.n2, no->dados.media);
        no = no->prox;
    }

    // Buscando a posi��o da matr�cula 5 na lista
    printf("\nBuscando a posi��o da matr�cula 5 na lista!\n");
    struct aluno busca_aluno;
    no = *li;
    int pos = 1;
    while (no != NULL && no->dados.matricula != 5) {
        no = no->prox;
        pos++;
    }
    if (no != NULL) {
        printf("A matr�cula 5 est� na posi��o %d da lista!\n", pos);
    } else {
        printf("A matr�cula 5 n�o foi encontrada na lista!\n");
    }

    // Liberando a lista
    printf("\nDestruindo a lista!\n");
    libera_lista(li);

    return 0;
}

// Implementa��o das fun��es de manipula��o da lista

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li) {
    if (li == NULL) {
        return 0;
    }
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) {
        return 0;
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        return 0;
    }
    no->dados = al;
    no->prox = NULL;
    if (*li == NULL) {
        *li = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int remove_lista_inicio(Lista* li) {
    if (li == NULL || *li == NULL) {
        return 0;
    }
    Elem* no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL || *li == NULL) {
        return 0;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (no == *li) {
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL) {
        return 0;
    }
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat) {
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    } else {
        *al = no->dados;
        return 1;
    }
}

