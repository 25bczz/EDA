#ifndef MEIOS_H_
#define MEIOS_H_
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

typedef struct registo_meio
{
	int ID;
	char nome[TAM_NOME], localizacao[TAM_MORADA];
	float bateria, autonomia, custo;
	int alugado;
	struct registo_meio* seguinte;
}RM;

typedef struct registo_alugueres
{
	int NIF;
	RM* meio;
	struct registo_alugueres* seguinte;
}RA;

RM* adicionarMeio(RM* topoM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo);

RM* editarMeio(RM* topoM, int ID);

RM* removerMeio(RM* topoM, int ID);

RM* ordenarMeios(RM* topoM);

void listarMeios(RM* topoM);

int darID(RM* topoM);

RA* adicionarAluguer(RA* topoA, RM* topoM, int NIF);

#endif