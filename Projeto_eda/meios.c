#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"
#include "grafos.h"

/// @brief Esta funcao adiciona um novo meio à lista ligada. Ela utiliza uma função auxiliar que atribui automaticamente o ID
/// @param auxM endereço do topo da lista dos meios
/// @param ID ID do novo meio
/// @param nome tipo do novo meio
/// @param localizacao localizacao onde se encontra o novo meio
/// @param bateria bateria restante do novo meio
/// @param autonomia autonomia restante do novo meio
/// @param custo custo de aluguer de um novo meio
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o novo meio adicionado no topo
RM* adicionarMeio(RM* auxM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo, int alugado, int NIF, time_t tempoinicial)
{
	RM* novo = malloc(sizeof(RM));
    RM* topoM = auxM;

    novo->ID = ID;
	strcpy(novo->nome, nome);
	strcpy(novo->localizacao, localizacao);
	novo->bateria = bateria;
	novo->autonomia = autonomia;
    novo->custo = custo;
    novo->alugado = alugado;
    novo->NIF = NIF;
    novo->tempoinicial = tempoinicial;

    if(topoM != NULL) novo->seguinte = topoM;
    else novo->seguinte = NULL;

	return novo;
}

/// @brief Esta função permite a um gestor alterar o custo de aluguer de um certo meio
/// @param auxM endereço do topo da lista dos meios
/// @param ID ID do meio que desejamos alterar o valor
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o custo do meio alterado
RM* editarMeio(RM* auxM, int ID)
{
    float custo;
    RM* topoM = auxM;

    limparTela();
    printf("Introduza o novo custo que deseja para o aluguer do veiculo:\n");
    scanf("%f", &custo);

    if(topoM != NULL)
    {
        while(topoM != NULL)
        {
            if(topoM->ID == ID)
            {
                topoM->custo = custo;
            }
            topoM = topoM->seguinte;
        }
    }
    else
    {
        printf("Nao ha nenhum veiculo registrado para alterar.\n");
    }
    return auxM;
}

/// @brief Esta funcao utiliza uma variavel auxiliar. Ela vai percorrendo a lista até achar o ID igual ao do meio que desejamos remover no endereço seguinte da lista para então o podermos remover
/// @param auxM endereço do topo da lista dos meios
/// @param ID ID do meio que desejamos remover
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o meio removido
RM* removerMeio(RM* auxM, int ID)
{
        RM* anterior = auxM, *atual = auxM, *aux;

        if (atual == NULL){
            return(NULL);
        }
        else if (atual->ID == ID) 
        {
            aux = atual->seguinte;
            free(atual);
            return(aux);
        }
        else
        {
            for (atual; atual != NULL && atual->ID != ID;atual=atual->seguinte){

                anterior = atual;

            }
                if (atual == NULL) {
                    return(auxM);
                }
                else
                {
                    anterior->seguinte = atual->seguinte;
                    free(atual);
                    return(auxM);
                }
        }
}

/// @brief Esta função ordena os meios por quantidade de bateria, de maneira decrescente
/// @param auxM endereço do topo da lista dos meios
void ordenarMeios(RM** auxM)
{
    int trocado = 1;
    RM** topoM = &(*auxM);
    if ((*auxM) != NULL){
        while (trocado) 
        {
            trocado = 0;
            RM* anterior = NULL;
            RM* atual = (*topoM);
            while (atual->seguinte != NULL) 
            {
                if (atual->autonomia < atual->seguinte->autonomia) 
                {
                    RM* proximo = atual->seguinte;
                    atual->seguinte = proximo->seguinte;
                    proximo->seguinte = atual;
                    if (anterior != NULL)
                    {
                        anterior->seguinte = proximo;
                    } else 
                    {
                        (*topoM) = proximo;
                    }
                    anterior = proximo;
                    trocado = 1;
                } 
                else 
                {
                    anterior = atual;
                    atual = atual->seguinte;
                }
            }
        }
        listarMeios(*topoM);
    }else   printf("\nA lista esta vazia\n");
}

/// @brief Esta funcao percorre a lista dos meios e vai imprimindo as informações no terminal
/// @param auxM endereço do topo da lista dos meios
void listarMeios(RM* auxM)
{
    RM* topoM = auxM;
	if (topoM != NULL)
	{
		limparTela();
		while (topoM != NULL)
		{
            if(topoM->alugado == 0)
            {
                printf("ID - %d\nTipo - %s\nLocalizacao - %s\nBateria - %.2f\nAutonomia - %2.f\nCusto - %.2f\n\n", topoM->ID, topoM->nome, topoM->localizacao, topoM->bateria, topoM->autonomia, topoM->custo);
            }
			topoM = topoM->seguinte;
		}
		enterContinuar();
	}
	else
	{
		limparTela();
		printf("Nao existem meios registrados.\n");
		enterContinuar();
	}
}

int listarMeiosAlugados(RM* auxM, int NIF)
{
    RM* topoM = auxM, *aux = NULL;


    while(topoM != NULL)
    {
        if(topoM->alugado == 1 && topoM->NIF == NIF)
        {
            aux = adicionarMeio(aux, topoM->ID, topoM->nome, topoM->localizacao, topoM->bateria, topoM->autonomia, topoM->custo, topoM->alugado, topoM->NIF, topoM->tempoinicial);
        }
        topoM = topoM->seguinte;
    }

    if(aux != NULL)
    {
        limparTela();
		while (aux != NULL)
		{
            printf("ID - %d\nTipo - %s\nLocalizacao - %s\nBateria - %.2f\nAutonomia - %2.f\nCusto - %.2f\n\n", aux->ID, aux->nome, aux->localizacao, aux->bateria, aux->autonomia, aux->custo);
			aux = aux->seguinte;
		}
		enterContinuar();
        return 1;
    }
    else 
    {
        limparTela();
        printf("Não há meios alugados por si\n");
        enterContinuar();
        return 0;
    }
}

/// @brief Esta função atribui automaticamente um ID para cada meio, por ordem crescente
/// @param auxM endereço do topo da lista dos meios
/// @return atribui um valor do tipo int, que é o novo ID para o meio
int darID(RM* auxM)
{
    RM* topoM = auxM;

    if(topoM != NULL)
    {
        int ID = 0;

        while(topoM != NULL)
        {
            if(topoM->ID > ID) ID = topoM->ID;
            topoM = topoM->seguinte;
        }
        return ++ID;
    }
    else return 1;
}

/// @brief Esta função permite adionar um novo registo de aluguer à lista ligada
/// @param auxA endereço do topo da lista dos alugueres
/// @param auxM endereço do topo da lista do meio que foi alugado
/// @param NIF NIF do cliente que alugou um meio
/// @return retorna um valor do tipo apontador para RA, sendo este o endereço do topo da lista com o aluguer adicionado
RA* adicionarAluguer(RA* auxA, RM* auxM, int NIF, time_t final)
{
    RM* topoM = auxM;
    RA* topoA = auxA;
	RA* novo = malloc(sizeof(RA));
    
    novo->ID = topoM->ID;
    strcpy(novo->nome,topoM->nome);
    strcpy(novo->localizacao,topoM->localizacao);
    novo->bateria = topoM->bateria;
    novo->autonomia = topoM->autonomia;
    novo->custo = topoM->custo * ((double)(final - topoM->tempoinicial) / 60);
    novo->NIF = NIF;
    novo->tempoinicial = topoM->tempoinicial;
    novo->tempofinal = final;

    if(topoA != NULL) novo->seguinte = topoA;
    else novo->seguinte = NULL;

	return novo;
}
