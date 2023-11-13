#include "cabecalho.h"

void encerrar_ocorrencia(viatura *vi, indiceOcorrencias &ocorr);
void prisao_andamento(viatura *vi, node *listPessoas, indiceOcorrencias &ocorr);

void viatura_uso(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr)
{
    int id;

    printf(
        "\n----------Viatura em Uso----------\n"
        "1 - Identificador da Viatura: \n");

    scanf("%d", &id);

    node *viaturo = buscarPonteiroViatura(id, vi);
    viatura *aux = (viatura *)viaturo->data;

    if (!viaturo)
    {
        printf("Viatura não encontrada.\n");
    }
    else if (aux->estado == 1)
    {
        // printf("Viatura em modo ronda.\n");
        viaturaAtribuirChamado(aux, ocorr);
    }
    else if (aux->estado == 4)
    {
        viatura_ocorrencia(pess, pol, ocorr, aux);
    }
    else if (aux->estado == 5)
    {
        printf("Viatura atendendo reforco.\n");
        viatura_ocorrencia(pess, pol, ocorr, aux);
    }
}

void viatura_ocorrencia(node *pess, node *pol, indiceOcorrencias &ocorr, viatura *vi)
{
    int op;
    // do
    // {
    printf(
        "\n----------SPM Viatura Ocorrencia----------\n"
        "1 - Pesquisar por CPF \n"
        "2 - Solicitar Reforcos \n"
        "3 - Prisao em Andamento \n"
        "4 - Encerrar Ocorrencia \n"
        "5 - Voltar para o Menu Principal \n"
        "0 - Encerrar Programa \n");
    printf("Opcao: ");
    scanf("%d", &op);
    if (op == 1)
        viaturaBuscarCPF(pess);
    else if (op == 2)
    {
        ocorrencia *aux_ocorr = (ocorrencia *)vi->ocorrencia->data;
        solicitar_reforco(aux_ocorr, ocorr);
    }
    else if (op == 3)
        prisao_andamento(vi, pess, ocorr);
    else if (op == 4)
        encerrar_ocorrencia(vi, ocorr);
    else if (op == 5)
        return;
    // } while (op != 0);
}

void viaturaBuscarCPF(node *list)
{

    char *CPF = (char *)calloc(MAX + 1, sizeof(char));
    printf("CPF: ");
    scanf(" %[^\n]", CPF);

    pessoa *p = pessoaBuscarPorCpf(list, CPF);
    if (!p)
    {
        printf("CPF nao encontrado");
        free(CPF);
        return;
    }
    printPessoa(p);

    int num;
    printf("1 - Encerrar vizualização");
    scanf("%d", &num);
    free(CPF);
}
void prisao_andamento(viatura *vi, node *listPessoas, indiceOcorrencias &ocorr)
{

    if (vi->estado == 3)
    {
        int op;
        printf(
            "\n----------SPM Viatura Ocorrencia----------\n"
            "1 - Confirmar retorno da DP \n"
            "2 - Voltar ao Menu Principal \n");
        scanf("%d", &op);
        if (op == 2)
            return;
        encerrar_ocorrencia(vi, ocorr);
    }
    else
    {
        vi->estado = 3;
        int n;
        char *CPF = (char *)calloc(MAX + 1, sizeof(char));
        printf("\n----------SPM Viatura: Prisao em Andamento----------\n");
        printf("Individuo(s) conduzido(s) para DP:");
        scanf("%d", &n);
        ocorrencia *aux_ocorr = (ocorrencia *)vi->ocorrencia->data;

        // aux_ocorr->presos = (pessoa **)malloc(sizeof(pessoa *) * n);
        printf("CPFs \n");
        for (int i = 0; i < n; i++)
        {
            scanf(" %[^\n]", CPF);
            pessoa *cabra = pessoaBuscarPorCpf(listPessoas, CPF);
            if (cabra)
            {
                // aux_ocorr->presos[i] = cabra;
                addNode(aux_ocorr->presos, cabra);
            }
            else
            {
                printf("CPF nao encontrado! Digite novamente\n");
                i--;
            }
        }
        prisao_andamento(vi, listPessoas, ocorr);
    }
}

void solicitar_reforco(ocorrencia *ocorr, indiceOcorrencias &todas_ocorr)
{
    int op;
    printf("\n----------SPM Viatura: Solicitar Reforcos----------\n"
           "1-Confirmar Solicitacao de Reforcos\n"
           "2-Cancelar\n");
    scanf("%d", &op);

    if (op == 1)
    {
        ocorr->reforco = 1;
        addNode(todas_ocorr.chamadosReforcos, ocorr);
        printf("Pedido de reforco solicitado.\n");
    }
}

void encerrar_ocorrencia(viatura *vi, indiceOcorrencias &ocorr)
{
    // vi->ocorrencia->next = ocorr.chamadosAtendidos;
    // ocorr.chamadosAtendidos = vi->ocorrencia;
    addNode(ocorr.chamadosAtendidos, vi->ocorrencia->data);

    vi->estado = 1;
    vi->ocorrencia = NULL;

    printf("Viatura voltou ao modo ronda.");
}

// void atender_reforco(viatura *aux, indiceOcorrencias &todas_ocorr)
// {
//     int avaliacao = 0; // 0 - Dispensada // 1 - Aceita
//     if (todas_ocorr.chamadosReforcos)
//         avaliacao = avaliarListaOcorrencias(todas_ocorr.chamadosReforcos, aux);
// }
