#ifndef CLIENTES_H
#define CLIENTES_H
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30

typedef struct registo_cliente
{
	char nome[TAM_NOME], morada[TAM_MORADA], password[TAM_PASSWORD];
	int NIF, idade;
	float saldo;
	struct registo_cliente* seguinte;
}RC;

typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

RC* adicionarCliente(RC* topoC, char nome[], char morada[], char password[], int NIF, int idade);

RC* editarDadosCliente(RC* topoC, int NIF);

RC* removerCliente(RC* topoC, int NIF);

void listarClientes(RC* topoC);

RC* carregarSaldo(RC* topoC, int NIF, float pagamento);

int Alugar(RC* topoC, RM* topoM, RA* topoA, int ID, int NIF);

RM* pesquisarLocalidade(RM* topoM, char localidade[]);

#endif