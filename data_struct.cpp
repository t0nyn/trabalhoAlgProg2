#include "cabecalho.h"

void addNode(node *&list, void *dt)
{
	node *newNode = (node *)malloc(sizeof(node));
	newNode->next = list;
	newNode->data = dt;
	list = newNode;
}


void addFim(node *&list, void *dt)
{
	node *p = list;

	node *novo = (node *)malloc(sizeof(node));
	novo->next = NULL;
	novo->data = dt;
	if (!list)
	{
		list = novo;
		return;
	}
	while (p->next)
		p = p->next;
	p->next = novo;
}

node *popInicio(node *&list)
{

	if (!list)
		return NULL;
	node *aux = list;
	list = list->next;
	return aux;
}

int count(node *list){
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return count;
}

void desalocar_pessoa(node *pess){
	node * passagem;
	node * inadimplencia;
	pessoa * temp_pessoa;
	void * temp_string;
	node * temp_pessoa_node = popInicio(pess);

	while(temp_pessoa_node){
		temp_pessoa = (pessoa *) temp_pessoa_node->data;
		if(temp_pessoa->passagens){
			passagem = popInicio(temp_pessoa->passagens);
			while(passagem){
				temp_string = passagem->data;
				if(temp_string){
					free(temp_string);
				}
				free(passagem);
				passagem = popInicio(temp_pessoa->passagens);
			}
			temp_string = NULL;
		}
		if(temp_pessoa->inadimplencias){
			inadimplencia = popInicio(temp_pessoa->inadimplencias);
			while(inadimplencia){
				temp_string = inadimplencia->data;
				if(temp_string){
					free(temp_string);
				}
				free(inadimplencia);
				
				inadimplencia = popInicio(temp_pessoa->inadimplencias);
			}
		}
		free(temp_pessoa_node);
		temp_pessoa_node = popInicio(pess);
	}
}

void desalocar_policia(node * pol){
	void * temp_policial;
	node * temp_policial_node = popInicio(pol);
	while(temp_policial_node){
		temp_policial = temp_policial_node->data;
		free(temp_policial_node);
		free(temp_policial);
		temp_policial_node = popInicio(pol);
	}

}

void desalocar_ocorrencia(node * ocorr){
	ocorrencia * temp_ocorrencia;
	node * temp_policial_node;
	node * temp_viatura_node;
	node * temp_preso_node;

	node * temp_ocorrencia_node = popInicio(ocorr);
	while(temp_ocorrencia_node){
		temp_ocorrencia = (ocorrencia *)temp_ocorrencia_node->data;
		
		if(temp_ocorrencia->policiais){
			temp_policial_node = popInicio(temp_ocorrencia->policiais);
			while(temp_policial_node){
				//Nesse momento nao e preciso desalocar o data
				//Pois o policial ja foi desalocado em desalocar_policial()
				free(temp_policial_node);
				temp_policial_node = popInicio(temp_ocorrencia->policiais);
			}
		}

		if(temp_ocorrencia->viaturas){
			temp_viatura_node = popInicio(temp_ocorrencia->viaturas);
			while(temp_viatura_node){
				//Nesse momento nao e preciso desalocar o data
				//Pois a viatura sera desalocada em desalocar_viatura()
				free(temp_viatura_node);
				temp_viatura_node = popInicio(temp_ocorrencia->viaturas);
			}
		}

		if(temp_ocorrencia->presos){
			temp_preso_node = popInicio(temp_ocorrencia->presos);
			while(temp_preso_node){
				//Nesse momento nao e preciso desalocar o data
				//Pois a pessoa foi desalocada em desalocar_pessoa()
				free(temp_preso_node);
				temp_preso_node = popInicio(temp_ocorrencia->presos);
			}
		}
		
		int n = temp_ocorrencia->qtdViaturas;
		free(temp_ocorrencia);
		free(temp_ocorrencia_node);

		for (int i = 0; i < n - 1; i++)
		{
			temp_ocorrencia_node = popInicio(ocorr);
			free(temp_ocorrencia_node);
		}
		
		temp_ocorrencia_node = popInicio(ocorr);
	}
}

void desalocar_viatura(node * vi){
	viatura * temp_viatura;
	node * temp_ocorrencia_node;
	node * temp_viatura_node = popInicio(vi);
	while(temp_viatura_node){
		temp_viatura = (viatura *)temp_viatura_node->data;
		free(temp_viatura_node);

		if(temp_viatura->policiais)
			free(temp_viatura->policiais);

		temp_ocorrencia_node = popInicio(temp_viatura->ocorrencia);
		while(temp_viatura->ocorrencia){
			//Nesse momento nao e preciso desalocar o data
			//Pois a ocorrencia foi desalocada em desalocar_ocorrencia();
			free(temp_ocorrencia_node);
			temp_ocorrencia_node = popInicio(temp_viatura->ocorrencia);
		}

		free(temp_viatura);
		temp_viatura_node = popInicio(vi);
	}
}

void desalocar(node *pess, node *pol, node *vi, indiceOcorrencias &ocorr){
	desalocar_pessoa(pess);
	desalocar_policia(pol);
	desalocar_ocorrencia(ocorr.chamadosAtendidos);
	desalocar_ocorrencia(ocorr.chamadosEspecializados);
	desalocar_ocorrencia(ocorr.chamadosPrioritarios);
	desalocar_ocorrencia(ocorr.chamadosRegulares);
	desalocar_ocorrencia(ocorr.chamadosReforcos);
	desalocar_viatura(vi);
	printf("\n\n Programa encerrado! \n\n");
}