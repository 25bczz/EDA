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

RC* adicionarCliente(RC* auxC, char nome[], char morada[], char password[], int NIF, int idade);

RC* editarDadosCliente(RC* auxC, int NIF);

RC* removerCliente(RC* auxC, int NIF);

void listarClientes(RC* auxC);

RC* carregarSaldo(RC* auxC, int NIF, float pagamento);

int Alugar(RC* auxC, RM* auxM, RA* auxA, int ID, int NIF);

RM* pesquisarLocalidade(RM* auxM, char localidade[]);

#endif