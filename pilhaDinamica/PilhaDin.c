#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

struct elemento{
	
	struct aluno dados;
	struct elemento *prox;
};
typedef struct elemento Elem;

Pilha* cria_Pilha(){
		
		Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
		if(pi != NULL){
			*pi = NULL;			
		}
		return pi;
	}
	
	void libera_Pilha(Pilha* pi){
		if(pi != NULL){
			Elem* no;
			
			while((*pi) != NULL){
				no = *pi;
				*pi = (*pi)->prox;
				free(no);
			}
			free(pi);
		}
	}
	
	int tamanho_Pilha(Pilha* pi){
		
		if(pi == NULL){
			return 0;
			
		}
		int cont = 0;
		Elem* no = *pi;
		
		while (no != NULL){
			cont++;
			no = no->prox;
		}
		
		return cont;
	}
	
	int Pilha_cheia(Pilha* pi){
		return 0;
	}
	
	int Pilha_vazia(Pilha* pi){
		
		if(pi == NULL){
			return 1;
		}
		
		if(*pi == NULL){
			return 1;
		}
		
		return 0;		
	}
	
	int insere_Pilha(Pilha* pi, struct aluno al){
		
		if(pi == NULL){
			return 0;
		}
		
		Elem* no;
		no = (Elem*) malloc(sizeof(Elem));
		
		if(no == NULL){
			return 0;
		}
		
		no->dados = al;
		no->prox = (*pi);
		*pi = no;
		return 1;
	}
	
	int remove_Pilha(Pilha* pi){
		
		if(pi == NULL ){
			return 0;
		}
		
		Elem *no = *pi;
		*pi = no->prox;
		free(no);
		return 1;	
	}
	
	int acessa_topo_Pilha(Pilha* pi, struct aluno *al){
		
		if(pi == NULL ){
			return 0;
		}
		
		if((*pi) == NULL){
			return 0;
		}	
		
		*al = (*pi)->dados;
		return 1;
	}	
	
	int main() {
     Pilha* pi = cria_Pilha();
     if (pi == NULL) {
        printf("Erro ao criar a pilha\n");
        return -1;
    }

    // Testando a inserção de elementos
    struct aluno a1 = {123, "Aluno1", 7.0, 8.5, 9.0};
    struct aluno a2 = {456, "Aluno2", 6.0, 7.5, 8.0};
    struct aluno a3 = {789, "Aluno3", 8.0, 9.5, 10.0};

    if (insere_Pilha(pi, a1))
        printf("Aluno1 inserido com sucesso!\n");
    else
        printf("Erro ao inserir Aluno1!\n");

    if (insere_Pilha(pi, a2))
        printf("Aluno2 inserido com sucesso!\n");
    else
        printf("Erro ao inserir Aluno2!\n");

    if (insere_Pilha(pi, a3))
        printf("Aluno3 inserido com sucesso!\n");
    else
        printf("Erro ao inserir Aluno3!\n");

    // Verificando se a pilha está vazia
    if (Pilha_vazia(pi))
        printf("A pilha está vazia!\n");
    else
        printf("A pilha não está vazia!\n");

    // Acessando o topo da pilha
    struct aluno al;
    if (acessa_topo_Pilha(pi, &al))
        printf("Topo da pilha: %s\n", al.nome);
    else
        printf("Erro ao acessar o topo da pilha!\n");

    // Removendo elementos da pilha
    if (remove_Pilha(pi))
        printf("Elemento removido com sucesso!\n");
    else
        printf("Erro ao remover elemento!\n");

    if (acessa_topo_Pilha(pi, &al))
        printf("Topo da pilha: %s\n", al.nome);
    else
        printf("Erro ao acessar o topo da pilha!\n");

    libera_Pilha(pi);
    return 0;
}
	


	
