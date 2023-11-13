#include "cabecalho.h"

void gerar_oficio_ocorrencias(char nome[MAX + 1], indiceOcorrencias &ocorr);

void comandante_geral(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
    policial *login = policial_login(pol, 3);

    if (login)
    {
        int op;
        do
        {
            printf(
                "\n----------SPM----------\n"
                "1 - Gerar oficio de ocorrencias \n"
                "2 - Voltar ao Menu Principal \n");
            printf("Opcao: ");
            scanf("%d", &op);
            if (op == 1)
                gerar_oficio_ocorrencias(login->nome, ocorr);
            else if (op == 2)
                return;
        } while (op != 0);
    }
}

void gerar_oficio_ocorrencias(char nome[MAX + 1], indiceOcorrencias &ocorr)
{
    node *listaOcorrenciasAtendidas = ocorr.chamadosAtendidos;

    if (!listaOcorrenciasAtendidas)
    {
        printf("\n Sem ocorrencias para gerar oficio\n");
        return;
    }

    char path[MAX + 1] = "./oficio de ocorrencias ";
    char fim[MAX + 1] = ".txt";
    strcat(path, nome);
    strcat(path, fim);

    FILE *fl = fopen(path, "w");

    fprintf(fl, "Ocorrencias -");

    while (listaOcorrenciasAtendidas)
    {
        ocorrencia *ocorr = (ocorrencia *)listaOcorrenciasAtendidas->data;
        fprintf(fl, "   Tipo de Policia: .%s\n", ocorr->tipo == 3 ? "Especializada" : "Regular");
        fprintf(fl, "   %s - %s\n", ocorr->desc, ocorr->loc);
        fprintf(fl, "   Policiais:\n");
        node *aux_policiais = ocorr->policiais;
        while (aux_policiais)
        {
            fprintf(fl, "       %s\n", ((policial *)aux_policiais->data)->nomeGuerra);
            aux_policiais = aux_policiais->next;
        }
        node *aux_presos = ocorr->presos;
        if (aux_presos)
        {
            fprintf(fl, "   Presos:\n");
            while (aux_presos)
            {
                fprintf(fl, "       %s\n", ((pessoa *)aux_presos->data)->nome);
                aux_presos = aux_presos->next;
            }
        }
        fprintf(fl, "\n\n");

        listaOcorrenciasAtendidas = listaOcorrenciasAtendidas->next;
    }

    printf("Oficio de ocorrencias gerado!\n");
    fclose(fl);
}