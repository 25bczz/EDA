#ifndef CLIENTES_H
#define CLIENTES_H
#define TAM_NOME 50
#define TAM_MORADA 100
#define TAM_PASSWORD 30
#define TAM_LINHA 200
#define TAM_VERTICES 18
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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
typedef struct registo_vertices VTC;
typedef struct registo_adjacentes ADJ;

RC* adicionarCliente(RC* auxC, char nome[], char morada[], char password[], int NIF, int idade, float saldo);

RC* editarDadosCliente(RC* auxC, VTC* auxVTC, int NIF);

RC* removerCliente(RC* auxC, int NIF);

void listarClientes(RC* auxC);

RC* carregarSaldo(RC* auxC, int NIF, float pagamento);

RC* editarSaldo(RC* auxC, int NIF, float pagamento);

RC* removerSaldo(RC* auxC, int NIF, float pagamento);

int Alugar(RC* auxC, RM* auxM, int ID, int NIF);

int cancelarAluguer(RC* auxC, RM* auxM, RA** auxA, int ID, int NIF);

void pesquisarLocalidade(RM* auxM, char localidade[]);

#endif