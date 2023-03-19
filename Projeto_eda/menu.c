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

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuLogin(RC* topoC, RG* topoG, RM* topoM, RA* topoA)
{
    int v, NIF;
    char password[TAM_PASSWORD];

    limparTela();
    printf("Introduza o seu NIF:\n");
    scanf("%d", &NIF);
    printf("Introduza a sua password\n");
    limparBuffer();
    scanf("%s", password);
    v = verificarClienteGestor(topoC, topoG, NIF, password);

    if(v) menuGestor(topoC, topoG, topoM, topoA, NIF);
    else menuCliente(topoC, topoG, topoM, topoA, NIF);
}

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuRegistro(RC* topoC, RG* topoG, RM* topoM, RA* topoA)
{
    int op, v;

    do{
        limparTela();
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
                scanf("%s", morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                scanf("%s", password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);
                printf("Introduza a sua idade:\n");
                scanf("%d", &idade);

                v = verificarClienteNIF(topoC, NIF);

                if(!v)
                {
                    topoC = adicionarCliente(topoC, nome, morada, password, NIF, idade);
                }
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);
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
                scanf("%s", morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                scanf("%s", password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);

                v = verificarGestorNIF(topoG, NIF);

                if(!v)
                {
                    topoG = adicionarGestor(topoG, nome, morada, password, NIF);
                }
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);
                break;
            }
            default:
            {
                limparTela();
                print("Opcao invalida.\n");
                enterContinuar();
                break;
            }
        }
    }while(op != 1 && op != 2);
}

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuCliente(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF)
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
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);

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

                limparTela();
                printf("Introduza a localidade que quer procurar:\n");
                limparBuffer();
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
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);
                break;
            }
            case 6:
            {
                int v;

                limparTela();
                printf("Deseja realmente eliminar a sua conta?\n1 - Sim\n2 - Nao\n");
                scanf("%d", &v);
                
                if(v)
                {
                    topoC =  removerCliente(topoC, NIF);
                    adicionarFicheiro(topoC, topoG, topoM, topoA);
                    adicionarFicheiroBin(topoC, topoG, topoM, topoA);

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

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuGestor(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF)
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
            case 1:
            {
                limparTela();
                listarClientes(topoC);
                enterContinuar();
                break;
            }
            case 2:
            {
                int v, elim;

                limparTela();
                listarClientes(topoC);
                printf("\nIntroduza o NIF do cliente que deseja eliminar:\n");
                scanf("%d", &elim);
                limparTela();
                printf("Deseja realmente eliminar este cliente?\n1 - Sim\n2 - Nao\n");
                scanf("%d", &v);
                
                if(v)
                {
                    topoC =  removerCliente(topoC, elim);
                    adicionarFicheiro(topoC, topoG, topoM, topoA);
                    adicionarFicheiroBin(topoC, topoG, topoM, topoA);

                    limparTela();
                    printf("Conta eliminada com sucesso!\n");
                    enterContinuar();
                }
                break;
            }
            case 3:
            {
                limparTela();
                listarMeios(topoM);
                enterContinuar();
                break;
            }
            case 4:
            {
                int ID;
                char nome[TAM_NOME], localizacao[TAM_MORADA];
                float bateria, autonomia, custo;

                limparTela();
                ID = darID(topoM);
                printf("Introduza o tipo de meio que deseja adicionar:\n");
                limparBuffer();
                gets(nome);
                printf("Introduza a localizacao do veiculo:\n");
                limparBuffer();
                scanf("%s", localizacao);
                printf("Introduza a bateria restante no veiculo:\n");
                scanf("%f", &bateria);
                printf("Introduza a autonomia restante no veiculo:\n");
                scanf("%f", &autonomia);
                printf("Introduza o custo para alugar o veiculo:\n");
                scanf("%f", &custo);

                topoM = adicionarMeio(topoM, ID, nome, localizacao, bateria, autonomia, custo);
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);

                limparTela();
                printf("Meio adicionado com sucesso\n");
                enterContinuar();
                break;
            }
            case 5:
            {
                char localidade[TAM_MORADA];
                RM* encontrados;

                limparTela();
                printf("Introduza a localidade que quer procurar:\n");
                limparBuffer();
                scanf("%s", localidade);

                encontrados = pesquisarLocalidade(topoM, localidade);

                limparTela();
                listarMeios(encontrados);
                enterContinuar();
                break;
            }
            case 6:
            {
                limparTela();
                topoG = editarDadosGestor(topoG, NIF);
                adicionarFicheiro(topoC, topoG, topoM, topoA);
                adicionarFicheiroBin(topoC, topoG, topoM, topoA);
                break;
            }
            case 7:
            {
                int v;

                limparTela();
                printf("Deseja realmente eliminar a sua conta?\n1 - Sim\n2 - Nao\n");
                scanf("%d", &v);
                
                if(v)
                {
                    topoG =  removerGestor(topoG, NIF);
                    adicionarFicheiro(topoC, topoG, topoM, topoA);
                    adicionarFicheiroBin(topoC, topoG, topoM, topoA);

                    limparTela();
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

/// @brief Menu de interação com o cliente
void menu()
{
    int op;
    do
    {
        RC* topoC = conteudoRC();
	    RG* topoG = conteudoRG();
	    RM* topoM = conteudoRM();
	    RA* topoA = conteudoRA();


        limparTela();
        printf("Introduza a opcao que desejar:\n1 - Login\n2 - Registro\n0 - Sair\n");
        scanf("%d", &op);
        limparTela();
        switch(op)
        {
            case 1:
            {
                menuLogin(topoC, topoG, topoM, topoA);
                break; 
            }
            case 2:
            {
                menuRegistro(topoC, topoG, topoM, topoA);
                break;
            }
            case 0: break;
            default:
            {
                limparTela();
                print("Opcao invalida.\n");
                enterContinuar();
                break;
            }
        }
    }while(op != 0);
}