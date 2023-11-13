#include "cabecalho.h"

void policial_militar(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
    policial *login = policial_login(pol, 1);

    if (login)
    {
        printf("LOGADO!\n");

        node *aux = ocorr.chamadosAtendidos;
        while (aux)
        {
            ocorrencia *aux2 = (ocorrencia *)aux->data;
            node *aux3 = aux2->policiais;

            while (aux3)
            {
                policial *aux_pol = (policial *)aux3->data;
                if (!strcasecmp(aux_pol->nomeGuerra, login->nomeGuerra) && !aux2->boletimCriado)
                {
                    printOcorrencia(aux);
                    int op;
                    printf("Deseja escrever um boletim dessa ocorrencia? 1-sim 0-nao\n");
                    scanf("%d", &op);
                    if (op)
                    {
                        printf("Escreva o boletim de ocorrencia:\n");
                        scanf(" %[^\n]", aux2->boletimOcorrencia);
                        aux2->boletimCriado = 1;
                    }
                }
                aux3 = aux3->next;
            }
            aux = aux->next;
        }
    }
}

// void pm_visualizar_ocorr(node *vi, policial *pol)
// {
//     viatura *aux = (viatura *)vi->data;
//     node *aux_ocorr = aux->ocorrencia;

//     while (aux_ocorr)
//     {
//         ocorrencia *ocorr_atual = (ocorrencia *)aux_ocorr->data;
//         for (int i = 0; i < aux->numPoliciais; i++)
//     }
// }