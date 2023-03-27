#ifndef MENU_H
#define MENU_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

void menu();

void menuLogin(RC** topoC, RG** topoG, RM** topoM, RA* topoA);

void menuRegistro(RC** topoC, RG** topoG, RM** topoM, RA** topoA);

void menuCliente(RC** topoC, RG* topoG, RM** topoM, RA* topoA, int NIF);

void menuGestor(RC** topoC, RG** topoG, RM** topoM, RA* topoA, int NIF);

#endif