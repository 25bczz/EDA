#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct registo_vertices
{
    int num;
    char geocode[TAM_MORADA];
    ADJ* adjacentes;
    struct registo_vertices *seguinte;
}VTC;

typedef struct registo_adjacentes
{
    int adj;
    float peso;
    struct registo_adjacentes *seguinte;
}ADJ;

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;



#endif