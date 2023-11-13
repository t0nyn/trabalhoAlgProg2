#include "cabecalho.h"

void viatura_login_regular(node *viaturas, indiceOcorrencias &todes, node *policiais);
void viatura_estado_neutro(node *v, indiceOcorrencias &todas_ocorr);
void viatura_login_especializada(node *viaturas, indiceOcorrencias &todes, node *policiais);
void viatura_login(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
	int op;
	do
	{
		printf(
			"\n----SPM LOGIN VIATURA----\n"
			"1 - Policia Regular \n"
			"2 - Policia Especializada \n"
			"3 - Voltar ao Menu Principal \n");
		printf("Opcao: ");
		scanf("%d", &op);
		if (op == 1)
		{
			viatura_login_regular(vi, ocorr, pol);
			return;
			// printListPessoa(pess);
			// printListViatura(vi);
			// printListPolicia(pol);
		}
		else if (op == 2)
		{
			viatura_login_especializada(vi, ocorr, pol);
			return;
		}
		else if (op == 3)
			return;
	} while (op != 0);
}

void viatura_login_regular(node *viaturas, indiceOcorrencias &todes, node *policiais)
{
	int cod;
	printf("Codigo da Viatura: ");
	scanf("%d", &cod);

	node *viaturaExistente = buscarViatura(cod, viaturas);

	if (!viaturaExistente)
		return;
	viatura *v = (viatura *)viaturaExistente->data;
	if (strcasecmp(v->tipo, "regular"))
	{
		printf("A viatura informada nao eh do tipo regular.\n");
		return;
	}

	printf("Quantidade de PMs: ");
	scanf("%d", &v->numPoliciais);

	if (v->numPoliciais < 2 || v->numPoliciais > 4)
	{
		printf("Embarque negado.\n");
		return;
	}
	else
	{
		node **aux_policiais = (node **)malloc(v->numPoliciais * sizeof(node));
		char nomeGuerra[MAX + 1];
		for (int i = 0; i < v->numPoliciais; i++)
		{
			printf("Identificacao do PM: ");
			scanf(" %[^\n]", nomeGuerra);
			node *policialExistente = buscarPolicial(nomeGuerra, policiais);
			if (!policialExistente)
			{
				printf("Nome de Guerra informado nao existe.\n"
					   "Cancelando embarcacao.\n");
				return;
			}
			aux_policiais[i] = policialExistente;
		}
		v->policiais = aux_policiais;
		viatura_estado_neutro(viaturaExistente, todes);
	}
}

void viatura_login_especializada(node *viaturas, indiceOcorrencias &todes, node *policiais)
{
	int cod;
	printf("Codigo da Viatura: ");
	scanf("%d", &cod);

	node *viaturaExistente = buscarViatura(cod, viaturas);

	if (!viaturaExistente)
		return;
	viatura *v = (viatura *)viaturaExistente->data;
	if (strcasecmp(v->tipo, "especializada"))
	{
		printf("A viatura informada nao eh do tipo especializada.\n");
		return;
	}

	v->numPoliciais = 4;
	node **aux_policiais = (node **)malloc(v->numPoliciais * sizeof(node));
	char nomeGuerra[MAX + 1];
	for (int i = 0; i < v->numPoliciais; i++)
	{
		printf("Identificacao do PM: ");
		scanf(" %[^\n]", nomeGuerra);
		node *policialExistente = buscarPolicial(nomeGuerra, policiais);
		if (!policialExistente)
		{
			printf("Nome de Guerra informado nao existe.\n"
				   "Cancelando embarcacao.\n");
			return;
		}
		aux_policiais[i] = policialExistente;
	}
	v->policiais = aux_policiais;
	viatura_estado_neutro(viaturaExistente, todes);
}

void viatura_estado_neutro(node *v, indiceOcorrencias &todas_ocorr)
{
	printf(
		"\n----VIATURA ESTADO NEUTRO----\n"
		"1 - Apto para atender ocorrencia \n"
		"2 - Cancelar embarcacao \n");

	int op;
	scanf("%d", &op);
	viatura *aux = (viatura *)v->data;

	if (op == 1)
	{
		aux->estado = 1;
		for (int i = 0; i < aux->numPoliciais; i++)
		{
			node *poliExistente = aux->policiais[i];
			policial *poli = (policial *)poliExistente->data;
			poli->alocado = 1;
		}
		// printf("Viatura pronta para atender ocorrencia.\n");
		viaturaAtribuirChamado(aux, todas_ocorr);
		// aux->estado = 1;
		// int avaliacao; // 0 - Dispensada // 1 - Aceita
		// if (!strcasecmp("regular", aux->tipo))
		// {
		// 	if (todas_ocorr.chamadosPrioritarios)
		// 		avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosPrioritarios, aux);
		// 	if (todas_ocorr.chamadosRegulares && avaliacao != 1)
		// 		avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosRegulares, aux);
		// 	if (!avaliacao)
		// 		viatura_modo_ronda(aux);
		// }
		// else if (!strcasecmp("especializada", aux->tipo))
		// {
		// 	if (todas_ocorr.chamadosEspecializados)
		// 		avaliacao = avaliarOcorrencia(todas_ocorr.chamadosRegulares, aux);
		// 	if (!avaliacao)
		// 		viatura_modo_ronda(aux);
		// }
	}
	else if (op == 2)
	{
		printf("Embarcação cancelada com sucesso.\n");
		free(aux->policiais);
		aux->policiais = NULL;
	}
}

void viatura_modo_ronda(viatura *v)
{
	v->estado = 1;
	printf("Viatura direcionada para rondas, no aguardo de chamadas policiais.\n1- Voltar para o Menu principal.\n");
	char a;
	scanf(" %c", &a);
	return;
}

node *viaturasEmRonda(node *vi, char tipo[MAX + 1])
{
	int menor = 100;
	node *menorViatura = NULL;

	for (; vi != NULL; vi = vi->next)
	{
		viatura *p = (viatura *)vi->data;
		if (p->estado == 1 && !strcasecmp(tipo, p->tipo))
		{
			if (p->numOcorrencias < menor)
				menorViatura = vi;
		}
	}

	return menorViatura;
}

void viaturaAtribuirChamado(viatura *aux, indiceOcorrencias &todas_ocorr)
{
	addNode(todas_ocorr.viaturaDia, aux);
	for (int i = 0; i < aux->numPoliciais; i++)
	{
		// printPolicial(aux->policiais[i]->data);
		addNode(todas_ocorr.policialDia, aux->policiais[i]->data);
	}
	int decider = avaliarListaReforcos(todas_ocorr.chamadosReforcos, aux);

	if (!decider)
	{
		int avaliacao = 0; // 0 - Dispensada // 1 - Aceita
		if (!strcasecmp("regular", aux->tipo))
		{
			if (todas_ocorr.chamadosPrioritarios)
				avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosPrioritarios, aux);
			if (todas_ocorr.chamadosRegulares && avaliacao != 1)
				avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosRegulares, aux);
			if (!avaliacao)
			{
				viatura_modo_ronda(aux);
			}
			else
			{
				printf("Chamado atribuido com sucesso.\n");
			}
		}
		else if (!strcasecmp("especializada", aux->tipo))
		{
			if (todas_ocorr.chamadosEspecializados)
			{
				avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosEspecializados, aux);
			}
			if (!avaliacao)
			{
				viatura_modo_ronda(aux);
			}
			else
			{
				printf("Chamado atribuido com sucesso.\n");
			}
		}
	}
}