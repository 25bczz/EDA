#ifndef MENU_H
#define MENU_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;
typedef struct registo_vertices VTC;
typedef struct registo_arestas GRAFO;

void menu();

void menuLogin(RC** topoC, RG** topoG, RM** topoM, RA** topoA, VTC** topoVTC, GRAFO** topoGRAFO);

void menuRegistro(RC** topoC, RG** topoG);

void menuCliente(RC** topoC, RG* topoG, RM** topoM, RA** topoA, VTC** topoVTC, GRAFO** topoGRAFO, int NIF);

void menuGestor(RC** topoC, RG** topoG, RM** topoM, RA* topoA, VTC** topoVTC, GRAFO** topoGRAFO, int NIF);

#endif