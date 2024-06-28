#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h" 

struct fila {
	int inicio, final, qtd;
	struct aluno dados [MAX];
};

Fila* cria_Fila()
{
	Fila *fi;
	fi = (Fila*) malloc(sizeof(struct fila));
	if (fi != NULL) 
	{
		fi->inicio = 0;
		fi->final = 0;
		fi->qtd = 0;
	}
	return fi;
}

void libera_Fila(Fila* fi)
{
	free(fi);
}

int tamanho_Fila(Fila* fi)
{
	if (fi == NULL)
		return -1;
	return fi->qtd;
}

int Fila_cheia(Fila* fi)
{
	if (fi == NULL)
		return -1;
	if (fi->qtd == MAX)
		return 1;
	else
		return 0;
}

int Fila_vazia(Fila* fi)
{
	if (fi == NULL)
		return -1;
	if (fi->qtd == 0)
		return 1;
	else
		return 0;
}

int insere_Fila (Fila* fi, struct aluno al) 
{
	if (fi == NULL)
		return 0;
	if (fi->qtd == MAX)
		return 0;
	fi->dados [fi->final] = al;
	fi->final = (fi->final+1)%MAX;
	fi->qtd++;
	return 1;
}

int remove_Fila(Fila* fi)
{
	if(fi == NULL || fi->qtd == 0)
		return 0;
	fi->inicio = (fi->inicio+1)%MAX;
	fi->qtd--;
	return 1;
}

int consulta_Fila(Fila* fi, struct aluno *al)
{
	if(fi == NULL || Fila_vazia(fi))
		return 0;
	*al = fi->dados[fi->inicio];
	return 1;
}

int main() {
    Fila* fi;  // Declaração da fila estática
    struct aluno a1 = {123, "Aluno 1", 7.5, 8.0, 9.0};
    struct aluno a2 = {456, "Aluno 2", 6.5, 5.0, 8.0};
    struct aluno a3 = {789, "Aluno 3", 9.0, 8.5, 7.0};
    struct aluno al;

    // Criação da fila estática
    fi = cria_Fila();

    // Verificação da criação da fila
    if (fi == NULL) {
        printf("Erro ao criar a fila!\n");
        return 1;
    }

    // Inserção na fila estática
    insere_Fila(fi, a1);
    insere_Fila(fi, a2);
    insere_Fila(fi, a3);

    // Mostra todos os elementos da fila estática
    printf("Fila estatica:\n");
    int i;
    for (i = 0; i < tamanho_Fila(fi); i++) {
        consulta_Fila(fi, &al);
        printf("Matricula: %d, Nome: %s, Notas: %.2f %.2f %.2f\n",
               al.matricula,
               al.nome,
               al.n1,
               al.n2,
               al.n3);
        remove_Fila(fi);
    }
    printf("\n");

    // Liberação de memória
    libera_Fila(fi);

    return 0;
}
