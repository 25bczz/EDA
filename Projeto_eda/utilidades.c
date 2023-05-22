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

/// @brief limpa a tela
void limparTela()
{
	//system("cls||clear");
    system("clear");
}

/// @brief limpa o buffer
void limparBuffer()
{
	fflush(stdin);
}

/// @brief limpa o buffer e espera a interação do cliente para continuar
void enterContinuar()
{
	limparBuffer();
	printf("Pressione ENTER para continuar..");
	getc(stdin);
}

/// @brief verifica através de uma password e um NIF se o utilizador é um cliente ou um gestor
/// @param auxC endereço do topo da lista dos clientes
/// @param auxG endereço do topo da lista dos gestores
/// @param NIF NIF do utilizador
/// @param password password do utilizador
/// @return retorna um valor do tipo int = 1 se for gestor ou = 0 se for cliente. Se não houver conta retorna -1;
int verificarClienteGestor(RC* auxC, RG* auxG, int NIF, char password[])
{
    RC* topoC = auxC;
    RG* topoG = auxG;

    int c = -1, g = -1, op;

    while(topoC != NULL)
    {
        if(topoC->NIF == NIF && (strcmp(topoC->password,password) == 0))
        {
            c = 0;
        }
        topoC = topoC->seguinte;
    }

    while(topoG != NULL)
    {
        if(topoG->NIF == NIF && (strcmp(topoG->password,password) == 0))
        {
            g = 1;
        }
        topoG = topoG->seguinte;
    }

    if(c != -1 && g != -1)
    {
        do{
            limparTela();
            printf("Existem 2 contas com esses dados. Como deseja prosseguir?\n1 - Cliente\n2 - Gestor\n");
            scanf("%d", &op);

            switch(op)
            {
                case 1: return 0;
                case 2: return 1;
            }
        }while(op != 1 && op != 2);
    }
    else if(c == -1 && g == -1)
    {
        limparTela();
        printf("Nao existe nenhuma conta com esses dados.\n");
        enterContinuar();
        return -1;
    }
    else if(c != -1 && g == -1) return 0;
    else return 1;
}

/// @brief Esta função verifica se já existe algum cliente registrado com certo NIF
/// @param auxC endereço do topo da lista dos clientes
/// @param NIF NIF do cliente que desejamos verificar se já há algum registrado
/// @return Devolve 1 se houver um NIF igual já registado e 0 caso contrário
int verificarClienteNIF(RC* auxC, int NIF)
{
    RC* topoC = auxC;

    while(topoC != NULL)
    {
        if(topoC->NIF == NIF)
        {
            limparTela();
            printf("Ja existe um cliente com esse NIF registado.\n");
            enterContinuar();
            return 1;
        }
        topoC = topoC->seguinte;
    }
    return 0;
}

/// @brief Esta função verifica se já existe algum gestor registrado com certo NIF
/// @param auxG endereço do topo da lista dos gestores
/// @param NIF NIF do cliente que desejamos verificar se já há algum registrado
/// @return Devolve 1 se houver um NIF igual já registado e 0 caso contrário
int verificarGestorNIF(RG* auxG, int NIF)// Devolve 1 se houver um NIF igual já registado e 0 caso contrário
{
    RG* topoG = auxG;

    while(topoG != NULL)
    {
        if(topoG->NIF == NIF)
        {
            limparTela();
            printf("Ja existe um gestor com esse NIF registado.\n");
            enterContinuar();
            return 1;
        }
        topoG = topoG->seguinte;
    }
    return 0;
}

/// @brief Esta função verifica se determinado veiculo ja está alugado
/// @param auxM endereço do topo da lista dos meios
/// @param ID ID do meio que desejamos verificar
/// @return devolve 1 se já estiver alugado e 0 se não estiver
int verificarAlugado(RM* auxM, int ID)
{
    RM* topoM = auxM;

    while(topoM != NULL)
    {
        if(topoM->ID == ID)
        {
            if(topoM->alugado == 1) return 1;
            else return 0;
        }
        topoM = topoM->seguinte;
    }
    return 0;
}

int verificarAlugadoNIF(RM* auxM, int ID, int NIF)
{
    RM* topoM = auxM;

    while(topoM != NULL)
    {
        if(topoM->ID == ID)
        {
            if(topoM->alugado == 1 && topoM->NIF == NIF) return 1;
            else return 0;
        }
        topoM = topoM->seguinte;
    }
    return 0;
}

/// @brief Esta função verifica se uma palavra passe introduzida por um cliente é válida
/// @param auxC endereço do topo da lista dos clientes
/// @param NIF NIF do cliente que estamos a verificar
/// @param password password que estamos a verificar se estava válida
/// @return retorna 0 se a comparação resultar em igual e valores diferentes de 0 se forem diferentes
int verificarPasswordAntigaClientes(RC* auxC,int NIF, char password[])
{
    RC* topoC = auxC;

	while (topoC != NULL)
	{
		if (topoC->NIF == NIF) return strcmp(topoC->password, password);
        topoC = topoC->seguinte;
	}
    return -1;
}

/// @brief Esta função verifica se uma palavra passe introduzida por um gestor é válida
/// @param auxG endereço do topo da lista dos gestores
/// @param NIF NIF do gestor que estamos a verificar
/// @param password password que estamos a verificar se estava válida
/// @return retorna 0 se a comparação resultar em igual e valores diferentes de 0 se forem diferentes
int verificarPasswordAntigaGestores(RG* auxG, int NIF, char password[])
{
    RG* topoG = auxG;

    while (topoG != NULL)
	{
		if (topoG->NIF == NIF) return strcmp(topoG->password, password);
        topoG = topoG->seguinte;
	}
    return -1;
}
