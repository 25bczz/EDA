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

/// @brief esta funcao e atualizada para adicionar um vertice
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param id id do vertice que deseja inserir
/// @param geocode nome da localidade que deseja inserir
/// @return apontador para o inicio da lista do grafo atualizado
VTC* adicionarVertice(VTC* auxVTC, int id, char geocode[])
{
    VTC* novo = malloc(sizeof(VTC));
    VTC* topoVTC = auxVTC;

    novo->id = id;
    strcpy(novo->geocode, geocode);
    novo->adjacentes = NULL;

    if(topoVTC == NULL)  novo->seguinte = NULL;
    else novo->seguinte = topoVTC;

    return novo;
}

/// @brief esta funcao e utilizada para editar um vertice
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param id id do vertice que desejamos alterar a localizacao
/// @return apontador para o inicio da lista do grafo atualizado
VTC* editarVertice(VTC* auxVTC, int id)
{
    char loc[TAM_MORADA];
    VTC* topoVTC = auxVTC;

    limparTela();
    printf("Introduza a nova localizacao que deseja para o programa:\n");
    scanf("%s", loc);

    if (topoVTC != NULL)
    {
        while (topoVTC != NULL)
        {
            if (topoVTC->id == id)
            {
                strcpy(topoVTC->geocode, loc);
                return auxVTC;
            }
            topoVTC = topoVTC->seguinte;
        }
    }
    else
    {
        printf("Nao ha nenhuma localizacao para alterar.\n");
    }
    return auxVTC;
}

/// @brief esta funcao e utilizada para remover um vertice
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param id id do vertice que desejamos remover
/// @return apontador para o inicio da lista do grafo atualizado
VTC* removerVertice(VTC* auxVTC, int id)
{
    VTC* anterior = auxVTC, *atual = auxVTC, *aux;

    if (atual == NULL)  return (NULL);
    else if (atual->id == id)
    {
        aux = atual->seguinte;
        free(atual);

        VTC* elim = aux;

        while(elim != NULL)
        {
            removerAresta(elim, elim->id, id);
            elim = elim->seguinte;
        }

        return auxVTC;
    }
    else
    {
        for (atual; atual != NULL && atual->id != id; atual = atual->seguinte)
        {
            anterior = atual;
        }

        if (atual == NULL)  return (auxVTC);
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            
            VTC* elim = auxVTC;

            while(elim != NULL)
            {
                removerAresta(elim, elim->id, id);
                elim = elim->seguinte;
            }

            return auxVTC;
        }
    }
}

/// @brief lista o dos vertices todos, juntamente com a localizacao
/// @param auxVTC é o apontador para o inicio da lista do grafo
void listarVertices(VTC* auxVTC)
{
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL)
    {
        printf("%d - %s\n", topoVTC->id, topoVTC->geocode);
        topoVTC = topoVTC->seguinte;
    }
}

/// @brief procura a morada no grafo atraves do id do vertice
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param v id do vertice que deseja procurar
/// @return string da morada encontrada
char* procurarMorada(VTC* auxVTC, int v)
{
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL)
    {
        if(topoVTC->id == v)    return topoVTC->geocode;
        topoVTC = topoVTC->seguinte;
    }
    return NULL;
}

int procurarIDVTC(VTC* auxVTC, char localizacao[])
{
    int ID;
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL)
    {
        if(strcmp(localizacao, topoVTC->geocode) == 0)  ID = topoVTC->id;
        topoVTC = topoVTC->seguinte;
    }

    return ID;
}

/// @brief funcao utilizada para adicionar uma aresta
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param id id do vertice de origem da aresta
/// @param adj id do vertice de destino da aresta
/// @param peso peso da aresta
/// @return apontador para o inicio da lista do grafo atualizado
VTC* adicionarAresta(VTC* auxVTC, int id, int adj, float peso)
{
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL)
    {
        if(topoVTC->id == id)
        {
            ADJ* novo = malloc(sizeof(ADJ));

            novo->adj = adj;
            novo->peso = peso;
            novo->seguinte = topoVTC->adjacentes;
            topoVTC->adjacentes = novo;

            return auxVTC;
        }
        topoVTC = topoVTC->seguinte;
    }

    return auxVTC;
}

