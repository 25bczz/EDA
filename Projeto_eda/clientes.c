#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"
#include "grafos.h"

/// @brief Esta funcao adiciona um novo cliente à lista ligada. Primeiramente ela verifica se já existe um cliente com o mesmo NIF, caso não exista acrescenta então o novo membro no topo da lista.
/// @param auxC endereço do topo da lista a que vamos acrescentar o novo cliente
/// @param nome nome do cliente novo
/// @param morada morada do cliente novo
/// @param password password do cliente novo
/// @param NIF NIF do cliente novo
/// @param idade idade do cliente novo
/// @return retorna um valor do tipo apontador para RC, ou seja o novo endereço do topo da lista
RC* adicionarCliente(RC* auxC, char nome[], char morada[], char password[], int NIF, int idade, float saldo)
{
	RC* topoC = auxC;
	if (verificarClienteNIF(topoC, NIF) == 0)
	{
		RC* novo = malloc(sizeof(RC));

		strcpy(novo->nome, nome);
		strcpy(novo->morada, morada);
		strcpy(novo->password, password);
		novo->NIF = NIF;
		novo->idade = idade;
		novo->saldo = saldo;

		if(topoC != NULL) novo->seguinte = topoC;
    		else novo->seguinte = NULL;

		return novo;
	}
	else return topoC;
}
/// @brief Esta função interage com o utilizador e pergunta que dados ele quer alterar. Dependendo da escolha ele encaminha para tal e vai percorrendo a lista até ter o NIF igual ao introduzido anteriormente e altera os valores.
/// @param auxC endereço do topo da lista dos clientes
/// @param NIF NIF do cliente que desejamos alterar os dados
/// @return retorna um valor do tipo apontador para RC, sendo este o endereço do topo da lista com os dados atualizados
RC* editarDadosCliente(RC* auxC, int NIF)
{
	int opcao;
	RC* topoC = auxC;

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
	return auxC;
}

/// @brief Esta funcao utiliza uma variavel auxiliar. Ela vai percorrendo a lista até achar o NIF igual ao do cliente que desejamos remover no endereço seguinte da lista para então o podermos remover
/// @param auxC endereço do topo da lista dos clientes
/// @param NIF NIF do cliente que desejamos alterar os dados
/// @return retorna um valor do tipo apontador para RC, sendo este o endereço do topo da lista com o utilizador removido
RC* removerCliente(RC* auxC, int NIF)
{
        RC* anterior = auxC, *atual = auxC, *aux;

        if (atual == NULL){
            return(NULL);
        }
        else if (atual->NIF == NIF) 
        {
            aux = atual->seguinte;
            free(atual);
            return(aux);
        }
        else
        {
            for (atual; atual != NULL && atual->NIF != NIF;atual=atual->seguinte){

                anterior = atual;

            }
                if (atual == NULL) {
                    return(auxC);
                }
                else
                {
                    anterior->seguinte = atual->seguinte;
                    free(atual);
                    return(auxC);
                }
        }
}

/// @brief Esta funcao percorre a lista dos clientes e vai imprimindo as informações no terminal
/// @param auxC endereço do topo da lista dos clientes
void listarClientes(RC* auxC)
{
	RC* topoC = auxC;
	if (topoC != NULL)
	{
		limparTela();
		while (topoC != NULL)
		{
			printf("NIF - %d\nNome - %s\nIdade - %d\n\n", topoC->NIF, topoC->nome, topoC->idade);
			topoC = topoC->seguinte;
		}
		enterContinuar();
	}
	else
	{
		limparTela();
		printf("Nao existem clientes.\n");
		enterContinuar();
	}
}

/// @brief Esta funcao permite carregar o saldo de um cliente
/// @param auxC endereço do topo da lista dos clientes
/// @param NIF NIF do cliente que queremos "depositar" saldo
/// @param pagamento quantidade que desejamos "depositar" na conta do cliente
/// @return retorna o endereço para o topo da lista atualizada
RC* carregarSaldo(RC* auxC, int NIF, float pagamento)
{
	RC* topoC = auxC;
	while (topoC != NULL)
	{
		if (topoC->NIF == NIF)
		{
		    topoC->saldo += pagamento;
		    return topoC;
        }
		topoC = topoC->seguinte;
	}

	return topoC;
}

