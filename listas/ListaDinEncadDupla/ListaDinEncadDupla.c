#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ListaDinEncadDupla.h" 

//Definição do tipo lista
struct elemento{
	struct elemento *ant;
	struct aluno dados;
	struct elemento *prox;
};

typedef struct elemento Elem;

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista)); // Aloca memória para a lista
    if (li != NULL) {
        *li = NULL; // Inicializa a lista com NULL
    }
    return li;    
}

void libera_lista(Lista* li)
{
	if(li != NULL)
	{
		Elem* no;
		while((*li) != NULL)
		{
			no = *li;
			*li = (*li)->prox;
			free(no);	
		}
		free(li);
	}
}

int tamanho_lista(Lista* li)
{
	if(li == NULL)
		return 0;
	int cont = 0;
	Elem* no = *li;
	while(no != NULL)
	{
		cont++;
		no = no->prox;
	}
	return cont;
}

int lista_cheia(Lista* li)
{
	return 0;
}

int lista_vazia(Lista* li)
{
	if(li == NULL)
		return 1;
	if(*li == NULL)
		return 1;
	return 0; 
}

int insere_lista_inicio (Lista* li, struct aluno al) 
{
	if (li == NULL)
		return 0;
	
	Elem* no;
	
	no = (Elem*) malloc(sizeof(Elem));
	
	if (no == NULL)
		return 0;
	
	no->dados = al;
	no->prox = (*li);
	no->ant = NULL;
	if(*li != NULL)
		(*li)->ant = no;
	*li = no;

	return 1;
}

int insere_lista_final (Lista* li, struct aluno al)
{
	if (li == NULL)
		return 0;
	
	Elem *no;
	no = (Elem*) malloc(sizeof(Elem));
	
	if (no == NULL)
		return 0;
	
	no->dados = al;
	no->prox = NULL;
	
	if((*li) == NULL) 
	{
		no->ant = NULL;
		*li = no;
	}	
	else
	{
		Elem *aux = *li;
	
		while (aux->prox != NULL) 
		{
			aux = aux->prox;
		}
		aux->prox = no;
		no->ant = aux;
	}
	return 1;
}

int insere_lista_ordenada (Lista* li, struct aluno al)
{
	if (li== NULL)
	return 0;
	
	Elem *no;
	no = (Elem*) malloc(sizeof (Elem));
	
	if (no == NULL)
		return 0;
	no->dados = al;
	
	if ((*li)== NULL) 
	{
		no->prox = NULL;
		no->ant = NULL;
		*li = no;
		return 1;
	}
	else
	{
		Elem *ante, *atual = *li;
	
		while (atual != NULL && atual -> dados.matricula < al.matricula)
		{
			ante = atual;
			atual = atual->prox;
	
			if(atual == *li) 
			{
				no->ant = NULL;
				(*li)->ant = no;
				no->prox = (*li);
				*li = no;
			}
			else
			{
				
				no->prox = ante->prox;
				no->ant = ante;
				ante->prox = no;
				if(atual != NULL)
					atual->ant = no;
			}
		return 1;
		}
	}
}

int remove_lista_inicio(Lista* li)
{
	if(li == NULL)
		return 0;
	if((*li) == NULL)
		return 0;
	Elem* no = *li;
	*li = no->prox;
	free(no);
	return 1;
}

int remove_lista_final (Lista* li) 
{ 
	if (li == NULL)
		return 0;
	
	if((*li) == NULL)
		return 0;
	
	Elem *no = *li;
	
	while (no->prox != NULL)
	{ 
		no = no->prox;  
	}
	
	if (no->ant == NULL)
		*li = no->prox;
	else
		no->ant->prox = NULL;
	
	free (no);
	return 1;
}

int remove_lista(Lista* li, int mat) 
{ 
    if (li == NULL || *li == NULL) // lista vazia
        return 0;
    
    Elem *ant = NULL; // ponteiro para o elemento anterior
    Elem *atual = *li; // ponteiro para percorrer a lista
    
    // Busca pelo elemento com a matrícula especificada
    while (atual != NULL && atual->dados.matricula != mat) {
        ant = atual;
        atual = atual->prox;
    }
    
    // Se o elemento não foi encontrado
    if (atual == NULL)
        return 0;
    
    // Remoção do elemento encontrado
    if (ant == NULL) { // remoção do primeiro elemento
        *li = atual->prox;
    } else {
        ant->prox = atual->prox;
    }
    
    free(atual); // libera o nó da memória
    return 1;
}

int busca_lista_pos (Lista* li, int pos, struct aluno *al)
{
	if (li == NULL || pos <= 0)
	return 0;
	
	Elem *no = *li;
	
	int i = 1;
	
	while (no != NULL && i < pos) 
	{
		no = no->prox;
		i++;
	}
	if (no == NULL) 
		return 0;
	
	else
	{ 
		*al = no->dados; 
		return 1;
	}
}


int busca_lista_mat(Lista* li, int mat, struct aluno *al) 
{
	if (li== NULL)
		return 0;
	
		Elem *no = *li;
	while (no != NULL && no->dados.matricula != mat) 
	{
		no = no->prox;
	}
	if (no == NULL)
		return 0;
	else
	{
		*al = no->dados;
		return 1;
	}
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
    } else {
        printf("Lista criada com sucesso\n\n");
    }

    // Inserindo elementos na lista
    al.matricula = 1;
    snprintf(al.nome, sizeof(al.nome), "João"); // usando snprintf para copiar uma string para al.nome
    al.n1 = 7.5;
    al.n2 = 8.0;
    al.n3 = 6.5;
    insere_lista_final(li, al);

    al.matricula = 2;
    snprintf(al.nome, sizeof(al.nome), "Maria");
    al.n1 = 6.0;
    al.n2 = 7.0;
    al.n3 = 8.0;
    insere_lista_final(li, al);

    al.matricula = 3;
    snprintf(al.nome, sizeof(al.nome), "Pedro");
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
    struct aluno aluno_temp;

    for (i = 1; i <= tamanho_lista(li); i++) {
        busca_lista_pos(li, i, &aluno_temp);
        printf("%d\t\t%s\t\t%.1f\t%.1f\t%.1f\n",
               aluno_temp.matricula, aluno_temp.nome,
               aluno_temp.n1, aluno_temp.n2, aluno_temp.n3);
    }
    printf("--------------------------------------------------\n");

    // Removendo um aluno da lista
    int matricula_remover = 1;
    printf("\nRemovendo aluno com matrícula %d...\n", matricula_remover);
    remove_lista(li, matricula_remover);

    // Exibindo a lista após a remoção
    printf("\nLista após remoção:\n");
    printf("--------------------------------------------------\n");
    printf("Matrícula\tNome\t\tNota1\tNota2\tNota3\n");
    printf("--------------------------------------------------\n");

    for (i = 1; i <= tamanho_lista(li); i++) {
        busca_lista_pos(li, i, &aluno_temp);
        printf("%d\t\t%s\t\t%.1f\t%.1f\t%.1f\n",
               aluno_temp.matricula, aluno_temp.nome,
               aluno_temp.n1, aluno_temp.n2, aluno_temp.n3);
    }
    printf("--------------------------------------------------\n");

    // Liberando a lista da memória
    libera_lista(li);

    return 0;
}
