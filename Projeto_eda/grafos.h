#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct registo_vertices
{
    int id;
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

VTC* adicionarVertice(VTC* auxVTC, int id, char geocode[]);

VTC* editarVertice(VTC* auxVTC, int id);

VTC* removerVertice(VTC* auxVTC, int id);

void listarVertices(VTC* auxVTC);

char* procurarMorada(VTC* auxVTC, int v);

VTC* adicionarAresta(VTC* auxVTC, int id, int adj, float peso);

VTC* editarAresta(VTC* auxVTC, int v1, int v2, float peso);

VTC* removerAresta(VTC* auxVTC, int v1, int v2);

int procurarMeiosRaio(VTC* auxVTC, RM* auxM, int localizacao, char veiculo[], float raio);

int procurarMeiosRaioAux(VTC* topoVTC, int v , int visitados[], int dist, float raio);

int darIDVertice(VTC* auxVTC);

int verificarVerticeValido(VTC* auxVTC, int v);

int verificarArestaValida(VTC* auxVTC, int v1, int v2);

#endif