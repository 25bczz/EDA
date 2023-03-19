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

RM* adicionarMeio(RM* topoM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo)
{
	RM* novo = malloc(sizeof(RM));

    ID = darid(topoM);
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