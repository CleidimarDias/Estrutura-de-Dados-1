#include <stdio.h>
#include<locale.h>
#include "Listasequencial.h" //inclui os protótipos

//Definição do tipo lista

struct lista{
	int qtd;
	struct aluno dados [MAX];
};

Lista* cria_lista()
{
	Lista *li;
	li = (Lista*) malloc(sizeof(struct lista));
	if(li != NULL)
		li->qtd = 0;
		return li;
}

void libera_lista(Lista* li)
{
	free(li);
}

int tamanho_lista(Lista* li)
{
	if(li == NULL)
		return -1;
	else
		return li->qtd;
}

int lista_cheia(Lista* li)
{
	if(li == NULL)
		return -1;
	return(li->qtd == MAX);
}

int lista_vazia(Lista* li)
{
	if(li == NULL)
		return (li->qtd == 0);
}

int insere_lista_inicio (Lista* li, struct aluno al) 
{
	if(li== NULL)
		return 0;
	if (li->qtd == MAX)//lista cheia
		return 0;

	int i;

	for(i=li->qtd-1; i>=0; i--)
		li->dados[i+1] = li->dados [i];
	li->dados[0] = al;
	li->qtd++;

	return 1;
}

int insere_lista_final(Lista* li, struct aluno al)
{
	if(li == NULL)
		return 0;
	if(li->qtd == MAX)//lista cheia
		return 0;

	
	li->dados[li->qtd] = al;
	li->qtd++;
	
	return 1;
}

int insere_lista_ordenada (Lista* li, struct aluno al)
{
	if (li == NULL)
		return 0;

	if(li->qtd == MAX)//lista cheia
		return 0;
	
	int k,i=0;
	
	while(i<li->qtd && li->dados[i].matricula < al.matricula)
		i++;
	
	for(k=li->qtd-1; k >= i; k--)
		li->dados [k+1] = li->dados [k];
	li->dados[i] = al;
	li->qtd++;
	
	return 1;
}

int remove_lista_inicio(Lista* li)
{
	if(li == NULL)
		return 0;
	if(li->qtd == 0) //lista vazia
		return 0;
	int k = 0;
	for(k=0;k<li->qtd-1;k++)
		li->dados[k] = li->dados[k+1];
	li->qtd--;
	return 1;		
}

int remove_lista_final(Lista* li)
{
	if(li == NULL)
		return 0;
	if(li->qtd == 0) //lista vazia
		return 0;
	li->qtd--;
	return 1;		
}

int remove_lista(Lista* li, int mat) 
{ 
    if (li == NULL || li->qtd == 0)
        return 0;

    int i = 0;
    while (i < li->qtd && li->dados[i].matricula != mat)
        i++;
    
    if (i == li->qtd) // elemento não encontrado
        return 0;

    // Desloca os elementos para frente para remover o elemento na posição i
    int k;
    for ( k = i; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];

    li->qtd--;
    
    return 1;
}

int remove_lista_otimizado (Lista* li, int mat) 
{
	if (li == NULL)
		return 0;
	
	if (li->qtd == 0)
		return 0; 
	
	int i = 0; 
	while(i<li->qtd && li->dados[i].matricula != mat) 
		i++; 
	
	if(i== li->qtd)//elemento nao encontrado return 0;
		li->qtd--;
	li->dados[i] = li->dados [li->qtd];
	
	return 1;
}

int busca_lista_pos(Lista* li, int pos, struct aluno *al)
{
	if(li == NULL || pos <= 0 || pos > li->qtd)
		return 0;
	*al = li->dados[pos-1];
	return 1;
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) 
{ 
	if (li == NULL)
		return 0;
	
	int i = 0;
	
	while(i<li->qtd && li->dados[i].matricula != mat) 
		i++;
	
	if(i== li->qtd)//elemento nao encontrado
		return 0;
	
	*al = li->dados[i];
	
	return 1;
}




int main() {
	setlocale(LC_ALL, "Portuguese");
    Lista *li; // Declaração do ponteiro para a lista
    struct aluno al; // Declaração de uma variável do tipo aluno
    
    // Criando a lista
    li = cria_lista();
    
    // Verificando se a lista foi criada corretamente
    if (li == NULL) {
        printf("Erro ao criar a lista!\n\n");
        return 1;
    }else{
    	printf("\n Lista criada com sucesso\n");
	}
    
    // Inserindo elementos na lista
    al.matricula = 1;
    al.nome[0] = 'J'; al.nome[1] = 'o'; al.nome[2] = 'a'; al.nome[3] = 'o'; al.nome[4] = '\0';
    al.n1 = 7.5;
    al.n2 = 8.0;
    al.n3 = 6.5;
    insere_lista_final(li, al);
    
    al.matricula = 2;
    al.nome[0] = 'M'; al.nome[1] = 'a'; al.nome[2] = 'r'; al.nome[3] = 'i'; al.nome[4] = 'a'; al.nome[5] = '\0';
    al.n1 = 6.0;
    al.n2 = 7.0;
    al.n3 = 8.0;
    insere_lista_final(li, al);
    
    al.matricula = 3;
    al.nome[0] = 'P'; al.nome[1] = 'e'; al.nome[2] = 'd'; al.nome[3] = 'r'; al.nome[4] = 'o'; al.nome[5] = '\0';
    al.n1 = 5.0;
    al.n2 = 6.0;
    al.n3 = 7.0;
    insere_lista_final(li, al);
    
    // Exibindo a lista antes da remoção
    printf("Lista antes da remoção:\n");
    printf("--------------------------------------------------\n");
    printf("Matrícula\tNome\t\tNota1\tNota2\tNota3\n");
    printf("--------------------------------------------------\n");
    
    int i;
    for ( i = 0; i < tamanho_lista(li); i++) {
        printf("%d\t\t%s\t\t%.1f\t%.1f\t%.1f\n", 
               li->dados[i].matricula, li->dados[i].nome, 
               li->dados[i].n1, li->dados[i].n2, li->dados[i].n3);
    }
    printf("--------------------------------------------------\n");
    
    
    // Removendo um aluno da lista
    int mat = 1;
    printf("\nRemovendo aluno com matrícula %d...\n", mat);
    remove_lista(li, mat);
    
    // Exibindo a lista após a remoção
    printf("\nLista após remoção:\n");
    printf("--------------------------------------------------\n");
    printf("Matrícula\tNome\t\tNota1\tNota2\tNota3\n");
    printf("--------------------------------------------------\n");
    
    for ( i = 0; i < tamanho_lista(li); i++) {
        printf("%d\t\t%s\t\t%.1f\t%.1f\t%.1f\n", 
               li->dados[i].matricula, li->dados[i].nome, 
               li->dados[i].n1, li->dados[i].n2, li->dados[i].n3);
    }
    printf("--------------------------------------------------\n");
    
    // Liberando a lista da memória
    libera_lista(li);
    
    return 0;
}
