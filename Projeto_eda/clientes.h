#ifndef CLIENTES_H_
#define CLIENTES_H_
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

//fzr listagem clientes

RC* adicionarCliente(RC* topoC, char nome[], char morada[], char password[], int NIF, int idade);

RC* removerCliente(RC* topoC, int NIF);

RC* editarDados(RC* topoC, int NIF);

RC* carregarSaldo(RC* topoC, int NIF, float pagamento);

int Alugar(RC* topoC, RM* topoM, RA* topoA, int ID, int NIF);

int existeCliente(RC* topoC, int NIF, char password[]);

int verificarPasswordAntigaClientes(RC* topoC, int NIF, char password[]);

#endif