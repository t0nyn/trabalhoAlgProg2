
#include "cabecalho.h"

void printViatura(void *v)
{
	viatura *aux = (viatura *)v;
	printf("Cod: %d, tipo %s\n", aux->cod, aux->tipo);
}
void printListViatura(node *list)
{
	while (list != NULL)
	{
		printViatura(list->data);
		list = list->next;
	}
}
void loadViaturas(node *&list)
{
	FILE *fl = fopen("./viaturas.txt", "r");
	int in;

	do
	{
		viatura *temp = (viatura *)malloc(sizeof(viatura));
		in = fscanf(fl, "%d %[^\n]", &temp->cod, temp->tipo);
		temp->estado = 0;
		temp->numOcorrencias = 0;
		temp->policiais = NULL;
		temp->numPoliciais = 0;
		if (in != EOF)
			addNode(list, temp);
		else
			free(temp);
	} while (in != EOF);
	fclose(fl);
}

node *buscarViatura(int cod, node *list)
{
	// while (list != NULL)
	// {
	// 	viatura *aux = (viatura *)list->data;

	// 	if (aux->cod == cod)
	// 	{
	// 		if (aux->estado == 1)
	// 		{
	// 			printf("Viatura indisponivel.\n");
	// 			return NULL;
	// 		}
	// 		else
	// 		{
	// 			return list;
	// 		}
	// 	}
	// 	list = list->next;
	// }
	// printf("Viatura não encontrada.\n");
	// return NULL;

	node *viaturo = buscarPonteiroViatura(cod, list);
	viatura *aux = (viatura *)viaturo->data;

	if (!viaturo)
	{
		printf("Viatura não encontrada.\n");
		return NULL;
	}
	if (aux->estado == 1)
	{
		printf("Viatura indisponivel.\n");
		return NULL;
	}
	return viaturo;
}
node *buscarPonteiroViatura(int cod, node *list)
{
	while (list != NULL)
	{
		viatura *aux = (viatura *)list->data;

		if (aux->cod == cod)
		{
			return list;
		}
		list = list->next;
	}
	return NULL;
}

int avaliarOcorrencia(node *ocorr, viatura *vi)
{
	int action;
	printOcorrencia(ocorr);
	printf("Confirmada Acao Policial - 1    Acao Policial Dispensada - 2\n");
	scanf("%d", &action);
	if (action != 1)
	{
		// free(ocorr);
		return 0;
	}
	vi->ocorrencia = ocorr;
	for (int i = 0; i < vi->numPoliciais; i++)
	{
		ocorrencia *aux212 = (ocorrencia *)ocorr->data;
		addNode(aux212->policiais, vi->policiais[i]->data);
	}
	vi->estado = 4;
	return 1;
}

int avaliarListaOcorrencias(node *&ocorrencias, viatura *vi)
{
	int resp;
	node *ocorr = popInicio(ocorrencias);
	while (ocorr)
	{
		resp = avaliarOcorrencia(ocorr, vi);
		if (resp)
		{
			vi->numOcorrencias = vi->numOcorrencias + 1;
			return 1;
		}
		int n = ((ocorrencia *)ocorr->data)->qtdViaturas;
		// free(ocorr->data);
		free(ocorr);
		for (int i = 0; i < n - 1; i++)
		{
			ocorr = popInicio(ocorrencias);
			free(ocorr);
		}
		ocorr = popInicio(ocorrencias);
	}
	printf("Acabaram as ocorrencias.\n");
	return 0;
}

void avaliarReforco(node *&ocorrencias)
{
	node *aux_ref = ocorrencias;
	node *aux_comedia = NULL;
	while (aux_ref)
	{
		ocorrencia *aux_ref2 = (ocorrencia *)aux_ref->data;

		if (aux_ref2->reforco == 1)
		{
			printOcorrencia(aux_ref);
			int action;
			printf("Confirmada Pedido de Reforco - 1    Acao Policial Dispensada - 2\n");
			scanf("%d", &action);

			if (action != 1)
			{
				if (!aux_comedia)
				{
					ocorrencias = ocorrencias->next;
					free(aux_ref);
					aux_ref = ocorrencias;
					aux_comedia = NULL;
				}
				else
				{
					aux_comedia->next = aux_ref->next;
					free(aux_ref);
					aux_ref = aux_comedia->next;
				}
			}
			else
			{
				aux_ref2->reforco = 2;
			}
			aux_comedia = aux_ref;
			aux_ref = aux_ref->next;
		}
	}
	printf("\nZero(0) solicitacoes de reforco, prosseguindo para o cadastro de Ocorrencia.\n");
}

int avaliarListaReforcos(node *&ocorrencias, viatura *vi)
{
	node *ocorr = ocorrencias;
	node *aux_comedia = NULL;

	if (!ocorrencias)
	{
		return 0;
	}
	ocorrencia *aux = (ocorrencia *)ocorrencias->data;

	if (aux->reforco == 2)
	{
		printf("20\n");
		vi->ocorrencia = ocorr;
		ocorrencias = ocorrencias->next;
		ocorr = ocorrencias;
		vi->estado = 5;
		printf("Reforco atribuido\n");
		return 1;
	}

	while (ocorr)
	{
		printf("2\n");
		aux = (ocorrencia *)ocorrencias->data;
		if (aux->reforco == 2)
			printf("3\n");
		{
			vi->ocorrencia = ocorr;
			aux_comedia->next = ocorr->next;
			ocorr = aux_comedia->next;
			vi->estado = 5;
			printf("Reforco atribuido\n");
			return 1;
		}
		ocorr = ocorr->next;
	}
	printf("6\n");
	return 0;
}