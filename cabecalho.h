#ifndef TIPOS_H
#define TIPOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ESTRUTURAS DE DADOS
typedef struct node
{
	void *data;
	node *next;
} node;
void addNode(node *&list, void *dt);
node *popInicio(node *&list);
void addFim(node *&list, void *dt);
int count(node *list);

// PESSOAS
typedef struct pessoa
{
	char nome[MAX + 1];
	char cpf[MAX + 1];
	char cidade[MAX + 1];
	int idade;
	int numPassagens;
	node *passagens = NULL;
	int numInadimplencias;
	node *inadimplencias = NULL;
} pessoa;
void loadPessoas(node *&list);
void printPessoa(void *v);
void printListPessoa(node *list);
pessoa *pessoaBuscarPorCpf(node *list, char cpf[MAX + 1]);

// POLICIA
typedef struct policial
{
	char nome[MAX + 1];
	char cpf[MAX + 1];
	char nomeGuerra[MAX + 1];
	char cidade[MAX + 1];
	char cargo[MAX + 1];
	char senha[MAX + 1];
	int idade;
	int alocado;
} policial;
void loadPolicial(node *&list);
void printPolicial(void *v);
void printListPolicia(node *list);
node *buscarPolicial(char nomeGuerra[MAX + 1], node *list);

// VIATURA
typedef struct viatura
{
	int cod;
	char tipo[MAX + 1];
	int numPoliciais;
	node **policiais;
	int estado;
	// ESTADOS POSSIVEIS:
	// 0 - Nao foi alocada
	// 1 - Em ronda
	// 3 - Prisao em andamento
	// 4 - Chamada atribuida
	// 5 - prestando reforco
	int numOcorrencias;
	node *ocorrencia;
} viatura;
void printViatura(void *v);
void printListViatura(node *list);
void loadViaturas(node *&list);
node *buscarViatura(int cod, node *list);
node *buscarPonteiroViatura(int cod, node *list);

// OCORRENDCIA
typedef struct ocorrencia
{
	int tipo; // 1-Regular, 2-Prioritario, 3-Especializada
	char desc[MAX + 1];
	char loc[MAX + 1];
	char boletimOcorrencia[1000];
	int qtdViaturas;
	node *viaturas;
	node *policiais;
	node *presos;
	int reforco;	   // 2-refAprovado 1-Sim 0-Nao
	int boletimCriado; // 1-sim 0-nao
} ocorrencia;

typedef struct
{
	node *chamadosRegulares;
	node *chamadosEspecializados;
	node *chamadosPrioritarios;
	node *chamadosAtendidos;
	node *chamadosReforcos;
	node *policialDia;
	node *viaturaDia;

} indiceOcorrencias;
void printOcorrencia(node *v);
void excluir_boletim_ocorrencia(node *ocorr);

// VIATURA LOGIN
void viatura_login(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);
void viatura_modo_ronda(viatura *v);
void viaturaAtribuirChamado(viatura *aux, indiceOcorrencias &todas_ocorr);

// VIATURA
int avaliarListaOcorrencias(node *&ocorrencias, viatura *viatura);
int avaliarOcorrencia(node *&todas_ocorr, node *ocorr, viatura *vi);
void avaliarReforco(node *&ocorrencias);
int avaliarListaReforcos(node *&ocorrencias, viatura *vi);

// VIATURA EM USO
void viatura_uso(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);
void viatura_ocorrencia(node *pess, node *pol, indiceOcorrencias &ocorr, viatura *vi);
void viaturaBuscarCPF(node *list);
void solicitar_reforco(ocorrencia *ocorr, indiceOcorrencias &todas_ocorr);

// COPOM
void copom(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);

//  Policial
policial *policial_login(node *pol, int tipo);
node *buscarPolicialExistente(char nomeGuerra[MAX + 1], node *list);
node *viaturasEmRonda(node *vi, char tipo[MAX + 1]);

// POLICIAL MILITAR
void policial_militar(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);

// OFICIAL
void oficial(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);

// COMANDANTE GERAL
void comandante_geral(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);

// QuickSort
void quicksort(policial **arr, int low, int high);


void desalocar(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr);
#endif