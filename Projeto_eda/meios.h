#ifndef MEIOS_H
#define MEIOS_H

typedef struct registo_meio
{
	int ID;
	char nome[TAM_NOME], localizacao[TAM_MORADA];
	float bateria, autonomia, custo;
	int alugado, NIF;
	time_t tempoinicial;
	struct registo_meio* seguinte;
}RM;

typedef struct registo_alugueres
{
	int NIF, ID;
	time_t tempoinicial, tempofinal;
	char nome[TAM_NOME], localizacao[TAM_MORADA];
	float bateria, autonomia, custo;
	struct registo_alugueres* seguinte;
}RA;

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_vertices VTC;
typedef struct registo_adjacentes ADJ;

RM* adicionarMeio(RM* auxM, int ID, char nome[], char localizacao[], float bateria, float autonomia, float custo, int alugado, int NIF, time_t tempoinicial);

RM* editarMeio(RM* auxM, int ID);

RM* removerMeio(RM* auxM, int ID);

void ordenarMeios(RM** auxM);

/* void ordenarMeiosDist(RM** auxM); */

void listarMeios(RM* auxM);

int listarMeiosAlugados(RM* auxM, int NIF);

int darID(RM* auxM);

RA* adicionarAluguer(RA* auxA, RM* auxM, int NIF, time_t final);

#endif