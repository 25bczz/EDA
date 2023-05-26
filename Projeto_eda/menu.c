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

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuLogin(RC** topoC, RG** topoG, RM** topoM, RA** topoA, VTC** topoVTC, GRAFO* topoGRAFO)
{
    int v, NIF;
    char password[TAM_PASSWORD];

    limparTela();
    imprimirLogo();
    printf("Introduza o seu NIF:\n");
    scanf("%d", &NIF);
    printf("Introduza a sua password\n");
    limparBuffer();
    scanf("%s", password);
    v = verificarClienteGestor(*topoC, *topoG, NIF, password);

    if(v == 1) menuGestor(&(*topoC), &(*topoG), &(*topoM), *topoA, &(*topoVTC), &(*topoGRAFO), NIF);
    else if(v == 0) menuCliente(&(*topoC), *topoG, &(*topoM), &(*topoA), &(*topoVTC), &(*topoGRAFO), NIF);
}

/// @brief Menu de interação com o cliente
/// @param topoC endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
void menuRegistro(RC** topoC, RG** topoG)
{
    int op, v;

    do{
        limparTela();
        imprimirLogo();
        printf("Introduza a opcao que desejar:\n1 - Cliente\n2 - Gestor\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
                char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
                int NIF, idade;

                printf("Introduza o seu nome:\n");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                removerCaracter(nome);
                printf("Introduza a sua morada:\n");
                scanf("%s", morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                scanf("%s", password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);
                printf("Introduza a sua idade:\n");
                scanf("%d", &idade);

                v = verificarClienteNIF(*topoC, NIF);

                if(v == 0)
                {
                    *topoC = adicionarCliente(*topoC, nome, morada, password, NIF, idade, 0);
                }
                break;
            }
            case 2:
            {
                char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
                int NIF;

                printf("Introduza o seu nome:\n");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                printf("Introduza a sua morada:\n");
                limparBuffer();
                scanf("%s", morada);
                printf("Introduza a sua password:\n");
                limparBuffer();
                scanf("%s", password);
                printf("Introduza o seu NIF:\n");
                scanf("%d", &NIF);

                removerCaracter(nome);

                v = verificarGestorNIF(*topoG, NIF);

                if(v == 0)
                {
                    *topoG = adicionarGestor(*topoG, nome, morada, password, NIF);
                }
                break;
            }
            default:
            {
                limparTela();
                printf("Opcao invalida.\n");
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
void menuCliente(RC** topoC, RG* topoG, RM** topoM, RA** topoA, VTC** topoVTC, GRAFO* topoGRAFO, int NIF)
{
    int op;
    do
    {
        limparTela();
        imprimirLogo();
        imprimirDadosCliente(*topoC, NIF);
        printf("Introduza a opcao que desejar:\n1 - Carregar saldo\n2 - Listar meios\n3 - Alugar meio\n4 - Terminar aluguer\n5 - Pesquisar meios por localidade\n6 - Editar dados da minha conta\n7 - Eliminar a minha conta\n0 - Sair\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
                float pagamento;

                limparTela();
                printf("Introduza o saldo que deseja carregar:\n");
                scanf("%f", &pagamento);

                *topoC = carregarSaldo(*topoC, NIF, pagamento);

                limparTela();
                printf("Saldo atualizado com sucesso!\n");
                enterContinuar();
                break;
            }
            case 2:
            {
                limparTela();
                ordenarMeios(&(*topoM));
                break;
            }
            case 3:
            {
                int ID, v;

                limparTela();
                listarMeios(*topoM);
                printf("Introduza o ID do meio que deseja alugar:\n");
                scanf("%d", &ID);

                v = Alugar(*topoC, *topoM, ID, NIF);

                if(v == 1)
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
                int ID, v1, v2;

                limparTela();
                v1 = listarMeiosAlugados(*topoM, NIF);

                if(v1 == 1)
                {
                    printf("Introduza o ID do meio que deseja terminar o aluguer:\n");
                    scanf("%d", &ID);

                    v2 = cancelarAluguer(*topoC, *topoM, &(*topoA), ID, NIF);

                    if(v2)
                    {
                        limparTela();
                        printf("Aluguer terminado com sucesso\n");
                        enterContinuar();
                    }
                    else
                    {
                        limparTela();
                        printf("Ocorreu um erro ao terminar o aluguer do meio.\n");
                        enterContinuar();
                    }
                }
                break;
            }
            case 5:
            {
                char localidade[TAM_MORADA];

                limparTela();
                printf("Introduza a localidade que quer procurar:\n");
                limparBuffer();
                scanf("%s", localidade);

                pesquisarLocalidade(*topoM, localidade);
                break;
            }
            case 6:
            {
                limparTela();
                *topoC = editarDadosCliente(*topoC, NIF);

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
                    *topoC =  removerCliente(*topoC, NIF);

                    printf("Conta eliminada com sucesso!\n");
                    enterContinuar();
                }
                op = 0;
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
void menuGestor(RC** topoC, RG** topoG, RM** topoM, RA* topoA, VTC** topoVTC, GRAFO* topoGRAFO, int NIF)
{
    int op;

    do
    {
        limparTela();
        imprimirLogo();
        imprimirDadosGestor(*topoG, NIF);
        printf("Introduza a opcao que desejar:\n1 - Listar clientes\n2 - Remover clientes\n3 - Listar meios\n4 - Adionar meio\n5 - Pesquisar meios por localidade\n6 - Editar dados da minha conta\n7 - Eliminar a minha conta\n0 - Sair\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
                limparTela();
                listarClientes(*topoC);
                break;
            }
            case 2:
            {
                int v, elim;

                limparTela();
                listarClientes(*topoC);
                printf("\nIntroduza o NIF do cliente que deseja eliminar:\n");
                scanf("%d", &elim);
                printf("Deseja realmente eliminar este cliente?\n1 - Sim\n2 - Nao\n");
                scanf("%d", &v);
                
                if(v == 1)
                {
                    *topoC =  removerCliente(*topoC, elim);

                    limparTela();
                    printf("Conta eliminada com sucesso!\n");
                    enterContinuar();
                }
                break;
            }
            case 3:
            {
                limparTela();
                ordenarMeios(&(*topoM));
                break;
            }
            case 4:
            {
                int ID;
                char nome[TAM_NOME], localizacao[TAM_MORADA];
                float bateria, autonomia, custo;

                limparTela();
                ID = darID(*topoM);
                printf("Introduza o tipo de meio que deseja adicionar:\n");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                removerCaracter(nome);
                printf("Introduza a localizacao do veiculo:\n");
                scanf("%s", localizacao);
                printf("Introduza a bateria restante no veiculo:\n");
                scanf("%f", &bateria);
                printf("Introduza a autonomia restante no veiculo:\n");
                scanf("%f", &autonomia);
                printf("Introduza o custo para alugar o veiculo:\n");
                scanf("%f", &custo);

                *topoM = adicionarMeio(*topoM, ID, nome, localizacao, bateria, autonomia, custo, 0, 0, 0);

                limparTela();
                printf("Meio adicionado com sucesso\n");
                enterContinuar();
                break;
            }
            case 5:
            {
                char localidade[TAM_MORADA];

                limparTela();
                printf("Introduza a localidade que quer procurar:\n");
                limparBuffer();
                scanf("%s", localidade);

                pesquisarLocalidade(*topoM, localidade);
                break;
            }
            case 6:
            {
                limparTela();
                *topoG = editarDadosGestor(*topoG, NIF);
                break;
            }
            case 7:
            {
                int v;

                limparTela();
                printf("Deseja realmente eliminar a sua conta?\n1 - Sim\n2 - Nao\n");
                scanf("%d", &v);
                
                if(v == 1)
                {
                    *topoG =  removerGestor(*topoG, NIF);

                    limparTela();
                    printf("Conta eliminada com sucesso!\n");
                    enterContinuar();
                }
                op = 0;
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
