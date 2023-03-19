#ifndef MEIOS_H_
#define MEIOS_H_
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

//verificar aluguer no registo meios

RM* adicionarMeio(RM* topoM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo);

RM* removerMeio(RM* topoM, int ID);

void listarMeios(RM* topoM);

int darID(RM* topoM);

RA* adicionarAluguer(RA* topoA, int NIF, RM* topoM);

#endif