/// @brief funcao utilizada para alterar o peso de uma aresta
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param v1 vertice de origem da aresta
/// @param v2 vertice de destino da aresta
/// @param peso peso que deseja colocar na aresta
/// @return apontador para o inicio da lista do grafo atualizado
VTC* editarAresta(VTC* auxVTC, int v1, int v2, float peso)
{
    VTC* topoVTC = auxVTC;

    while (topoVTC != NULL && topoVTC->id != v1)    topoVTC = topoVTC->seguinte;

    if (topoVTC != NULL) 
    {
        ADJ* adj = topoVTC->adjacentes;
        
        while(adj != NULL)
        {
            if(adj->adj == v2)
            {
                adj->peso = peso;
            }
            adj = adj->seguinte;
        }
    }
    else
    {
        printf("A aresta que introduziu não é válida.");
    }

    return auxVTC;
}

/// @brief Esta função é utilizada para remover uma aresta do grafo
/// @param auxVTC é o apontador para o inicio da lista do grafo
/// @param v1 vertice de origem da aresta
/// @param v2 vertice de destino da aresta
/// @return valor do topo da lista do grafo alterado
VTC* removerAresta(VTC* auxVTC, int v1, int v2)
{
    VTC* anterior = auxVTC, *atual = auxVTC, *aux;

    if (atual == NULL)  return auxVTC;
    else if (atual->id == v1)
    {
        if(atual->adjacentes == NULL) return auxVTC;
        else if(atual->adjacentes->adj == v2)
        {
            ADJ* auxADJ = atual->adjacentes->seguinte;
            free(atual->adjacentes);
            atual->adjacentes = auxADJ;
            return auxVTC;
        }
        else
        {
            ADJ* auxANT = atual->adjacentes, *auxATUAL = atual->adjacentes;

            for(auxATUAL; auxATUAL != NULL && auxATUAL->adj != v2; auxATUAL = auxATUAL->seguinte) auxANT = auxATUAL;

            if(auxATUAL == NULL)    return auxVTC;
            else
            {
                auxANT = auxATUAL->seguinte;
                free(auxATUAL);
                return auxVTC;
            }
        }
    }
    else
    {
        for (atual; atual != NULL && atual->id != v1; atual = atual->seguinte)
        {
            anterior = atual;
        }

        if (atual == NULL)
            return (auxVTC);
        else
        {
            if(atual->adjacentes == NULL) return auxVTC;
            else if(atual->adjacentes->adj == v2)
            {
                ADJ* auxADJ;
                auxADJ = atual->adjacentes->seguinte;
                free(atual->adjacentes);
                atual->adjacentes = auxADJ;
                return auxVTC;
            }
            else
            {
                ADJ* auxANT = atual->adjacentes, *auxATUAL = atual->adjacentes;

                for(auxATUAL; auxATUAL != NULL && auxATUAL->adj != v2; auxATUAL = auxATUAL ->seguinte) auxANT = auxATUAL;

                if(auxATUAL == NULL)    return auxVTC;
                else
                {
                    auxANT = auxATUAL->seguinte;
                    free(auxATUAL);
                    return auxVTC;
                }
            }
        }
    }
}

/// @brief esta funcao e uma funcao auxiliar a funcao de procurarMeiosAux, e utilizada para andar pelos adjacentes todos
/// @param topoVTC é o apontador para o inicio da lista do grafo
/// @param v e o ultimo vertice que visitamos para pegarmos os adjacentes deles
/// @param visitados array dos pontos visitados
/// @param dist distancia atualizada conforme vamos andando
/// @param raio raio maximo que podemos alcancar
/// @return 1 se sair corretamente e 0 se nao sair corretamente
int procurarMeiosRaioAux(VTC* topoVTC, int v , int visitados[], int dist, float raio)
{
    VTC* auxVTC = topoVTC;

    while(auxVTC != NULL && auxVTC->id != v)    auxVTC = auxVTC->seguinte;

    if(auxVTC != NULL)
    {
        ADJ* adj = auxVTC->adjacentes;

        while(adj != NULL)
        {
            if(dist + adj->peso <= raio && !visitados[adj->adj])
            {
                dist += adj->peso;
                visitados[adj->adj] = 1;

                procurarMeiosRaioAux(topoVTC, adj->adj, visitados, dist, raio);
            }

            adj = adj->seguinte;
        }
    }
    return 1;
}

