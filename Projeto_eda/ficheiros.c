#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

//				FICHEIROS DE TEXTO

/// @brief função que lê um ficheiro txt e vai acrescentando a uma lista do tipo RC os valores encontrados.
/// @return retorna o endereço do topo da lista dos clientes com todos os dados
RC* conteudoRC()
{
	FILE* fp;
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF, idade;
	float saldo;
	RC* topoC = NULL;

	fp = fopen("clientes.txt", "r");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%[^;];%[^;];%[^;];%d;%d;%f", nome, morada, password, &NIF, &idade, &saldo);
			topoC = adicionarCliente(topoC, nome, morada, password, NIF, idade, saldo);
		}
		fclose(fp);
	}

	return topoC;
}

/// @brief função que lê um ficheiro txt e vai acrescentando a uma lista do tipo RG os valores encontrados.
/// @return retorna o endereço do topo da lista dos gestores com todos os dados
RG* conteudoRG()
{
	FILE* fp;
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF;
	RG* topoG = NULL;

	fp = fopen("gestores.txt", "r");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%[^;];%[^;];%[^;];%d", nome, morada, password, &NIF);
			topoG = adicionarGestor(topoG, nome, morada, password, NIF);
		}
		fclose(fp);
	}

	return topoG;
}

/// @brief função que lê um ficheiro txt e vai acrescentando a uma lista do tipo RM os valores encontrados.
/// @return retorna o endereço do topo da lista dos meios com todos os dados
RM* conteudoRM()
{
	FILE* fp;
	int ID;
	char nome[TAM_NOME], localizacao[TAM_MORADA];
	float bateria, autonomia, custo;
	RM* topoM = NULL;

	fp = fopen("meios.txt", "r");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%f;%f;%f", &ID, nome, localizacao, &bateria, &autonomia, &custo);
			topoM = adicionarMeio(topoM, ID, nome, localizacao, bateria, autonomia, custo);
		}
		fclose(fp);
	}

	return topoM;
}

/// @brief função que lê um ficheiro txt e vai acrescentando a uma lista do tipo RA os valores encontrados.
/// @return retorna o endereço do topo da lista dos alugueres com todos os dados
RA* conteudoRA()
{
	FILE* fp;
	int NIF;
	RA* topoA = NULL;
    RM* meio = NULL;

	fp = fopen("alugueres.txt", "r");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%[^;];%[^;];%f;%f;%f", &NIF, &meio->ID, meio->nome, meio->localizacao, &meio->bateria, &meio->autonomia, &meio->custo);
			topoA = adicionarAluguer(topoA, NIF, meio);
		}
		fclose(fp);
	}

	return topoA;
}

/// @brief Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro de texto
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void adicionarFicheiro(RC* topoC, RG* topoG, RM* topoM, RA* topoA)
{
	FILE* fp;

//				CLIENTES
	fp = fopen("clientes.txt", "w");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (topoC != NULL)
		{
			fprintf(fp, "%s;%s;%s;%d;%d;%.2f", topoC->nome, topoC->morada, topoC->password, topoC->NIF, topoC->idade, topoC->saldo);
			topoC = topoC->seguinte;
		}
		fclose(fp);
	}

//			GESTORES
	fp = fopen("gestores.txt", "w");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (topoG != NULL)
		{
			fprintf(fp, "%s;%s;%s;%d", topoG->nome, topoG->morada, topoG->password, topoG->NIF);
			topoG = topoG->seguinte;
		}
		fclose(fp);
	}

//				MEIOS
	fp = fopen("meios.txt", "w");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (topoM != NULL)
		{
			fprintf(fp, "%d;%s;%s;%.2f;%.2f;%.2f", topoM->ID, topoM->nome, topoM->localizacao, topoM->bateria, topoM->autonomia, topoM->custo);
			topoM = topoM->seguinte;
		}
		fclose(fp);
	}


