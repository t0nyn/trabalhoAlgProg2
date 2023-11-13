#include "cabecalho.h"
// #include "viatura_login.h"
#include "cabecalho.h"
#include "cabecalho.h"
#include "cabecalho.h"
#include "cabecalho.h"

// testando o git
// teste
int main(int argc, char const *argv[])
{
	node *viaturas = NULL;
	node *pessoas = NULL;
	node *policiais = NULL;

	indiceOcorrencias ocorrencias;
	ocorrencias.chamadosRegulares = NULL;
	ocorrencias.chamadosEspecializados = NULL;
	ocorrencias.chamadosPrioritarios = NULL;
	ocorrencias.chamadosAtendidos = NULL;
	ocorrencias.chamadosReforcos = NULL;
	ocorrencias.policialDia = NULL;
	ocorrencias.viaturaDia = NULL;

	loadViaturas(viaturas);
	loadPessoas(pessoas);
	loadPolicial(policiais);
	// printListPessoa(pessoas);
	// printListViatura(viaturas);
	// printListPolicia(policiais);

	int op;
	do
	{
		printf(
			"\n----------SPM----------\n"
			"1 - Viatura login \n"
			"2 - Viatura em uso \n"
			"3 - COPOM \n"
			"4 - Policial Militar \n"
			"5 - Oficial \n"
			"6 - Comandante Geral \n"
			"0 - Encerrar Programa \n");
		printf("Opcao: ");
		scanf(" %d", &op);
		if (op == 1)
			viatura_login(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 2)
			viatura_uso(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 3)
			copom(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 4)
			policial_militar(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 5)
			oficial(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 6)
			comandante_geral(pessoas, policiais, viaturas, ocorrencias);
		else if (op == 0){
			desalocar(pessoas, policiais, viaturas, ocorrencias);
			return 0;
		}
	} while (op != 0);

	return 0;
}