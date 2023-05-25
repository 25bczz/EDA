#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct registo_vertices
{
    int num;
    char geocode[TAM_MORADA];
    struct registo_vertices *seguinte;
}VTC;

typedef struct registo_arestas
{
    int adj;
    float peso;
    struct registo_arestas *seguinte;
}GRAFO;

VTC* lerVertices();

GRAFO* lerGrafo();

#endif