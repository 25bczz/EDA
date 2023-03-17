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

int verificarClienteGestor(RC* topoC, RG* topoG, int NIF, char password[])// Verifica se o usuário é cliente ou gestor, devolve 0 caso seja cliente e devolve 1 caso seja gestor
{
    int c = -1, g = -1, op;// Inicialização das variáveis como -1 para verificação

    while(topoC != NULL)// Percorre a lista de clientes e verifica se há um NIF igual e altera o valor da variavel de controlo
    {
        if(topoC->NIF == NIF && (strcmp(topoC->password,password) == 0))
        {
            c = 0;
        }
        topoC = topoC->seguinte;
    }

    while(topoG != NULL)// Percorre a lista de gestores e verifica se há um NIF igual e altera o valor da variavel de controlo
    {
        if(topoG->NIF == NIF && (strcmp(topoG->password,password) == 0))
        {
            g = 1;
        }
        topoG = topoG->seguinte;
    }

    if(c != -1 && g != -1)// Verifica os valores das variaveis de controlo
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
        printf("Não existe nenhuma conta com esses dados.\n");
        enterContinuar();
    }
    else if(c != -1 && g == -1) return 0;
    else return 1;
}

int verificarClienteNIF(RC* topoC, int NIF)// Devolve 1 se houver um NIF igual já registado e 0 caso contrário
{
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

int verificarGestorNIF(RG* topoG, int NIF)// Devolve 1 se houver um NIF igual já registado e 0 caso contrário
{
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

void menuLogin(RC* topoC, RG* topoG, RM* topoM, RA* topoA)// Menu de interação com o cliente
{
    int v, NIF;
    char password[TAM_PASSWORD];

    limparTela();// Limpa a tela
    printf("Introduza o seu NIF:\n");
    scanf("%d", &NIF);
    printf("Introduza a sua password\n");
    scanf("%s", password);
    v = verificarClienteGestor(topoC, topoG, NIF, password);

    if(v) menuGestor(topoC, topoG, topoM, topoA);
    else menuCliente(topoC, topoG, topoM, topoA);
}

void menuRegistro(RC* topoC, RG* topoG, RM* topoM, RA* topoA)// Menu de interação com o cliente
{
    int op, v;

    do{
        limparTela();// Limpa a tela
        printf("Introduza a opcao que desejar:\n1 - Gestor\n2 - Cliente\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
                char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
                int NIF, idade;

                printf("Introduza o seu nome:\n");
                limparBuffer();
                gets(nome);
                printf("Introduza a sua morada:\n");
                limparBuffer();
                gets(morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                gets(password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);
                printf("Introduza a sua idade:\n");
                scanf("%d", &idade);

                v = verificarClienteNIF(topoC, NIF);

                if(!v)
                {
                topoC = adicionarCliente(topoC, nome, morada, password, NIF, idade);
                }
                break;
            }
            case 2:
            {
                char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
                int NIF;

                printf("Introduza o seu nome:\n");
                limparBuffer();
                gets(nome);
                printf("Introduza a sua morada:\n");
                limparBuffer();
                gets(morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                gets(password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);

                v = verificarGestorNIF(topoG, NIF);

                if(!v)
                {
                topoG = adicionarGestor(topoG, nome, morada, password, NIF);
                }
                break;
            }
            default:
            {
                print("Opcao invalida.\n");
                enterContinuar();// Enter para continuar a interação e introduzir outra opção
                break;
            }
        }
    }while(op != 1 && op != 2);
}

void menu(RC* topoC, RG* topoG, RM* topoM, RA* topoA)// Menu de interação com o cliente
{
    int op;

    do
    {
        limparTela();// Limpa a tela
        printf("Introduza a opcao que desejar:\n1 - Login\n2 - Registro\n0 - Sair");
        scanf("%d", &op);
        limparTela();// Limpa a tela
        switch(op)
        {
            case 1:
            {
                menuLogin(topoC, topoG, topoM, topoA);// Entra em outro menu de interação com o utilizador
                break; 
            }
            case 2:
            {
                menuRegistro(topoC, topoG, topoM, topoA);// Entra em outro menu de interação com o utilizador
                break;
            }
            case 0:
                //Falta isto
                break;
            default:
            {
                print("Opcao invalida.\n");
                enterContinuar();// Enter para continuar a interação e introduzir outra opção
                break;
            }
        }
    }while(op != 0);
}