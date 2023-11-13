#include "cabecalho.h"

void gerar_relatorio_oficial(char nome[MAX + 1], indiceOcorrencias &ocorr);

void oficial(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
    policial *login = policial_login(pol, 2);

    if (login)
    {
        int op;
        do
        {
            printf(
                "\n----------SPM----------\n"
                "1 - Excluir Boletim de Ocorrencia \n"
                "2 - Gerar relatorio oficial \n"
                "3 - Voltar ao Menu Principal \n");
            printf("Opcao: ");
            scanf("%d", &op);
            if (op == 1)
                excluir_boletim_ocorrencia(ocorr.chamadosAtendidos);
            else if (op == 2)
                gerar_relatorio_oficial(login->nome, ocorr);
            else if (op == 3)
                return;
        } while (op != 0);
    }
}

void gerar_relatorio_oficial(char nome[MAX + 1], indiceOcorrencias &ocorr)
{
    node *listaPoliciais = ocorr.policialDia;
    node *listaViaturas = ocorr.viaturaDia;

    if (!listaViaturas)
    {
        printf("\n Sem viaturas e policiais no dia!\n");
        return;
    }

    char path[MAX + 1] = "./relatorio oficial ";
    char fim[MAX + 1] = ".txt";

    strcat(path, nome);
    strcat(path, fim);

    int nPolicial = count(ocorr.policialDia);
    policial **ArrayPoliciais = (policial **)malloc(sizeof(policial *) * nPolicial);

    for (int i = 0; i < nPolicial; i++)
    {
        ArrayPoliciais[i] = (policial *)listaPoliciais->data;
        listaPoliciais = listaPoliciais->next;
    }

    quicksort(ArrayPoliciais, 0, nPolicial - 1);

    FILE *fl = fopen(path, "w");

    fprintf(fl, "PMs - \n");
    for (int i = 0; i < nPolicial; i++)
    {
        fprintf(fl, "%s \n", ArrayPoliciais[i]->nome);
    }
    fprintf(fl, "\nViaturas - \n");

    while (listaViaturas != NULL)
    {
        // viatura *v =  listaViaturas->data;
        fprintf(fl, "V%3d\n", ((viatura *)listaViaturas->data)->cod);
        listaViaturas = listaViaturas->next;
    }
    printf("Relatorio gerado!\n");
    fclose(fl);
}

void excluir_boletim_ocorrencia(node *ocorr)
{
    node *aux = ocorr;
    int op;

    while (aux)
    {
        ocorrencia *aux_ocorr = (ocorrencia *)aux->data;

        if (aux_ocorr->boletimCriado)
        {
            printOcorrencia(aux);
            printf("Descricao: %s\n", aux_ocorr->boletimOcorrencia);
            printf("Deseja excluir esse Boletim de Ocorrencia? 1-sim 0-nao\n");
            scanf("%d", &op);

            if (op)
            {
                aux_ocorr->boletimCriado = 0;
                strcpy(aux_ocorr->boletimOcorrencia, "");
                printf("Boletim removido com sucesso.\n");
                break;
            }
        }
        aux = aux->next;
    }
}