//				ALUGUERES
	fp = fopen("alugueres.txt", "w");

	if (fp == NULL)
	{
		printf("Ficheiro indisponivel.");
	}
	else
	{
		while (topoA != NULL)
		{
			fprintf(fp, "%d;%d;%s;%s;%.2f;%.2f;%.2f", topoA->NIF, topoA->meio->ID, topoA->meio->nome, topoA->meio->localizacao, topoA->meio->bateria, topoA->meio->autonomia, topoA->meio->custo);
			topoA = topoA->seguinte;
		}
		fclose(fp);
	}
}


//			FICHEIROS BINÁRIOS

/// @brief função que lê um ficheiro binário e vai acrescentando a uma lista do tipo RC os valores encontrados.
/// @return retorna o endereço do topo da lista dos clientes com todos os dados
RC* conteudoBinRC() 
{
	FILE* fp;
	RC* aux = NULL;

	fp = fopen("clientes.bin", "rb");

	if (fp != NULL)
	{
		RC cliente;
		while (fread(&cliente, sizeof(RC), 1, fp) == 1)
		{
			aux = adicionarCliente(aux, cliente.nome, cliente.morada, cliente.password, cliente.NIF, cliente.idade, cliente.saldo);
		}
		fclose(fp);
	}
	
	return aux;
}

/// @brief função que lê um ficheiro binário e vai acrescentando a uma lista do tipo RG os valores encontrados.
/// @return retorna o endereço do topo da lista dos gestores com todos os dados
RG* conteudoBinRG()
{
	FILE* fp;
	RG* aux = NULL;

	fp = fopen("gestores.bin", "rb");

	if (fp != NULL)
	{
		RG gestor;
		while (fread(&gestor, sizeof(RG), 1, fp) == 1)
		{
			aux = adicionarGestor(aux, gestor.nome, gestor.morada, gestor.password, gestor.NIF);
		}
		fclose(fp);
	}
	
	return aux;
}

/// @brief função que lê um ficheiro binário e vai acrescentando a uma lista do tipo RM os valores encontrados.
/// @return retorna o endereço do topo da lista dos meios com todos os dados
RM* conteudoBinRM()
{
	FILE* fp;
	RM* aux = NULL;

	fp = fopen("meios.bin", "rb");

	if (fp != NULL)
	{
		RM meio;
		while (fread(&meio, sizeof(RG), 1, fp) == 1)
		{
			aux = adicionarMeio(aux, meio.ID, meio.nome, meio.localizacao, meio.bateria, meio.autonomia, meio.custo);
		}
		fclose(fp);
	}
	
	return aux;
}

/// @brief função que lê um ficheiro binário e vai acrescentando a uma lista do tipo RA os valores encontrados.
/// @return retorna o endereço do topo da lista dos alugueres com todos os dados
RA* conteudoBinRA()
{
	FILE* fp;
	RA* aux = NULL;

	fp = fopen("alugueres.bin", "rb");

	if (fp != NULL)
	{
		RA aluguer;
		while (fread(&aluguer, sizeof(RG), 1, fp) == 1)
		{
			aux = adicionarAluguer(aux, aluguer.NIF, aluguer.meio); 
		}
		fclose(fp);
	}
	
	return aux;
}

/// @brief Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro binário
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void adicionarFicheiroBin(RC* topoC, RG* topoG, RM* topoM, RA* topoA)
{
//				CLIENTES
	FILE* fp;
	fp = fopen("clientes.bin", "wb");

	while (topoC != NULL)
	{
		fwrite(topoC, sizeof(RC), 1, fp);
		topoC = topoC->seguinte;
	}

	fclose(fp);


//				GESTORES
	fp = fopen("gestores.bin", "wb");

	while (topoG != NULL)
	{
		fwrite(topoG, sizeof(RG), 1, fp);
		topoG = topoG->seguinte;
	}

	fclose(fp);


//				MEIOS
	fp = fopen("meios.bin", "wb");

	while (topoM != NULL)
	{
		fwrite(topoM, sizeof(RM), 1, fp);
		topoM = topoM->seguinte;
	}

	fclose(fp);


//				ALUGUERES
	fp = fopen("alugueres.bin", "wb");

	while (topoA != NULL)
	{
		fwrite(topoA, sizeof(RA), 1, fp);
		topoA = topoA->seguinte;
	}

	fclose(fp);
}