RC* editarSaldo(RC* auxC, int NIF, float pagamento)
{
	RC* topoC = auxC;

	while (topoC != NULL)
	{
		if (topoC->NIF == NIF)
		{
		    topoC->saldo = pagamento;
		    return topoC;
        }
		topoC = topoC->seguinte;
	}

	return topoC;
}

RC* removerSaldo(RC* auxC, int NIF, float pagamento)
{
	RC* topoC = auxC;
	while (topoC != NULL)
	{
		if (topoC->NIF == NIF)
		{
		    topoC->saldo -= pagamento;
		    return topoC;
        }
		topoC = topoC->seguinte;
	}

	return topoC;
}

/// @brief Esta função utiliza a função de verificação que verifica se um meio já está alugado, depois, se esse meio não se encontrar alugado, a variavel auxiliar toma os valores do meio desejado. Seguidamente, verificamos se o cliente tem saldo suficiente e fazemos a transação
/// @param auxC endereço do topo da lista dos clientes
/// @param auxM endereço do topo da lista dos meios
/// @param auxA endereço do topo da lista dos alugueres
/// @param ID ID do meio que desejamos alugar
/// @param NIF NIF do cliente que quer alugar
/// @return retorna 1 se for possivel alugar e 0 se nao se verificar esta condição
int Alugar(RC* auxC, RM* auxM, int ID, int NIF)
{
	RC* topoC = auxC;
	RM* topoM = auxM;
	int v = 0;

	while (topoM != NULL)
	{
		if (topoM->ID == ID) 
		{
			v = verificarAlugado(topoM, ID);

			if(v == 0)
			{
				while (topoC != NULL)
				{
					if (topoC->NIF == NIF)
					{
						if (topoC->saldo < topoM->custo * 5) return 0;
						else
						{
							topoM->alugado = 1;
							topoM->NIF = NIF;
							topoM->tempoinicial = time(NULL);
							return 1;
						}
					}
					topoC = topoC->seguinte;
				}
			}
			else return 0;
		}
		topoM = topoM->seguinte;
	}
	return 1;

}

int cancelarAluguer(RC* auxC, RM* auxM, RA** auxA, int ID, int NIF)
{
	RC* topoC = auxC;
	RM* topoM = auxM;
	time_t final = time(NULL);
	int v = 0;

	while (topoM != NULL)
	{
		if (topoM->ID == ID) 
		{
			v = verificarAlugadoNIF(topoM, ID, NIF);

			if(v == 1)
			{
						while (topoC != NULL)
						{
							if (topoC->NIF == NIF)
							{
								topoC = removerSaldo(topoC, topoC->NIF, (topoM->custo * ((final - topoM->tempoinicial) / 60)));
								*auxA = adicionarAluguer(*auxA, topoM, NIF, final);
								topoM->tempoinicial = 0;
								topoM->alugado = 0;
								topoM->NIF = 0;
								return 1;
							}
							topoC = topoC->seguinte;
						}
			}
			else return 0;
		}
		topoM = topoM->seguinte;
	}
	return 1;
}

/// @brief Esta função procura um meio numa certa localidade
/// @param auxM endereço do topo da lista dos meios
/// @param localidade localidade que desejamos procurar pelos meios
/// @return retorna um endereço para o topo da lista com os meios encontrados naquela localidade apenas
void pesquisarLocalidade(RM* auxM, char localidade[])
{
	int v = 0;
	RM* aux = NULL, *topoM = auxM;;

	if(topoM != NULL)
	{
		while(topoM != NULL)
		{
			if(strcmp(topoM->localizacao,localidade) == 0)
			{
				v = 1;
				aux = adicionarMeio(aux, topoM->ID, topoM->nome, topoM->localizacao, topoM->bateria, topoM->autonomia, topoM->custo, topoM->alugado, topoM->NIF, topoM->tempoinicial);
			}
			topoM = topoM->seguinte;
		}

		if(v == 1)
		{
			limparTela();
			listarMeios(aux);
			enterContinuar();
		}
		else
		{
			printf("Nao existem meios disponiveis nessa localidade neste momento.\n");
		}
	}
	else
	{
		limparTela();
		printf("Nao existem meios disponiveis no momento\n");
		enterContinuar();
	}
}
