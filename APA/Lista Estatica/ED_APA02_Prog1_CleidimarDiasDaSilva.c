#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#include "ED_APA02_Prog1_CleidimarDiasDaSilva.h"


#define MAX 10
struct aluno{
	int matricula;
	float n1, n2;
	float media;
};

typedef struct lista Lista;

Lista* cria_lista ();
void libera_lista (Lista* li);
int tamanho_lista (Lista* li);
int lista_cheia (Lista* li);
int lista_vazia (Lista* li);
int insere_lista_inicio (Lista* li, struct aluno al);
int insere_lista_final (Lista* li, struct aluno al);
int insere_lista_ordenada (Lista* li, struct aluno al);
int remove_lista_inicio (Lista* li);
int remove_lista_final (Lista* li);
int remove_lista(Lista* li, int mat);
int remove_lista_otimizado (Lista* li, int mat);
int busca_lista_pos(Lista* li, int pos, struct aluno *al);
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

struct lista {
	int qtd;
	struct aluno dados[MAX];
};

Lista* cria_lista(){
	Lista *li;
	li = (Lista*) malloc(sizeof(struct lista));
	if(li != NULL){
		li->qtd = 0;
	}
	return li;
}

void libera_lista (Lista* li){
	free(li);
}

int tamanho_lista (Lista* li){
	
	if(li == NULL){
		return -1;
		
	}else{
		return li->qtd;
	}
	
}

int lista_cheia (Lista* li){
	
	if(li == NULL){
		return -1;	
	}
	return (li->qtd == MAX);
}

int lista_vazia (Lista* li){
	
	if(li == NULL){
		return -1;
	}
	return (li->qtd == 0);
}


int insere_lista_inicio (Lista* li, struct aluno al){
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == MAX){
		return 0;
	}
	
	int i;
	
	for (i = li->qtd-1; i>=0; i--){
		li->dados[i+1] = li->dados[i];
	}
	
	li->dados[0] = al;
	li->qtd++;
	return 1;
}

int insere_lista_final (Lista* li, struct aluno al){
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == MAX){
		return 0;
	}
	
	li->dados[li->qtd] = al;
	li->qtd++;
	return 1;
}

int insere_lista_ordenada (Lista* li, struct aluno al){
	if (li == NULL){
		return 0;
	}
	
	if(li->qtd == MAX){
		return 0;
	}
	
	int i, k = 0;
	
	while(i<li->qtd && li->dados[i].matricula < al.matricula){
		i++;
	}
	
	for(k=li->qtd - 1; k>=i; k--){
		li->dados[k+1] = li->dados[k];
	}
	
	li->dados[i] = al;
	li->qtd++;
	return 1;
}

int remove_lista_inicio (Lista* li){
	
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == 0){
		return 0;
	}
	
	int i;
	
	for (i = 0; i<li->qtd - 1; i++){
		li->dados[i] = li->dados[i+1];
	}
	li->qtd--;
	return 1;
}

int remove_lista_final (Lista* li){
	
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == 0){
		return 0;
	}
	
	li->qtd--;
}

int remove_lista(Lista* li, int mat){
	
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == 0){
		return 0;
	}
	
	int i, k = 0;
	
	while(i < li->qtd && li->dados[i].matricula != mat ){
		i++;
	}
	
	// Elemento não encontrado	
	if(i == li->qtd){ 
		return 0;
	}
	
	
	for(k = i; k < li->qtd - 1; k++){
		li->dados[k] = li->dados[k+1];
		li->qtd--;
		return 1;
	}
}

int remove_lista_otimizado (Lista* li, int mat){
	
	if(li == NULL){
		return 0;
	}
	
	if(li->qtd == 0){
		return 0;
	}
	
	int i, k =0;
	
	while(i < li->qtd && li->dados[i].matricula != mat){
		i++;
	}
	
	if(i == li->qtd){
		return 0;
	}
	
	li->qtd--;	
	li->dados[i] = li->dados[li->qtd];
	return 1;
}

