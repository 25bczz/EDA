#ifndef FICHEIROS_H_
#define FICHEIROS_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

//				FICHEIROS DE TEXTO

RC* conteudoRC();// Função para ler do ficheiro clientes.txt e adicionar à lista topoC e devolver o endereço inicial da lista após ler tudo

RG* conteudoRG();// Função para ler do ficheiro gestores.txt e adicionar à lista topoG e devolver o endereço inicial da lista após ler tudo

RM* conteudoRM();// Função para ler do ficheiro meios.txt e adicionar à lista topoM e devolver o endereço inicial da lista após ler tudo

RA* conteudoRA();// Função para ler do ficheiro alugueres.txt e adicionar à lista topoA e devolver o endereço inicial da lista após ler tudo

void adicionarFicheiro(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro


//				FICHEIROS BINÁRIOS

RC* conteudoBinRC();// Função para ler do ficheiro clientes.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo

RG* conteudoBinRG();// Função para ler do ficheiro gestores.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo

RM* conteudoBinRM();// Função para ler do ficheiro meios.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo

RA* conteudoBinRA();// Função para ler do ficheiro alugueres.bin e adicionar à lista aux e devolver o endereço inicial da lista após ler tudo

void adicionarFicheiroBin(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Função que vai percorrendo as listas recebidas por parâmetros e vai adicionando ao respetivo ficheiro

#endif