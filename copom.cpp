#include "cabecalho.h"

void printOcorrencia(node *v)
{
    ocorrencia *aux = (ocorrencia *)v->data;
    printf("\n-------SPM-Ocorrencia-------\n");
    printf("Descricao: %s\nLocalizacao: %s\n", aux->desc, aux->loc);
}

void copom(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
    avaliarReforco(ocorr.chamadosReforcos);

    char prioritario;

    ocorrencia *nova_ocorrencia = (ocorrencia *)malloc(sizeof(ocorrencia));

    printf(
        "\n-------COPOM-------\n");
    printf("Policia Normal - 1   Policia Especializada - 2: ");
    scanf("%d", &nova_ocorrencia->tipo);
    printf("Quantidade de viaturas: ");
    scanf("%d", &nova_ocorrencia->qtdViaturas);
    printf("Descricao: ");
    scanf(" %[^\n]", nova_ocorrencia->desc);
    printf("Localizacao: ");
    scanf(" %[^\n]", nova_ocorrencia->loc);
    nova_ocorrencia->reforco = 0;
    nova_ocorrencia->boletimCriado = 0;

    if (nova_ocorrencia->tipo == 1)
    {
        // node *aux2 = viaturasEmRonda(vi, "regular");
        // viatura *aux = (viatura *)aux2->data;
        // if (aux2)
        // {
        //     aux->ocorrencia = (node *)nova_ocorrencia;
        //     return;
        // }

        char viTipo[] = "regular";
        printf("E uma chamada prioritaria?(s/n)");
        scanf(" %c", &prioritario);
        if (prioritario == 's')
        {
            for (int i = 0; i < nova_ocorrencia->qtdViaturas; i++)
            {
                addFim(ocorr.chamadosPrioritarios, nova_ocorrencia);
            }
            node *aux2 = viaturasEmRonda(vi, viTipo);
            if (!aux2)
            {
                printf("nope\n");
                printf("Sem viaturas em ronda disponiveis.\n");
                return;
            }
            viatura *aux = (viatura *)aux2->data;
            if (aux)
            {
                aux->ocorrencia = popInicio(ocorr.chamadosPrioritarios);
                for (int i = 0; i < aux->numPoliciais; i++)
                {
                    ocorrencia *aux212 = (ocorrencia *)aux->ocorrencia->data;
                    addNode(aux212->policiais, aux->policiais[i]->data);
                }
                printf("Chamada atribuida com sucesso para a viatura %03d\n", aux->cod);
                aux->estado = 4;
                return;
            }
        }
        else
        {
            for (int i = 0; i < nova_ocorrencia->qtdViaturas; i++)
            {
                addFim(ocorr.chamadosRegulares, nova_ocorrencia);
            }
            node *aux2 = viaturasEmRonda(vi, viTipo);
            if (!aux2)
            {
                printf("Sem viaturas em ronda disponíveis.\n");
                return;
            }
            else
            {
                viatura *aux = (viatura *)aux2->data;
                aux->ocorrencia = popInicio(ocorr.chamadosRegulares);
                for (int i = 0; i < aux->numPoliciais; i++)
                {
                    ocorrencia *aux212 = (ocorrencia *)aux->ocorrencia->data;
                    addNode(aux212->policiais, aux->policiais[i]->data);
                }
                printf("Chamada atribuida com sucesso para a viatura %03d\n", aux->cod);
                aux->estado = 4;
                return;
            }
        }
    }
    else if (nova_ocorrencia->tipo == 2)
    {
        char viTipo[] = "especializada";
        for (int i = 0; i < nova_ocorrencia->qtdViaturas; i++)
        {
            addFim(ocorr.chamadosEspecializados, nova_ocorrencia);
        }
        node *aux2 = viaturasEmRonda(vi, viTipo);
        if (!aux2)
        {
            printf("Sem viaturas especializadas disponíveis.\n");
            return;
        }
        viatura *aux = (viatura *)aux2->data;
        if (aux2)
        {
            aux->ocorrencia = popInicio(ocorr.chamadosEspecializados);
            for (int i = 0; i < aux->numPoliciais; i++)
            {
                ocorrencia *aux212 = (ocorrencia *)aux->ocorrencia->data;
                addNode(aux212->policiais, aux->policiais[i]->data);
            }
            printf("Chamada atribuida com sucesso para a viatura %03d\n", aux->cod);
            aux->estado = 4;
            return;
        }
    }
}