/// @brief esta funcao procura todos os meios presentes num raio e lista-os
/// @param auxVTC apontador para o inicio da lista do grafo
/// @param auxRM apontador para o inicio da lista dos veiculos
/// @param localizacao vertice da localizacao onde se encontra o cliente
/// @param veiculo tipo de veiculo que o cliente deseja procurar
/// @param raio raio maximo onde o cliente deseja encontrar o veiculo
/// @return 1 se sair corretamente e 0 se nao sair corretamente
int procurarMeiosRaio(VTC* auxVTC, RM* auxM, int localizacao, char veiculo[], float raio)
{
    VTC* topoVTC = auxVTC;
    int visitados[TAM_VERTICES], i;

    for(i = 0; i < TAM_VERTICES; i++) visitados[i] = 0;

    while(topoVTC != NULL && topoVTC->id != localizacao)    topoVTC = topoVTC->seguinte;

    if(topoVTC == NULL) return 0;
    else 
    {
        visitados[topoVTC->id] = 1;
        int dist = 0;

        procurarMeiosRaioAux(auxVTC, topoVTC->id, visitados, dist, raio);

        RM* aux = NULL;

        for(i = 0; i < TAM_VERTICES; i++)
        {
            if(visitados[i] == 1)
            {
                char *geocode = malloc(sizeof(char) * TAM_MORADA);

                geocode = procurarMorada(auxVTC, i);

                RM* topoM = auxM;
                while(topoM != NULL)
                {
                    if(strcmp(topoM->nome, veiculo) == 0 && strcmp(geocode,topoM->localizacao) == 0 && topoM->alugado == 0)
                    {
                        aux = adicionarMeio(aux, topoM->ID, topoM->nome, topoM->localizacao, topoM->bateria, topoM->autonomia, topoM->custo, topoM->alugado, topoM->NIF, topoM->tempoinicial);
                    }
                    topoM = topoM->seguinte;
                }
            }
        }

        ordenarMeios(&aux);

        return 1;
    }
}

/// @brief esta funcao anda pelos vtc e devolve acima um do valor mais alto
/// @param auxVTC apontador para o topo da lista dos vertices
/// @return devolve acima um do valor mais alto, se ja tiver atingido o max verifica se tem algum numero que ainda nao esta registado, caso contrario devolve -1, se for o primeiro devolve 0
int darIDVertice(VTC* auxVTC)
{
    VTC* topoVTC = auxVTC;
    int visitados[TAM_VERTICES], i;

    for(i = 0; i < TAM_VERTICES; i++)   visitados[i] = 0;

    if(topoVTC == NULL) return 0;

    int aux = 0;

    while (topoVTC != NULL)
    {
        visitados[topoVTC->id] = 1;
        if (topoVTC->id > aux)  aux = topoVTC->id;
        topoVTC = topoVTC->seguinte;
    }

    if (aux == (TAM_VERTICES - 1))
    {
        for(i = 0; i < TAM_VERTICES; i++)
        {
            if(visitados[i] == 0)  return i; 
        }

        return -1;
    }
    else    return ++aux;
}

/// @brief esta funcao verifica se um vertice introduzido é valido ou nao
/// @param auxVTC apontador para o topo dos vertices
/// @param v vertice introduzido que queremos verificar
/// @return retorna 1 se for valido e 0 caso contrario
int verificarVerticeValido(VTC* auxVTC, int v)
{
    if(v >= 0 && v < TAM_VERTICES)
    {
        VTC* topoVTC = auxVTC;

        while(topoVTC != NULL)
        {
            if(v == topoVTC->id) return 1;
            topoVTC = topoVTC->seguinte;
        }

        if(topoVTC == NULL) return 0;
    }
    else return 0;
}

int verificarArestaValida(VTC* auxVTC, int v1, int v2)
{
    VTC* topoVTC = auxVTC;

    while(topoVTC != NULL && topoVTC->id != v1) topoVTC = topoVTC->seguinte;

    if(topoVTC == NULL) return 0;
    else
    {
        ADJ* adj = topoVTC->adjacentes;

        while(adj != NULL)
        {
            if(adj->adj == v2)  return 1;
            adj = adj->seguinte;
        }
        
        return 0;
    }
}

