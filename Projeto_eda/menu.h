#ifndef MENU_H
#define MENU_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;
typedef struct registo_vertices VTC;
typedef struct registo_adjacentes ADJ;

void menu();

void menuLogin(RC** topoC, RG** topoG, RM** topoM, RA** topoA, VTC** topoVTC);

void menuRegistro(RC** topoC, RG** topoG, VTC* topoVTC);

void menuCliente(RC** topoC, RG* topoG, RM** topoM, RA** topoA, VTC* topoVTC, int NIF);

void menuGestor(RC** topoC, RG** topoG, RM** topoM, RA* topoA, VTC** topoVTC, int NIF);

#endif