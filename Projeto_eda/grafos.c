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

VTC* removerVertice(VTC* auxVTC, char id) // ja removemos o vertice em si, falta remover as ligacoes com aquele vertice utilizar loop e removeraresta
{
    VTC* anterior = auxVTC, *atual = auxVTC, *aux;

    if (atual == NULL)  return (NULL);
    else if (atual->id == id)
    {
        aux = atual->seguinte;
        free(atual);
        //
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
            //
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

VTC* editarAresta(VTC* auxVTC, int v1, int v2, float peso)
{
    VTC* topoVTC = auxVTC;

    while (topoVTC != NULL && topoVTC->id != v1)    topoVTC = topoVTC->seguinte;

    if (topoVTC != NULL) 
    {
        ADJ* adj = topoVTC->adjacentes;
        
        while(adj != NULL)
        {
            if(adj->adj == v2)
            {
                adj->peso = peso;
            }
            adj = adj->seguinte;
        }
    }
    else
    {
        printf("A aresta que introduziu não é válida.");
    }

    return auxVTC;
}

VTC* removerAresta(VTC* auxVTC, int v1, int v2)
{
    VTC* anterior = auxVTC, *atual = auxVTC, *aux;

    //falta andar pelos adjacentes e verificar se sao iguais a v2(fzr um ADJ* anterior, ADJ* atual e ADJ* aux tbm)
    if (atual == NULL)  return (NULL);
    else if (atual->id == v1)
    {
        aux = atual->seguinte;
        free(atual);
        return (aux);
    }
    else
    {
        for (atual; atual != NULL && atual->id != v1; atual = atual->seguinte)
        {
            anterior = atual;
        }

        if (atual == NULL)
            return (auxVTC);
        else
        {
            //falta andar pelos adjacentes e verificar se sao iguais a v2(fzr um ADJ* anterior, ADJ* atual e ADJ* aux tbm)
            anterior->seguinte = atual->seguinte;
            free(atual);
            return (auxVTC);
        }
    }
}