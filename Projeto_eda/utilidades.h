#ifndef UTILIDADES_H
#define UTILIDADES_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

void limparTela();

void limparBuffer();

void enterContinuar();

void imprimirLogo();

void imprimirDadosCliente(RC* auxC, int NIF);

void imprimirDadosGestor(RG* auxG, int NIF);

int verificarClienteGestor(RC* auxC, RG* auxG, int NIF, char password[]);

int verificarClienteNIF(RC* auxC, int NIF);

int verificarGestorNIF(RG* auxG, int NIF);

int verificarAlugado(RM* auxM, int ID);

int verificarAlugadoNIF(RM* auxM, int ID, int NIF);

int verificarPasswordAntigaClientes(RC* auxC, int NIF, char password[]);

int verificarPasswordAntigaGestores(RG* auxG, int NIF, char password[]);

#endif
