#ifndef GESTOR_H
#define GESTOR_H

typedef struct registo_gestor
{
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF;
	struct registo_gestor* seguinte;
}RG;

typedef struct registo_cliente RC;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;
typedef struct registo_vertices VTC;
typedef struct registo_adjacentes ADJ;

RG* adicionarGestor(RG* auxG, char nome[], char morada[], char password[], int NIF);

RG* editarDadosGestor(RG* auxG, VTC* auxVTC, int NIF);

RG* removerGestor(RG* auxG, int NIF);

#endif