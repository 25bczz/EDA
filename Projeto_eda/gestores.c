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

RG* adicionarGestor(RG* topoG, char nome[], char morada[], char password[], int NIF)
{
	if (!verificarGestorNIF(topoG, NIF))
	{
		RG* novo = malloc(sizeof(RG));

		strcpy(novo->nome, nome);
		strcpy(novo->morada, nome);
		strcpy(novo->password, nome);
		novo->NIF = NIF;

		if(topoG != NULL) novo->seguinte = topoG;
    	else novo->seguinte = NULL;

		return novo;
	}
	else return topoG;
}

RG* editarDadosGestor(RG* topoG, int NIF)
{
	int opcao;

	printf("Escolha a opcao que deseja alterar:\n");
	printf("1 - Morada\n2 - Password\n");
	scanf("%d", &opcao);

	switch (opcao)
	{
		case 1:
		{
			char morada[TAM_MORADA];
			printf("Introduza a sua nova morada:\n");
            limparBuffer();
			scanf("%s", morada);

			while (topoG != NULL)
			{
				if (topoG->NIF == NIF)
				{
					strcpy(topoG->morada,morada);
				}
                topoG = topoG->seguinte;
			}
			break;
		}
		case 2:
		{
			int vf;
			char password[TAM_PASSWORD];

			printf("Introduza a password antiga:\n");
            limparBuffer();
			scanf("%s", password);

			vf = verificarPasswordAntigaGestores(topoG, NIF, password);

			while (vf != 0)
			{
                limparTela();
				printf("A password introduzida e errada.\n Introduza novamente a password antiga:\n");
                limparBuffer();
				scanf("%s", password);
				vf = verificarPasswordAntigaGestores(topoG, NIF, password);
			}

            limparTela();
			printf("Introduza a sua nova password:\n");
            limparBuffer();
			scanf("%s", password);

			while (topoG != NULL)
			{
				if (topoG->NIF == NIF)
				{
					strcpy(topoG->password, password);
				}
                topoG = topoG->seguinte;
			}
			break;
		}
	}
    limparTela();
    printf("Dados alterados com sucesso\n");
    enterContinuar();
	return topoG;
}

RG* removerGestor(RG* topoG, int NIF)
{
    while (topoG != NULL)
	{
		if (topoG->seguinte->NIF == NIF)
		{
			RG* anterior = topoG;
			topoG = topoG->seguinte;
			anterior->seguinte = topoG->seguinte;
			free(topoG);
            return anterior;
		}
		topoG = topoG->seguinte;
	}
}