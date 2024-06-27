#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Defini��o da estrutura aluno
struct aluno {
    int matricula;
    // char nome[30];
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

// Fun��es de manipula��o da lista
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int remove_lista(Lista* li, int mat);
int busca_lista_pos(Lista* li, int pos, struct aluno *al);
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

// Fun��o para criar a lista
Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}

// Fun��o para liberar a lista
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

// Fun��o para obter o tamanho da lista
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

// Fun��o para verificar se a lista est� cheia (sempre retorna 0, pois a lista � din�mica)
int lista_cheia(Lista* li) {
    return 0;
}

// Fun��o para verificar se a lista est� vazia
int lista_vazia(Lista* li) {
    if (li == NULL || *li == NULL) {
        return 1;
    }
    return 0;
}

// Fun��o para inserir um elemento no in�cio da lista
int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) {
        return 0;
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        return 0;
    }
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

// Fun��o para inserir um elemento no final da lista
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
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

// Fun��o para inserir um elemento de forma ordenada na lista
int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) {
        return 0;
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        return 0;
    }
    no->dados = al;
    if (*li == NULL) {
        no->prox = NULL;
        *li = no;
        return 1;
    } else {
        Elem *ant = NULL, *atual = *li;
        while (atual != NULL && atual->dados.matricula < al.matricula) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

// Fun��o para remover um elemento do in�cio da lista
int remove_lista_inicio(Lista* li) {
    if (li == NULL || *li == NULL) {
        return 0;
    }
    Elem* no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

// Fun��o para remover um elemento do final da lista
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

// Fun��o para remover um elemento da lista pela matr�cula
int remove_lista(Lista* li, int mat) {
    if (li == NULL || *li == NULL) {
        return 0;
    }
    Elem *ant = NULL, *no = *li;
    while (no != NULL && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    }
    if (no == *li) {
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

// Fun��o para buscar um elemento na lista pela posi��o
int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0) {
        return 0;
    }
    Elem* no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL) {
        return 0;
    } else {
        *al = no->dados;
        return 1;
    }
}

// Fun��o para buscar um elemento na lista pela matr�cula
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

int main() {
    setlocale(LC_ALL, "");

    Lista* li = cria_lista();

    float notas[10][2] = {{8.0, 9.0}, {5.0, 6.0}, {8.0, 7.0}, {4.0, 9.0}, {2.0, 6.0}, {7.5, 6.0}, {3.0, 5.0}, {2.0, 1.0}, {9.0, 8.0}, {8.0, 6.0}};
    int matriculas[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Lista vazia!\nInserindo elementos na lista!\n");

	int i;
    for ( i = 0; i < 10; i++) {
        struct aluno al;
        al.matricula = matriculas[i];
        al.n1 = notas[i][0];
        al.n2 = notas[i][1];
        al.media = (al.n1 + al.n2) / 2.0;
        insere_lista_ordenada(li, al);
    }

    printf("Foram inseridos 10 elementos na lista!\n");
    exibe_lista(li);

    printf("\nInserindo a matr�cula 11!\n");
    struct aluno al;
    al.matricula = 11;
    al.n1 = 10.0;
    al.n2 = 10.0;
    al.media = (al.n1 + al.n2) / 2.0;
    insere_lista_ordenada(li, al);

    printf("A lista cont�m %d elementos\n", tamanho_lista(li));
    printf("Elementos da lista ap�s inser��o:\n");
    exibe_lista(li);

    printf("\nRemovendo o primeiro e �ltimo elemento da lista!\n");
    remove_lista_inicio(li);
    remove_lista_final(li);

    printf("Lista ap�s a remo��o dos dois elementos!\n");
    printf("A lista cont�m %d elementos\n", tamanho_lista(li));
    printf("Elementos da lista ap�s remo��o:\n");
    exibe_lista(li);

    printf("\nBuscando a posi��o da matr�cula 5 na lista!\n");
    int posicao;
    struct aluno busca_aluno;
    if (busca_lista_mat(li, 5, &busca_aluno)) {
        printf("A matr�cula 5 est� na posi��o %d da lista!\n", posicao);
    } else {
        printf("Matr�cula 5 n�o encontrada na lista!\n");
    }

    printf("\nDestruindo a lista!\n");
    libera_lista(li);

    return 0;
}