int busca_lista_pos(Lista* li, int pos, struct aluno *al){
	
	if(li == NULL || pos <=0 || pos > li->qtd){
		return 0;
	}
	
	*al = li->dados[pos -1];
	return 1;
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al){
	
	if(li == NULL){
		return 0;
	}
	
	int i = 0;
	
	while(i < li->qtd && li->dados[i].matricula != mat){
		i++;
	}
	
	if(i == li->qtd){
		return 0;
	}
	
	*al = li->dados[i];
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Definindo matrículas e notas
    int matriculas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float notas[][2] = {{8.0, 9.0}, {5.0, 6.0}, {8.0, 7.0}, {4.0, 9.0}, {2.0, 6.0},
                        {7.5, 6.0}, {3.0, 5.0}, {2.0, 1.0}, {9.0, 8.0}, {8.0, 6.0}};

    Lista *li = cria_lista();
    if (li == NULL) {
        printf("Erro ao criar a lista\n");
        return 1;
    }

    printf("Lista vazia!\n");
    printf("Inserindo elementos na lista!\n");

    // Inserindo alunos na lista
    struct aluno al;
    int i; // Declaração da variável fora do laço for
    for (i = 0; i < 10; i++) {
        al.matricula = matriculas[i];
        al.n1 = notas[i][0];
        al.n2 = notas[i][1];
        al.media = (al.n1 + al.n2) / 2;
        insere_lista_final(li, al);
    }

    printf("Foram inseridos 10 elementos na lista!\n");

    // Exibindo elementos da lista
    printf("Elementos da lista com média:\n");
    
//    for (i = 0; i < tamanho_lista(li); i++) {
//        busca_lista_pos(li, i + 1, &al);
//        printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
//    }

	for (i = tamanho_lista(li) -1 ; i >= 0; i--) {
        	busca_lista_pos(li, i + 1, &al);
        	printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
    }


    // Tentando inserir um novo aluno
    printf("Inserindo a matrícula 11!\n");
    al.matricula = 11;
    al.n1 = 10.0;
    al.n2 = 10.0;
    al.media = (al.n1 + al.n2) / 2;

    if (insere_lista_final(li, al) == 0) {
        printf("Lista cheia! A lista contem 10 elementos\n");
    }

    // Removendo o primeiro e último elementos
    printf("Removendo o primeiro e último elemento da lista!\n");
    remove_lista_inicio(li);
    remove_lista_final(li);

    // Exibindo a lista após remoções
    printf("Lista após a remoção dos dois elementos! A lista contém %d elementos\n", tamanho_lista(li));
//    for (i = 0; i < tamanho_lista(li); i++) {
//        busca_lista_pos(li, i + 1, &al);
//        printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
//    }
    
    for (i = tamanho_lista(li) -1 ; i >= 0; i--) {
        busca_lista_pos(li, i + 1, &al);
        printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
    }

    // Inserindo novamente a matrícula 11
    printf("Inserindo a matrícula 11!\n");
    insere_lista_final(li, al);

    printf("A lista contém %d elementos\n", tamanho_lista(li));
//    for (i = 0; i < tamanho_lista(li); i++) {
//        busca_lista_pos(li, i + 1, &al);
//        printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
//    }
    
     for (i = tamanho_lista(li) -1; i >= 0; i--) {
        busca_lista_pos(li, i + 1, &al);
        printf("Matrícula: %d, N1:%.1f, N2:%.1f, Média: %.1f\n", al.matricula, al.n1, al.n2, al.media);
    }

    // Buscando a posição da matrícula 5
    printf("Buscando a posição da matrícula 5 na lista!\n");
    for (i = 0; i < tamanho_lista(li); i++) {
        busca_lista_pos(li, i + 1, &al);
        if (al.matricula == 5) {
            printf("A matrícula 5 está na posição %d da lista!\n", i + 1);
            break;
        }
    }

    // Liberando a lista
    printf("Destruindo a lista!\n");
    libera_lista(li);

    return 0;
}
