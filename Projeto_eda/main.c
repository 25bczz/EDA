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

#include "menu.c"
#include "clientes.c"
#include "meios.c"
#include "gestores.c"
#include "ficheiros.c"
#include "utilidades.c"
#include "grafos.c"


/// @brief Esta função acede ao menu de interação
void main()
{
	int op;
	RC* topoC = NULL;
	RG* topoG = NULL;
	RM* topoM = NULL;
	RA* topoA = NULL;
    VTC* topoVTC = NULL;

    topoC = conteudoRC();
	topoG = conteudoRG();
	topoM = conteudoRM();
	topoA = conteudoRA();
    topoVTC = conteudoVTC();
    topoVTC = conteudoADJ(topoVTC);

    do
    {
        limparTela();
        imprimirLogo();
        printf("Introduza a opcao que desejar:\n1 - Login\n2 - Registro\n0 - Sair\n");
        scanf("%d", &op);
        limparTela();
        switch(op)
        {
            case 1:
            {
                menuLogin(&topoC, &topoG, &topoM, &topoA, &topoVTC);
                break; 
            }
            case 2:
            {
                menuRegistro(&topoC, &topoG, topoVTC);
                break;
            }
            case 0: break;
            default:
            {
                limparTela();
                printf("Opcao invalida.\n");
                enterContinuar();
                break;
            }
        }
    }while(op != 0);

    adicionarFicheiro(topoC, topoG, topoM, topoA, topoVTC);
    adicionarFicheiroBin(topoC, topoG, topoM, topoA, topoVTC);
}
