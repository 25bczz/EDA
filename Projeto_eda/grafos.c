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

VTC* adicionarVertice(VTC* auxVTC, int num, char loc[])
{
    VTC* topoVTC = auxVTC;

    VTC* novo = malloc(sizeof(VTC));

    novo->num = num;
    strcpy(novo->geocode, loc);

    if (topoVTC != NULL)    novo->seguinte = topoVTC;
    else    novo->seguinte = NULL;

    return novo;
}

GRAFO* adicionarAresta(GRAFO** grafo, int v1, int v2, float peso)
{
    GRAFO *novo = malloc(sizeof(GRAFO));

    novo->adj = v2;
    novo->peso = peso;

    if((*grafo[v1]) == NULL)
    {
        grafo[v1] = novo;
        return *grafo;
    }
    else 
    {
        novo->seguinte = grafo[v1];
        return novo;
    }
}