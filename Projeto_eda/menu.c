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
/// @param topoC apontador para o endereço do topo da lista dos clientes
/// @param topoG apontador para o endereço do topo da lista dos gestores
/// @param topoM apontador para o endereço do topo da lista dos meios
/// @param topoA apontador para o endereço do topo da lista dos alugueres
/// @param topoVTC apontador para o endereço do topo da lista dos vertices/grafo
void menuLogin(RC** topoC, RG** topoG, RM** topoM, RA** topoA, VTC** topoVTC)
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

    if(v == 1) menuGestor(&(*topoC), &(*topoG), &(*topoM), *topoA, &(*topoVTC), NIF);
    else if(v == 0) menuCliente(&(*topoC), *topoG, &(*topoM), &(*topoA), *topoVTC, NIF);
}

/// @brief Menu de interação com o cliente
/// @param topoC apontador para o endereço do topo da lista dos clientes
/// @param topoG apontador para o endereço do topo da lista dos gestores
/// @param topoM endereço do topo da lista dos vertices/grafo
void menuRegistro(RC** topoC, RG** topoG, VTC* topoVTC)
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
                char nome[TAM_NOME], *morada = malloc(sizeof(char) * TAM_MORADA), password[TAM_PASSWORD];
                int NIF, idade, loc;

                printf("Introduza o seu nome:\n");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                removerCaracter(nome);
                printf("Introduza o numero correspondente a sua morada:\n");
                listarVertices(topoVTC);
                scanf("%d", &loc);
                morada = procurarMorada(topoVTC, loc);
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
/// @param topoC apontador para o endereço do topo da lista dos clientes
/// @param topoG endereço do topo da lista dos gestores
/// @param topoM apontador para o endereço do topo da lista dos meios
/// @param topoA apontador para o endereço do topo da lista dos alugueres
/// @param topoVTC endereço do topo da lista dos vertices/grafo
/// @param NIF NIF do cliente que realizou o login
void menuCliente(RC** topoC, RG* topoG, RM** topoM, RA** topoA, VTC* topoVTC, int NIF)
{
    int op;
    do
    {
        limparTela();
        imprimirLogo();
        imprimirDadosCliente(*topoC, NIF);
        printf("Introduza a opcao que desejar:\n1 - Carregar saldo\n2 - Listar meios\n3 - Alugar meio\n4 - Terminar aluguer\n5 - Pesquisar meios por localidade\n6 - Pesquisar meio por raio\n7 - Editar dados da minha conta\n8 - Eliminar a minha conta\n0 - Sair\n");
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
                char *localizacao = malloc(sizeof(char) * TAM_MORADA);
                int loc;

                limparTela();
                printf("Introduza o numero da localizacao do veiculo:\n");
                listarVertices(topoVTC);
                scanf("%d", &loc);
                localizacao = procurarMorada(topoVTC, loc);

                pesquisarLocalidade(*topoM, localizacao);
                break;
            }
            case 6:
            {
                char veiculo[TAM_NOME];
                int loc;
                float raio;

                limparTela();
                printf("Introduza o raio em que deseja procurar:\n");
                scanf("%f", &raio);
                printf("Introduza o veiculo que deseja procurar\n");
                scanf("%s", veiculo);
                printf("Introduza o numero da localizacao onde esta:\n");
                listarVertices(topoVTC);
                scanf("%d", &loc);
                limparTela();

                procurarMeiosRaio(topoVTC, *topoM, loc, veiculo, raio);
                break;
            }
            case 7:
            {
                limparTela();
                *topoC = editarDadosCliente(*topoC, topoVTC, NIF);

                break;
            }
            case 8:
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
/// @param topoC apontador para o endereço do topo da lista dos clientes
/// @param topoG apontador para o endereço do topo da lista dos gestores
/// @param topoM apontador para o endereço do topo da lista dos meios
/// @param topoA endereço do topo da lista dos alugueres
/// @param topoVTC apontador para o endereço do topo da lista dos vertices/grafo
/// @param NIF NIF do gestor que realizou o login
void menuGestor(RC** topoC, RG** topoG, RM** topoM, RA* topoA, VTC** topoVTC, int NIF)
{
    int op;

    do
    {
        limparTela();
        imprimirLogo();
        imprimirDadosGestor(*topoG, NIF);
        printf("Introduza a opcao que desejar:\n1 - Listar clientes\n2 - Remover clientes\n3 - Listar meios\n4 - Adionar meio\n5 - Pesquisar meios por localidade\n6 - Procurar meios por raio\n7 - Editar dados da minha conta\n8 - Adicionar localidade\n9 - Alterar localidade\n10 - Remover localidade\n11 - Adicionar ligacoes\n12 - Alterar ligacoes\n13 - Remover ligacoes\n14 - Recolher veiculos\n15 - Eliminar a minha conta\n0 - Sair\n");
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
                int ID, loc;
                char nome[TAM_NOME], *localizacao = malloc(sizeof(char) * TAM_MORADA);
                float bateria, autonomia, custo;

                limparTela();
                ID = darID(*topoM);
                printf("Introduza o tipo de meio que deseja adicionar:\n");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                removerCaracter(nome);
                printf("Introduza o numero da localizacao do veiculo:\n");
                listarVertices(*topoVTC);
                scanf("%d", &loc);
                localizacao = procurarMorada(*topoVTC, loc);
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
                char *localizacao = malloc(sizeof(char) * TAM_MORADA);
                int loc;

                limparTela();
                printf("Introduza o numero da localizacao do veiculo:\n");
                listarVertices(*topoVTC);
                scanf("%d", &loc);
                localizacao = procurarMorada(*topoVTC, loc);

                pesquisarLocalidade(*topoM, localizacao);
                break;
            }
            case 6:
            {
                char veiculo[TAM_NOME];
                int loc;
                float raio;

                limparTela();
                printf("Introduza o raio em que deseja procurar:\n");
                scanf("%f", &raio);
                printf("Introduza o veiculo que deseja procurar\n");
                scanf("%s", veiculo);
                printf("Introduza o numero da localizacao onde esta:\n");
                listarVertices(*topoVTC);
                scanf("%d", &loc);
                limparTela();
                
                procurarMeiosRaio(*topoVTC, *topoM, loc, veiculo, raio);
                break;
            }
            case 7:
            {
                limparTela();
                *topoG = editarDadosGestor(*topoG, *topoVTC, NIF);
                break;
            }
            case 8:
            {
                int id = darIDVertice(*topoVTC);
                char geocode[TAM_MORADA];

                if(id != -1)
                {
                    limparTela();
                    printf("Introduza a geolocalizacao que deseja para essa nova localidade:\n");
                    scanf("%s", geocode);

                    *topoVTC = adicionarVertice(*topoVTC, id, geocode);
                }
                else
                {
                    limparTela();
                    printf("Atingiu o numero maximo de localizacoes.\n");
                    enterContinuar();
                }

                break;
            }
            case 9:
            {
                int id, v;

                printf("Introduza o numero do vertice que deseja alterar:\n");
                scanf("%d", &id);
                v = verificarVerticeValido(*topoVTC, id);

                if(v == 1)  editarVertice(*topoVTC, id);
                else    
                {
                    limparTela();
                    printf("Vertice invalido introduzido\n");
                    enterContinuar();
                }
                break;
            }
            case 10:
            {
                int id, v;

                printf("Introduza o numero do vertice que deseja remover:\n");
                scanf("%d", &id);
                v = verificarVerticeValido(*topoVTC, id);

                if(v == 1)  
                {
                    removerVertice(*topoVTC, id);
                    limparTela();
                    printf("Vertice removido con sucesso\n");
                    enterContinuar();
                }
                else    
                {
                    limparTela();
                    printf("Vertice invalido introduzido\n");
                    enterContinuar();
                }

                break;
            }
            case 11:
            {
                int v1, v2, vv1, vv2, va;
                float peso;

                printf("Introduza o ID do vertice de origem:\n");
                scanf("%d", &v1);
                printf("Introduza o ID do vertice de destino:\n");
                scanf("%d", &v2);
                printf("Introduza o peso da aresta:\n");
                scanf("%f", &peso);

                vv1 = verificarVerticeValido(*topoVTC, v1);
                vv2 = verificarVerticeValido(*topoVTC, v2);

                if(vv1 == 1 && vv2 == 1)  
                {
                    va = verificarArestaValida(*topoVTC, v1, v2);

                    if(va == 1) adicionarAresta(*topoVTC, v1, v2, peso);
                    else
                    {
                        limparTela();
                        printf("Aresta introduzida invalida\n");
                        enterContinuar();
                    }
                }
                else    
                {
                    limparTela();
                    printf("Vertices introduzidos invalidos\n");
                    enterContinuar();
                }

                break;
            }
            case 12:
            {
                int v1, v2, vv1, vv2, va;
                float peso;

                printf("Introduza o ID do vertice de origem da aresta que deseja editar:\n");
                scanf("%d", &v1);
                printf("Introduza o ID do vertice de destino da aresta que deseja editar:\n");
                scanf("%d", &v2);

                vv1 = verificarVerticeValido(*topoVTC, v1);
                vv2 = verificarVerticeValido(*topoVTC, v2);

                if(vv1 == 1 && vv2 == 1)  
                {
                    va = verificarArestaValida(*topoVTC, v1, v2);

                    if(va == 1) 
                    {
                        printf("Introduza o peso que deseja colocar na aresta:\n");
                        scanf("%f", &peso);
                        editarAresta(*topoVTC, v1, v2, peso);
                    }
                    else
                    {
                        limparTela();
                        printf("Aresta introduzida invalida\n");
                        enterContinuar();
                    }
                }
                else   
                {
                    limparTela();
                    printf("Vertices introduzidos invalidos\n");
                    enterContinuar();
                }

                break;
            }
            case 13:
            {
                int v1, v2, vv1, vv2, va;

                printf("Introduza o ID do vertice de origem da aresta que deseja remover:\n");
                scanf("%d", &v1);
                printf("Introduza o ID do vertice de destino da aresta que deseja remover:\n");
                scanf("%d", &v2);

                vv1 = verificarVerticeValido(*topoVTC, v1);
                vv2 = verificarVerticeValido(*topoVTC, v2);

                if(vv1 == 1 && vv2 == 1)
                {
                    va = verificarArestaValida(*topoVTC, v1, v2);

                    if(va == 1) removerAresta(*topoVTC, v1, v2);
                    else
                    {
                        limparTela();
                        printf("Aresta introduzida invalida\n");
                        enterContinuar();
                    }
                }
                else    
                {
                    limparTela();
                    printf("Vertices introduzidos invalidos\n");
                    enterContinuar();
                }

                break;
            }
            case 14:
            {
                int nmr;

                limparTela();
                printf("Introduza o numero de veiculos que o seu camiao pode recolher:\n");
                scanf("%d", &nmr);

                limparTela();
                camiao(*topoM, *topoVTC, nmr);
                enterContinuar();

                break;
            }
            case 15:
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
