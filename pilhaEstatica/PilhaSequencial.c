#include <stdio.h>
#include <stdlib.h>
#include "PilhaSequencial.h"

struct pilha{
	int qtd;
	struct aluno dados[MAX];
};

Pilha* cria_Pilha(){
		Pilha* pi;
		pi = (Pilha*) malloc(sizeof(struct pilha));
		if(pi != NULL){
			pi->qtd = 0;			
		}
		return pi;
	}
	
	void libera_Pilha(Pilha* pi){
		free(pi);
	}
	
	int tamanho_Pilha(Pilha* pi){
		
		if(pi == NULL){
			return -1;
			
		}else{
			return pi->qtd;
		}
	}
	
	int Pilha_cheia(Pilha* pi){
		if(pi == NULL){
			return -1;
		}
		return (pi->qtd == MAX);
	}
	
	int Pilha_vazia(Pilha* pi){
		
		if(pi == NULL){
			return -1;
		}
		
		return (pi->qtd == 0);
	}
	
	int insere_Pilha(Pilha* pi, struct aluno al){
		
		if(pi == NULL){
			return 0;
		}
		
		if(pi->qtd == MAX){
			return 0;
		}
		
		pi->dados[pi->qtd] = al;
		pi->qtd++;
		return 1;
	}
	
	int remove_Pilha(Pilha* pi){
		
		if(pi == NULL || pi->qtd == 0){
			return 0;
		}
		
		pi->qtd--;
		return 1;
	}
	
	int acessa_topo_Pilha(Pilha* pi, struct aluno *al){
		
		if(pi == NULL || pi->qtd ==0){
			return 0;
		}
		
		*al = pi->dados[pi->qtd-1];
		return 1;
	}


int main(){
	
	Pilha* pi = cria_Pilha();
	
	if(pi == NULL){
		printf("Erro ao Criar a Pilha\n");
	}
	
	struct aluno a1 = {123, "Aluno1", 7.0, 8.5, 9.0};
	struct aluno a2 = {456, "Aluno2", 6.0, 7.5, 8.0};

	if (insere_Pilha(pi, a1))
    	printf("Aluno1 inserido com sucesso!\n");
	else
    	printf("Erro ao inserir Aluno1!\n");

	if (insere_Pilha(pi, a2))
    	printf("Aluno2 inserido com sucesso!\n");
	else
    	printf("Erro ao inserir Aluno2!\n");
    	
    struct aluno al;
    
	if (acessa_topo_Pilha(pi, &al))
    	printf("Topo da pilha: %s\n", al.nome);
	else
    	printf("Erro ao acessar o topo da pilha!\n");	
    	
    if (remove_Pilha(pi))
    	printf("Elemento removido com sucesso!\n");
	else
    	printf("Erro ao remover elemento!\n");
}
	
