#ifndef MENU_H
#define MENU_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

void menu();

void menuLogin(RC* auxC, RG* auxG, RM* auxM, RA* auxA);

void menuRegistro(RC* auxC, RG* auxG, RM* auxM, RA* auxA);

void menuCliente(RC* auxC, RG* auxG, RM* auxM, RA* auxA, int NIF);

void menuGestor(RC* auxC, RG* auxG, RM* auxM, RA* auxA, int NIF);

#endif