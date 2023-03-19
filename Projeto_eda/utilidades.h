#ifndef UTILIDADES_H_
#define UTILIDADES_H_
 
void limparTela();

void limparBuffer();

void enterContinuar();

int verificarClienteGestor(RC* topoC, RG* topoG, int NIF, char password[]);// Verifica se o usuário é cliente ou gestor, devolve 0 caso seja cliente e devolve 1 caso seja gestor

int verificarClienteNIF(RC* topoC, int NIF);// Devolve 1 se houver um NIF igual já registado e 0 caso contrário

int verificarGestorNIF(RG* topoG, int NIF);// Devolve 1 se houver um NIF igual já registado e 0 caso contrário

int verificarAlugado(RM* topoM, int ID);

int verificarPasswordAntigaClientes(RC* topoC, int NIF, char password[]);

int verificarPasswordAntigaGestores(RG* topoG, int NIF, char password[]);

#endif