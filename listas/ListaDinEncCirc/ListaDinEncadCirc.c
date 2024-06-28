#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h" 

//Definição do tipo lista

struct elemento
{
	struct aluno dados;
	struct elemento *prox;
};

typedef struct elemento Elem;

Lista* cria_lista()
{
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL)
		*li =NULL;
	return li;
}

void libera_lista (Lista* li) 
{
	if(li != NULL && (*li) != NULL)
	{
		Elem *aux, *no = *li;
	
		while((*li) != no->prox) 
		{
			aux = no;
			no = no->prox;
			free (aux);
		}
		free (no);
		free (li);
	}

}

int tamanho_lista (Lista* li) 
{
	if (li == NULL || (*li) == NULL)
		return 0;
	
	int cont = 0;
	Elem* no = *li;
	
	do {
		cont++;
		no = no->prox;
	}while(no != (*li));
	
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

int insere_lista_inicio(Lista* li, struct aluno al) 
{
    if (li == NULL)
        return 0;
    
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    
    no->dados = al;

    if ((*li) == NULL) 
	{
        *li = no;
        no->prox = no;
    } 
	else 
	{
        Elem* aux = *li;
        while (aux->prox != (*li)) 
		{
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;
    }

    return 1;
}

int insere_lista_final (Lista* li, struct aluno al)
{
	if (li == NULL)
		return 0;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL)
		return 0;
	no->dados = al;
	if((*li) == NULL) 
	{
		*li = no;
		no->prox = no;
	}
	else
	{ 
		Elem *aux = *li; 
		while (aux->prox != (*li))
		{ 
			aux = aux->prox;
		}
		aux->prox = no; no->prox = *li;
		no->prox =*li;
	}
	return 1;
}

insere_lista_ordenada (Lista* li, struct aluno al) 
{ 
	if (li== NULL)
		return 0;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if (no == NULL)
		return 0;
	no->dados = al;
	if ((*li) == NULL) 
	{
		*li = no;
		no->prox = no;
		return 1;
	}
	else
	{
		if((*li)->dados.matricula > al.matricula) 
		{
			Elem *atual = *li; 
			while (atual->prox != (*li))
			atual = atual->prox;
			no->prox = *li;
			atual->prox = no;
			*li = no;
			return 1;
		}
		Elem *ant = *li, *atual = (*li)->prox;
		
		while (atual != (*li) && atual->dados.matricula < al.matricula)
		{
			ant = atual; 
			atual = atual->prox;
		}
		ant->prox = no;
		
		no->prox = atual;
		
		return 1;
	}
}

int remove_lista_inicio (Lista* li) 
{
	if (li == NULL)
		return 0;
	if((*li) == NULL)
		return 0;
	if((*li) == (*li)->prox) 
	{
		free(*li);
		*li = NULL;
		return 1;
	}
	Elem *atual = *li;
	while (atual->prox != (*li))
		atual = atual->prox;
	Elem *no = *li;
	atual->prox = no->prox;
	(*li) = no->prox;
	free (no);
	return 1;
}

int remove_lista_final (Lista* li) 
{
	if (li == NULL)
		return 0;
	if((*li) == NULL)
		return 0;
	if ((*li) = (*li)->prox)
	{
		free(*li);
		*li = NULL;
		return 1;
	}
	Elem *ant, *no = *li;
	while (no->prox != (*li)) 
	{
		ant = no;
		no = no->prox;
	}
	ant->prox = no->prox;
	free (no);
	return 1;
}

int remove_lista(Lista* li, int mat) 
{
	if (li == NULL)
		return 0;
	if((*li)== NULL)
		return 0;
	Elem *no = *li;
	if (no->dados.matricula == mat)
	{
		free(no);
		*li = NULL;
		return 1;
	}
	else
	{
		Elem *ult = *li;
		while (ult->prox != (*li))
			ult = ult->prox;
		ult->prox = (*li)->prox;
		*li = (*li)->prox;
		free (no);
		return 1;
	}
	Elem *ant = no; 
	no = no->prox; 
	while (no != (*li) && no->dados.matricula != mat) 
		{
			ant = no;
			no = no->prox;
		}
	if (no == *li)
		return 0;
	ant->prox = no->prox;
	free(no);
	return 1;
}

int busca_lista_pos (Lista* li, int pos, struct aluno *al) 
{ 
	if (li == NULL || (*li) == NULL || pos <= 0)
		return 0;
	Elem *no = *li;
	int i = 1;
	while (no->prox != (*li) && i < pos) 
	{
		no = no->prox;
		i++;
	}
	if(i!= pos)
		return 0;
	else
	{
		*al = no->dados;
		return 1;
	}
}

int busca_lista_mat (Lista* li, int mat, struct aluno *al) 
{
	if(li == NULL || (*li) == NULL)
		return 0;
	Elem *no = *li;
	while(no->prox != (*li) && no->dados.matricula != mat) 
		no = no->prox;
	if (no->dados.matricula != mat)
		return 0;
	else 
	{
		*al = no->dados;
		return 1;
	}
}

void mostra_lista(Lista* li) {
    if (lista_vazia(li)) {
        printf("Lista vazia!\n");
        return;
    }

    Elem* atual = *li;
    do {
        printf("Matricula: %d, Nome: %s, Notas: %.2f %.2f %.2f\n", 
               atual->dados.matricula, 
               atual->dados.nome,
               atual->dados.n1,
               atual->dados.n2,
               atual->dados.n3);
        atual = atual->prox;
    } while (atual != *li);
    printf("\n");
}


int main() {
    Lista* li; // Ponteiro para a lista
    struct aluno a1, a2, a3, a4; // Exemplos de alunos para inserção na lista
    struct aluno aluno_busca;
    int busca_posicao = 2;
    int matricula_busca = 12345;

    // Criação da lista
    li = cria_lista();

    // Verifica se a lista foi criada corretamente
    if (li == NULL) {
        printf("Erro ao criar a lista!\n");
        return 1; // Termina o programa com erro
    }

    // Inserção de elementos na lista
    a1.matricula = 12345;
    a2.matricula = 67890;
    a3.matricula = 54321;
    a4.matricula = 54344;

    insere_lista_final(li, a1);
    insere_lista_final(li, a2);
    insere_lista_final(li, a3);
    insere_lista_ordenada ( li, a4);
    
    mostra_lista(li);

    // Busca por posição na lista
    if (busca_lista_pos(li, busca_posicao, &aluno_busca)) {
        printf("Aluno encontrado na posicao %d:\n", busca_posicao);
        printf("Matricula: %d\n", aluno_busca.matricula);
    } else {
        printf("Nao foi possivel encontrar o aluno na posicao %d\n", busca_posicao);
    }
    
    

    // Busca por matrícula na lista
    if (busca_lista_mat(li, matricula_busca, &aluno_busca)) {
        printf("Aluno encontrado com matricula %d:\n", matricula_busca);
        printf("Nome: %s\n", aluno_busca.nome);
    } else {
        printf("Nao foi possivel encontrar o aluno com matricula %d\n", matricula_busca);
    }

    // Remoção de elementos da lista
    remove_lista_final(li);

    // Libera a lista da memória
    libera_lista(li);

    return 0;
}
