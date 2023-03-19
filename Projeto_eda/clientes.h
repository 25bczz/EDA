#ifndef CLIENTES_H_
#define CLIENTES_H_
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

typedef struct registo_cliente
{
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF, idade;
	float saldo;
	struct registo_cliente* seguinte;
}RC;

RC* adicionarCliente(RC* topoC, char nome[], char morada[], char password[], int NIF, int idade);

RC* editarDadosCliente(RC* topoC, int NIF);

RC* removerCliente(RC* topoC, int NIF);

void listarClientes(RC* topoC);

RC* carregarSaldo(RC* topoC, int NIF, float pagamento);

int Alugar(RC* topoC, RM* topoM, RA* topoA, int ID, int NIF);

RM* pesquisarLocalidade(RM* topoM, char localidade[]);

#endif