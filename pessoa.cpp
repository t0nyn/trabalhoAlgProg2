#include "cabecalho.h"

void loadPessoas(node *&list)
{
	FILE *fl = fopen("./pessoas.txt", "r");
	int in;

	do
	{
		pessoa *new_node = (pessoa *)malloc(sizeof(pessoa));
		new_node->inadimplencias = NULL;
		new_node->passagens = NULL;
		in = fscanf(fl, " %[^\n] %[^\n] %[^\n] %d %d", new_node->nome,
					new_node->cpf,
					new_node->cidade,
					&new_node->idade,
					&new_node->numPassagens);

		for (int i = 0; i < new_node->numPassagens; i++)
		{
			char *tempPassagem = (char *)malloc(MAX + 1 * sizeof(char));
			in = fscanf(fl, " %[^\n]", tempPassagem);

			if (in != EOF)
				addNode(new_node->passagens, tempPassagem);
			else
				free(tempPassagem);
		}

		in = fscanf(fl, "%d", &new_node->numInadimplencias);
		for (int i = 0; i < new_node->numInadimplencias; i++)
		{
			char *tempInadimplencia = (char *)malloc(MAX + 1 * sizeof(char));
			in = fscanf(fl, " %[^\n]", tempInadimplencia);

			if (in != EOF)
				addNode(new_node->inadimplencias, tempInadimplencia);
			else
				free(tempInadimplencia);
		}

		if (in != EOF)
			addNode(list, new_node);
		else
			free(new_node);

	} while (in != EOF);
	fclose(fl);
}
void printPessoa(void *v)
{
	pessoa *aux = (pessoa *)v;
	printf("Nome: %s \n CPF: %s\n Cidade %s\n  Idade: %d\n Passagens: %d\n", aux->nome, aux->cpf, aux->cidade, aux->idade, aux->numPassagens);

	for (int i = 0; i < aux->numPassagens; i++)
	{
		char *tempPassagem = (char *)aux->passagens->data;

		printf("	%s\n", tempPassagem);
		aux->passagens = aux->passagens->next;
	}

	printf("Inadimplencias: %d\n", aux->numInadimplencias);
	for (int i = 0; i < aux->numInadimplencias; i++)
	{
		char *tempInadimplencia = (char *)aux->inadimplencias->data;
		printf("	%s\n, ", tempInadimplencia);
		aux->inadimplencias = aux->inadimplencias->next;
	}
	printf("\n");
}

void printListPessoa(node *list)
{
	while (list != NULL)
	{
		printPessoa(list->data);
		list = list->next;
	}
}

pessoa *pessoaBuscarPorCpf(node *list, char cpf[MAX + 1])
{
	while (list != NULL)
	{
		pessoa *p = (pessoa *)list->data;
		if (strcasecmp(p->cpf, cpf) == 0)
		{
			return p;
		}
		list = list->next;
	}
	return NULL;
}