#ifndef GESTOR_H
#define GESTOR_H
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30

typedef struct registo_gestor
{
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF;
	struct registo_gestor* seguinte;
}RG;

typedef struct registo_cliente RC;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

RG* adicionarGestor(RG* topoG, char nome[], char morada[], char password[], int NIF);

RG* editarDadosGestor(RG* topoG, int NIF);

RG* removerGestor(RG* topoG, int NIF);

#endif