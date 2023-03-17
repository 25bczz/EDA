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

    if(v) menuGestor(topoC, topoG, topoM, topoA, NIF);
    else menuCliente(topoC, topoG, topoM, topoA, NIF);
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
                limparTela();
                print("Opcao invalida.\n");
                enterContinuar();// Enter para continuar a interação e introduzir outra opção
                break;
            }
        }
    }while(op != 1 && op != 2);
}

void menuCliente(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF)// Menu de interação com o cliente
{
    int op;
    do
    {
        RC* topoC = conteudoRC();
        RG* topoG = conteudoRG();
        RM* topoM = conteudoRM();
        RA* topoA = conteudoRA();

        limparTela();
        printf("Introduza a opcao que desejar:\n1 - Carregar saldo\n2 - Listar meios\n3 - Alugar meio\n4 - Pesquisar meios por localidade\n5 - Editar dados da minha conta\n6 - Eliminar a minha conta\n0 - Sair\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
                float pagamento;

                limparTela();
                printf("Introduza o saldo que deseja carregar:\n");
                scanf("%d", &pagamento);

                topoC = carregarSaldo(topoC, NIF, pagamento);
                adicionarFicheiro(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro

                limparTela();
                printf("Saldo atualizado com sucesso!\n");
                enterContinuar();
                break;
            }
            case 2:
            {
                limparTela();
                listarMeios(topoM);
                enterContinuar();
                break;
            }
            case 3:
            {
                int ID, v;

                limparTela();
                listarMeios(topoM);
                printf("Introduza o ID do meio que deseja alugar:\n");
                scanf("%d", &ID);

                v = Alugar(topoC, topoM, topoA, ID, NIF);

                if(v)
                {
                    limparTela();
                    printf("Meio alugado com sucesso\n");
                    enterContinuar();
                }
                else
                {
                    limparTela();
                    printf("Ocorreu um erro ao alugar o meio.\n");
                    enterContinuar();
                }

                break;
            }
            case 4:
            {
                char localidade[TAM_MORADA];
                RM* encontrados;

                printf("Introduza a localidade que quer procurar:\n");
                scanf("%s", localidade);

                encontrados = pesquisarLocalidade(topoM, localidade);

                limparTela();
                listarMeios(encontrados);
                enterContinuar();

                break;
            }
            case 5:
            {
                limparTela();
                topoC = editarDadosCliente(topoC, NIF);
                adicionarFicheiro(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                break;
            }
            case 6:
            {
                int v;

                limparTela();
                printf("Deseja realmente eliminar a sua conta?\n1 - Sim\n2 - Nao");
                scanf("%d", &v);
                
                if(v)
                {
                    topoC =  removerCliente(topoC, NIF);
                    adicionarFicheiro(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                    adicionarFicheiroBin(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro

                    printf("Conta eliminada com sucesso!\n");
                    enterContinuar();
                }

                break;
            }
            case 0: break;
            default:
            {
                limparTela();
                printf("Opcao invalida.\n");
                enterContinuar();
            }
        }
    } while (op != 0);
    
}

void menuGestor(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF)// Menu de interação com o cliente
{
    int op;

    do
    {
        RC* topoC = conteudoRC();
        RG* topoG = conteudoRG();
        RM* topoM = conteudoRM();
        RA* topoA = conteudoRA();

        limparTela();
        printf("Introduza a opcao que desejar:\n1 - Listar clientes\n2 - Remover clientes\n3 - Listar meios\n4 - Adionar meio\n5 - Pesquisar meios por localidade\n6 - Editar dados da minha conta\n7 - Eliminar a minha conta\n0 - Sair\n");
        scanf("%d", &op);

        switch(op)
        {

        }
    } while (op != 0);
    
}

void menu()// Menu de interação com o cliente
{
    int op;
    do
    {
        RC* topoC = conteudoRC();
	    RG* topoG = conteudoRG();
	    RM* topoM = conteudoRM();
	    RA* topoA = conteudoRA();


        limparTela();// Limpa a tela
        printf("Introduza a opcao que desejar:\n1 - Login\n2 - Registro\n0 - Sair\n");
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
                adicionarFicheiro(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro
                break;
            }
            case 0: break;
            default:
            {
                limparTela();
                print("Opcao invalida.\n");
                enterContinuar();// Enter para continuar a interação e introduzir outra opção
                break;
            }
        }
    }while(op != 0);
}