#ifndef MENU_H_
#define MENU_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

void menu();// Menu de interação com o cliente

void menuLogin(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuRegistro(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuCliente(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

void menuGestor(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

#endif