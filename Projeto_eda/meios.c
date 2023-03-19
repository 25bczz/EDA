#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

/// @brief Esta funcao adiciona um novo meio à lista ligada. Ela utiliza uma função auxiliar que atribui automaticamente o ID
/// @param topoM endereço do topo da lista dos meios
/// @param ID ID do novo meio
/// @param nome tipo do novo meio
/// @param localizacao localizacao onde se encontra o novo meio
/// @param bateria bateria restante do novo meio
/// @param autonomia autonomia restante do novo meio
/// @param custo custo de aluguer de um novo meio
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o novo meio adicionado no topo
RM* adicionarMeio(RM* topoM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo)
{
	RM* novo = malloc(sizeof(RM));

    novo->ID = ID;
	strcpy(novo->nome, nome);
	strcpy(novo->localizacao, localizacao);
	novo->bateria = bateria;
	novo->autonomia = autonomia;
    novo->custo = custo;
    novo->alugado = 0;

    if(topoM != NULL) novo->seguinte = topoM;
    else novo->seguinte = NULL;

	return novo;
}

/// @brief Esta função permite a um gestor alterar o custo de aluguer de um certo meio
/// @param topoM endereço do topo da lista dos meios
/// @param ID ID do meio que desejamos alterar o valor
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o custo do meio alterado
RM* editarMeio(RM* topoM, int ID)
{
    float custo;

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
        printf("Nao ha nenhum veiculo registrado para alterar.");
    }
    return topoM;
}

/// @brief Esta funcao utiliza uma variavel auxiliar. Ela vai percorrendo a lista até achar o ID igual ao do meio que desejamos remover no endereço seguinte da lista para então o podermos remover
/// @param topoM endereço do topo da lista dos meios
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com o meio removido
RM* removerMeio(RM* topoM, int ID)
{
	while (topoM != NULL)
	{
		if (topoM->seguinte->ID == ID)
		{
			RM* anterior = topoM;
			topoM = topoM->seguinte;
			anterior->seguinte = topoM->seguinte;
			free(topoM);

            while(anterior != NULL)
            {
                anterior->ID = --anterior->ID;
                anterior = anterior->seguinte;
            }
            return anterior;
		}
		topoM = topoM->seguinte;
	}
}

/// @brief Esta função ordena os meios por quantidade de bateria, de maneira decrescente
/// @param topoM endereço do topo da lista dos meios
/// @return retorna um valor do tipo apontador para RM, sendo este o endereço do topo da lista com os meios ordenados por quantidade de bateria de forma decrescente
RM* ordenarMeios(RM* topoM)
{
    int trocado = 1;
    while (trocado) 
    {
        trocado = 0;
        RM* anterior = NULL;
        RM* atual = topoM;
        while (atual->seguinte != NULL) 
        {
            if (atual->bateria < atual->seguinte->bateria) 
            {
                RM* proximo = atual->seguinte;
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;
                if (anterior != NULL)
                {
                    anterior->seguinte = proximo;
                } else 
                {
                    topoM = proximo;
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
}

/// @brief Esta funcao percorre a lista dos meios e vai imprimindo as informações no terminal
/// @param topoM endereço do topo da lista dos meios
void listarMeios(RM* topoM)
{
	if (topoM != NULL)
	{
		limparTela();
        topoM = ordenarMeios(topoM);
		while (topoM != NULL)
		{
            if(!topoM->alugado)
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

/// @brief Esta função atribui automaticamente um ID para cada meio, por ordem crescente
/// @param topoM endereço do topo da lista dos meios
/// @return atribui um valor do tipo int, que é o novo ID para o meio
int darID(RM* topoM)
{
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
/// @param topoA endereço do topo da lista dos alugueres
/// @param topoM endereço do topo da lista do meio que foi alugado
/// @param NIF NIF do cliente que alugou um meio
/// @return retorna um valor do tipo apontador para RA, sendo este o endereço do topo da lista com o aluguer adicionado
RA* adicionarAluguer(RA* topoA, RM* topoM, int NIF)
{
	RA* novo = malloc(sizeof(RA));
    
    novo->meio->ID = topoM->ID;
    strcpy(novo->meio->nome,topoM->nome);
    strcpy(novo->meio->localizacao,topoM->localizacao);
    novo->meio->bateria = topoM->bateria;
    novo->meio->autonomia = topoM->autonomia;
    novo->meio->custo = topoM->custo;
    novo->NIF = NIF;
    novo->meio->alugado = topoM->alugado;

    if(topoA != NULL) novo->seguinte = topoA;
    else novo->seguinte = NULL;

	return novo;
}