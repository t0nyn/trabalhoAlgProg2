
#include "cabecalho.h"

void uncrypt(char *new_psw)
{
	int len = strlen(new_psw);
	char psw[MAX + 1];
	strcpy(psw, new_psw);
	int j = 0;
	for (int i = len - 1; i >= 0; i--, j++)
	{
		if ((psw[i] >= 'a' && psw[i] <= 'z') || (psw[i] >= 'A' && psw[i] <= 'Z'))
		{
			char aux = psw[i] - 3;
			new_psw[j] = aux < 'A' || (aux > 'Z' && aux < 'a') ? aux + 26 : aux;
		}
		else
			new_psw[j] = psw[i];
	}
	new_psw[j] = '\0';
}

void loadPolicial(node *&list)
{
	FILE *fl = fopen("./policiais.txt", "r");
	int in;

	do
	{
		policial *temp = (policial *)malloc(sizeof(policial));
		in = fscanf(fl, " %[^\n] %[^\n] %[^\n] %[^\n] %d %[^\n] %[^\n]", temp->nome, temp->cpf, temp->nomeGuerra, temp->cidade, &temp->idade, temp->cargo, temp->senha);
		uncrypt(temp->senha);
		// printf("%s %s\n", temp->nomeGuerra, temp->senha);
		temp->alocado = 0;
		if (in != EOF)
			addNode(list, temp);
		else
			free(temp);
	} while (in != EOF);
	fclose(fl);
}

void printPolicial(void *v)
{
	policial *aux = (policial *)v;
	printf("Nome: %s, CPF %s, Nome de Guerra: %s, Cidade: %s, Idade: %d, Cargo: %s, Senha: %s\n", aux->nome, aux->cpf, aux->nomeGuerra, aux->cidade, aux->idade, aux->cargo, aux->senha);
}
void printListPolicia(node *list)
{
	while (list != NULL)
	{
		printPolicial(list->data);
		list = list->next;
	}
}

node *buscarPolicial(char nomeGuerra[MAX + 1], node *list)
{
	node *polissa = buscarPolicialExistente(nomeGuerra, list);

	if (!polissa)
	{
		return NULL;
	}
	else if (((policial *)polissa->data)->alocado)
	{
		printf("Policial já está alocado em outra Viatura.\n");
		return NULL;
	}
	else
	{
		return polissa;
	}
}

node *buscarPolicialExistente(char nomeGuerra[MAX + 1], node *list)
{
	while (list != NULL)
	{
		policial *aux = (policial *)list->data;

		if (!strcasecmp(nomeGuerra, aux->nomeGuerra))
		{
			return list;
		}
		list = list->next;
	}
	// printf("Policial não encontrado.\n");
	return NULL;
}

policial *policial_login(node *pol, int tipo)
{
	// TIPO
	// 1 - Qualquer policial
	// 2 - Oficial ou superior
	// 3 - Comandante

	char ndg[MAX + 1];
	char senha[MAX + 1];
	printf("\nPolicial militar\n");
	printf("Nome de Guerra: ");
	scanf(" %[^\n]", ndg);

	node *policialEncontrado = buscarPolicialExistente(ndg, pol);
	if (!policialEncontrado)
	{
		printf("Policial não encontrado.\n");
		return NULL;
	}
	policial *aux = (policial *)policialEncontrado->data;

	if (tipo != 1 && (!strcasecmp(aux->cargo, "soldado") || (tipo == 3 && strcasecmp(aux->cargo, "Comandante Geral"))))
	{
		printf("Acesso negado a essa patente.\n");
		return NULL;
	}

	// printf("%s %s\n", aux->nomeGuerra, aux->senha);
	printf("Senha: ");
	scanf(" %[^\n]", senha);

	if (!strcmp(aux->senha, senha))
	{
		return aux;
	}
	else
	{
		printf("Senha incorreta!!!\n");
		return NULL;
	}
}
