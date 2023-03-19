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

RC* adicionarCliente(RC* topoC, char nome[], char morada[], char password[], int NIF, int idade)
{
	if (!verificarClienteNIF(topoC, NIF))
	{
		RC* novo = malloc(sizeof(RC));

		strcpy(novo->nome, nome);
		strcpy(novo->morada, nome);
		strcpy(novo->password, nome);
		novo->NIF = NIF;
		novo->idade = idade;
		novo->saldo = 0;
		novo->seguinte = topoC;

		return novo;
	}
	else return topoC;
}

RC* editarDadosCliente(RC* topoC, int NIF)
{
	int opcao;

	printf("Escolha a opcao que deseja alterar:\n");
	printf("1 - Morada\n2 - Password\n3 - Idade\n");
	scanf("%d", &opcao);

	switch (opcao)
	{
		case 1:
		{
			char morada[TAM_MORADA];
			printf("Introduza a sua nova morada:\n");
            limparBuffer();
			scanf("%s", morada);

			while (topoC != NULL)
			{
				if (topoC->NIF == NIF)
				{
					strcpy(topoC->morada,morada);
				}
                topoC = topoC->seguinte;
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

			vf = verificarPasswordAntigaClientes(topoC, NIF, password);

			while (vf != 0)
			{
                limparTela();
				printf("A password introduzida e errada.\n Introduza novamente a password antiga:\n");
                limparBuffer();
				scanf("%s", password);
				vf = verificarPasswordAntigaClientes(topoC, NIF, password);
			}

            limparTela();
			printf("Introduza a sua nova password:\n");
            limparBuffer();
			scanf("%s", password);

			while (topoC != NULL)
			{
				if (topoC->NIF == NIF)
				{
					strcpy(topoC->password, password);
				}
                topoC = topoC->seguinte;
			}
			break;
		}
		case 3:
		{
			int idade;
			printf("Introduza a sua idade:\n");
			scanf("%d", &idade);

			while (topoC != NULL)
			{
				if (topoC->NIF == NIF)
				{
					topoC->idade = idade;
				}
                topoC = topoC->seguinte;
			}
			break;
		}
	}
    limparTela();
    printf("Dados alterados com sucesso\n");
    enterContinuar();
	return topoC;
}

RC* removerCliente(RC* topoC, int NIF)
{
		while (topoC != NULL)
		{
			if (topoC->seguinte->NIF == NIF)
			{
				RC* anterior = topoC;
				topoC = topoC->seguinte;
				anterior->seguinte = topoC->seguinte;
				free(topoC);

				return anterior;
			}
			topoC = topoC->seguinte;
		}
}

RC* carregarSaldo(RC* topoC, int NIF, float pagamento)
{
	while (topoC != NULL)
	{
		if (topoC->NIF == NIF)
		{
		    topoC->saldo += pagamento;
		    return topoC;
        }
		topoC = topoC->seguinte;
	}
}

int Alugar(RC* topoC, RM* topoM, RA* topoA, int ID, int NIF)
{
	RM* aux = NULL;

	while (topoM != NULL)
	{
		if (topoM->ID == ID) aux = topoM;
		topoM = topoM->seguinte;
	}

	if (aux != NULL)
	{
		while (topoC != NULL)
		{
			if (topoC->NIF == NIF)
			{
				if (topoC->saldo < aux->custo) return 0;
				else
				{
					topoC = carregarSaldo(topoC, NIF, -aux->custo);
					topoA = adicionarAlugueres(topoA, aux, NIF);
					return 1;
				}
			}
			topoC = topoC->seguinte;
		}
	}
	else return 0;
}