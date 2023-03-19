#ifndef GESTOR_H_
#define GESTOR_H_
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

typedef struct registo_gestor
{
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF;
	struct registo_gestor* seguinte;
}RG;

RG* adicionarGestor(RG* topoG, char nome[], char morada[], char password[], int NIF);

RG* editarDadosGestor(RG* topoG, int NIF);

RG* removerGestor(RG* topoG, int NIF);

#endif