CM* adicionarCM(CM* auxCM, int vtc)
{
    CM* topoCM = auxCM;

    while(topoCM != NULL)
    {
        if(topoCM->vertice == vtc)
        {
            topoCM->quantidade++;
            return auxCM;
        }
        topoCM  = topoCM->seguinte;
    }

    CM* novo = malloc(sizeof(CM));

    novo->quantidade = 1;
    novo->vertice = vtc;

    if(auxCM == NULL) novo->seguinte = NULL;
    else novo->seguinte = auxCM;

    return novo;
}

int caminhoMaisCurto(VTC* auxVTC, int v1, int v2)   // falta andar pelos adjs dos adjs e fzr o de voltar ao vtc que tava anteriormente escolhido
{
    VTC* topoVTC = auxVTC;
    float vertices[TAM_VERTICES], vertices_menor[TAM_VERTICES], peso, peso_menor;
    int i, visitados[TAM_VERTICES];

    for(i = 0; i < TAM_VERTICES; i++)   vertices[i] = INFINITO;     //declaramos todos os pesos como infinito inicalmente
    for(i = 0; i < TAM_VERTICES; i++)   visitados[i] = 0;           //declaramos todos os visitados como 0 inicalmente

    vertices[v1] = 0;       // o de origem fica com peso 0
    visitados[v1] = 1;      // e fica visitado tambem

    while(topoVTC != NULL && topoVTC->id != v1)   topoVTC = topoVTC->seguinte;      //vamos ate ao 1 vtc

    if(topoVTC == NULL) return -1;      // se vier nulo e pq o vertice era invalido

    while(topoVTC->adjacentes != NULL)      // vamos aos adj do vtc inicial
    {
        if(vertices[topoVTC->adjacentes->adj] > (peso + topoVTC->adjacentes->peso))    vertices[topoVTC->adjacentes->adj] = peso + topoVTC->adjacentes->peso; // significa que o caminho que estamos a percorrer atualmente nos levou "mais depressa a tal vtc ent substituimos"
        else
        {
            // temos de voltar ate esse vertice com o peso que ja tava la e ver os adjacentes a partir dai pq tinhamos um cmainho menor ate chegar ate tal vtc
        }
        peso = vertices[topoVTC->adjacentes->adj]; // o peso fica sempre com o peso atual do vertice onde tamos, que é o ultimo do caminho ate ao momento, ou seja tem o maior peso

        if(topoVTC->adjacentes->adj == v2 && peso < peso_menor)  // se chegarmos ao vtc desejado e o peso atual for menor que o declarado anteriormente
        {
            peso_menor = peso;  // o peso menor pega o valor deste peso que passa a ser o menor
            for(i = 0; i < TAM_VERTICES; i++)   vertices_menor[i] = vertices[i];    // vtcs para sabermos depois o caminho exato que foi utilizado
        }

        for(i = 0; i < TAM_VERTICES; i++)   vertices[i] = INFINITO; // declaramos tudo de novo para entrar novamente no ciclo
        for(i = 0; i < TAM_VERTICES; i++)   visitados[i] = 0;
        vertices[v1] = 0;
        visitados[v1] = 1;

        topoVTC->adjacentes = topoVTC->adjacentes->seguinte;    // andamos com o clico para a frente e vamos verificar os outros adjacentes do vtc inicial
    }


}

void camiao(RM* auxM, VTC* auxVTC, int nmr)
{
    RM* veiculos = NULL, *topoM = auxM;
    VTC* topoVTC = auxVTC;
    CM* topoCM = NULL;
    int id;

    veiculos = verificarBateria50(auxM);

    if(veiculos == NULL)    printf("Nao ha veiculos disponiveis com bateria inferior a 50 para recolha.\n");
    else
    {
        while(veiculos != NULL)
        {
            id = procurarIDVTC(topoVTC, veiculos->localizacao);

            topoCM = adicionarCM(topoCM, id);

            veiculos = veiculos->seguinte;
        }

        CM* auxCM =  topoCM;

        while(auxCM != NULL)
        {
            //printf("%d %d\n", auxCM->vertice, auxCM->quantidade);
            if(auxCM->quantidade == 0)
            {
                caminhoMaisCurto(auxVTC, auxCM->vertice, auxCM->seguinte->vertice);
                auxCM = auxCM->seguinte;
            }
        }
    }
}