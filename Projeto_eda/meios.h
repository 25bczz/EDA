#ifndef MEIOS_H
#define MEIOS_H

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

RM* adicionarMeio(RM* auxM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo, int alugado);

RM* editarMeio(RM* auxM, int ID);

RM* removerMeio(RM* auxM, int ID);

void ordenarMeios(RM** auxM);

void listarMeios(RM* auxM);

int darID(RM* auxM);

RA* adicionarAluguer(RA* auxA, RM* auxM, int NIF);

#endif