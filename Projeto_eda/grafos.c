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

VTC* adicionarVertice(VTC* auxVTC, int id, char geocode[])
{
    VTC* novo = malloc(sizeof(VTC));
    VTC* topoVTC = auxVTC;

    novo->id = id;
    strcpy(novo->geocode, geocode);
    novo->adjacentes = NULL;

    if(topoVTC == NULL)  novo->seguinte = NULL;
    else novo->seguinte = topoVTC;

    return novo;
}

VTC* editarVertice(VTC* auxVTC, int id)
{
    char loc[TAM_MORADA];
    VTC* topoVTC = auxVTC;

    limparTela();
    printf("Introduza a nova localizacao que deseja para o programa:\n");
    scanf("%s", loc);

    if (topoVTC != NULL)
    {
        while (topoVTC != NULL)
        {
            if (topoVTC->id == id)
            {
                strcpy(topoVTC->geocode, loc);
                return auxVTC;
            }
            topoVTC = topoVTC->seguinte;
        }
    }
    else
    {
        printf("Nao ha nenhuma localizacao para alterar.\n");
    }
    return auxVTC;
}

VTC* removerVertice(VTC* auxVTC, char id) // falta ir ao grafo e remover todas as ligacoes!
{
    VTC* anterior = auxVTC, *atual = auxVTC, *aux;

    if (atual == NULL)
        return (NULL);
    else if (atual->id == id)
    {
        aux = atual->seguinte;
        free(atual);
        return (aux);
    }
    else
    {
        for (atual; atual != NULL && atual->id != id; atual = atual->seguinte)
        {
            anterior = atual;
        }
        if (atual == NULL)
            return (auxVTC);
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return (auxVTC);
        }
    }
}

VTC* adicionarAresta(VTC* auxVTC, int id, int adj, float peso)
{
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL)
    {
        if(topoVTC->id == id)
        {
            ADJ* novo = malloc(sizeof(ADJ));

            novo->adj = adj;
            novo->peso = peso;
            novo->seguinte = topoVTC->adjacentes;
            topoVTC->adjacentes = novo;

            return auxVTC;
        }
        topoVTC = topoVTC->seguinte;
    }

    return auxVTC;
}