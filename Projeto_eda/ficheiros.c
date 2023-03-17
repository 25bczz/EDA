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

RC* conteudoRC()// Função para ler do ficheiro clientes.txt e adicionar à lista topoC e devolver o endereço inicial da lista após ler tudo
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

RG* conteudoRG()// Função para ler do ficheiro gestores.txt e adicionar à lista topoG e devolver o endereço inicial da lista após ler tudo
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

RM* conteudoRM()// Função para ler do ficheiro meios.txt e adicionar à lista topoM e devolver o endereço inicial da lista após ler tudo
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

RA* conteudoRA()// Função para ler do ficheiro alugueres.txt e adicionar à lista topoA e devolver o endereço inicial da lista após ler tudo
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
			topoA = adicionarAluguer(topoA, NIF, meio); //meio->ID, meio->nome, meio->localizacao, meio->bateria, meio->autonomia, meio->custo
		}
		fclose(fp);
	}

	return topoA;
}

void adicionarFicheiro(RC* topoC, RG* topoG, RM* topoM, RA* topoA)// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
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

RC* conteudoBinRC() // Função para ler do ficheiro clientes.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo
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

RG* conteudoBinRG()// Função para ler do ficheiro gestores.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo
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

RM* conteudoBinRM()// Função para ler do ficheiro meios.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo
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

RA* conteudoBinRA()// Função para ler do ficheiro alugueres.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo
{
	FILE* fp;
	RA* aux = NULL;

	fp = fopen("alugueres.bin", "rb");

	if (fp != NULL)
	{
		RA aluguer;
		while (fread(&aluguer, sizeof(RG), 1, fp) == 1)
		{
			aux = adicionarAluguer(aux, aluguer.NIF, aluguer.meio); //aluguer.meio->ID, aluguer.meio->nome, aluguer.meio->localizacao, aluguer.meio->bateria, aluguer.meio->autonomia, aluguer.meio->custo
		}
		fclose(fp);
	}
	
	return aux;
}

void adicionarFicheiroBin(RC* topoC, RG* topoG, RM* topoM, RA* topoA)// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
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