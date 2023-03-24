#ifndef MEIOS_H
#define MEIOS_H
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30

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

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;

RM* adicionarMeio(RM* topoM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo);

RM* editarMeio(RM* topoM, int ID);

RM* removerMeio(RM* topoM, int ID);

RM* ordenarMeios(RM* topoM);

void listarMeios(RM* topoM);

int darID(RM* topoM);

RA* adicionarAluguer(RA* topoA, RM* topoM, int NIF);

#endif