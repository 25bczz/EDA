#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct registo_vertices
{
    int num;
    char geocode[TAM_MORADA];
    GRAFO adjacentes
    struct registo_vertices *seguinte;
}VTC;

typedef struct registo_arestas
{
    int adj;
    float peso;
    struct registo_arestas *seguinte;
}ADJACENTES;

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

VTC* adicionarVertice(VTC* topoVTC, int id, char loc[]);

GRAFO* adicionarAresta(GRAFO** grafo, int v1, int v2, float peso);

#endif