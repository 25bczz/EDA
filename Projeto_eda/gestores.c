#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

/// @brief Esta funcao adiciona um novo gestor à lista ligada. Primeiramente ela verifica se já existe um gestor com o mesmo NIF, caso não exista acrescenta então o novo membro no topo da lista.
/// @param auxG endereço do topo da lista a que vamos acrescentar o novo gestor
/// @param nome nome do gestor novo
/// @param morada morada do gestor novo
/// @param password password do gestor novo
/// @param NIF NIF do gestor novo
/// @return retorna um valor do tipo apontador para RG, ou seja o novo endereço do topo da lista
RG* adicionarGestor(RG* auxG, char nome[], char morada[], char password[], int NIF)
{
	RG* topoG = auxG;
	if (verificarGestorNIF(topoG, NIF) == 0)
	{
		RG* novo = malloc(sizeof(RG));

		strcpy(novo->nome, nome);
		strcpy(novo->morada, morada);
		strcpy(novo->password, password);
		novo->NIF = NIF;

		if(topoG != NULL) novo->seguinte = topoG;
    	else novo->seguinte = NULL;

		return novo;
	}
	else return topoG;
}

/// @brief Esta função interage com o gestor e pergunta que dados ele quer alterar. Dependendo da escolha ele encaminha para tal e vai percorrendo a lista até ter o NIF igual ao introduzido anteriormente e altera os valores.
/// @param auxG endereço do topo da lista dos gestores
/// @param NIF NIF do gestor que desejamos alterar os dados
/// @return retorna um valor do tipo apontador para RG, sendo este o endereço do topo da lista com os dados atualizados
RG* editarDadosGestor(RG* auxG, int NIF)
{
	int opcao;
	RG* topoG = auxG;

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

/// @brief Esta funcao utiliza uma variavel auxiliar. Ela vai percorrendo a lista até achar o NIF igual ao do gestor que desejamos remover no endereço seguinte da lista para então o podermos remover
/// @param auxG endereço do topo da lista dos gestores
/// @param NIF NIF do cliente que desejamos alterar os dados
/// @return retorna um valor do tipo apontador para RG, sendo este o endereço do topo da lista com o utilizador removido
RG* removerGestor(RG* auxG, int NIF)
{
	RG* topoG = auxG;
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
	return topoG;
}