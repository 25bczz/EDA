#ifndef MENU_H_
#define MENU_H_

void menu();// Menu de interação com o cliente

void menuLogin(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuRegistro(RC* topoC, RG* topoG, RM* topoM, RA* topoA);// Menu de interação com o cliente

void menuCliente(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

void menuGestor(RC* topoC, RG* topoG, RM* topoM, RA* topoA, int NIF);// Menu de interação com o cliente

int verificarClienteGestor(RC* topoC, RG* topoG, int NIF, char password[]);// Verifica se o usuário é cliente ou gestor, devolve 0 caso seja cliente e devolve 1 caso seja gestor

int verificarClienteNIF(RC* topoC, int NIF);// Devolve 1 se houver um NIF igual já registado e 0 caso contrário

int verificarGestorNIF(RG* topoG, int NIF);// Devolve 1 se houver um NIF igual já registado e 0 caso contrário

#endif