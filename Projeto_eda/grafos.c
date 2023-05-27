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