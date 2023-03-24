#ifndef MENU_H
#define MENU_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

void menu();// Menu de interação com o cliente

void menuLogin(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuRegistro(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuCliente(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

void menuGestor(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

#endif