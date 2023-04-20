#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "clientes.h"
#include "meios.h"
#include "gestores.h"
#include "ficheiros.h"
#include "utilidades.h"

/* Utilizado para dar debug
#include "menu.c"
#include "clientes.c"
#include "meios.c"
#include "gestores.c"
#include "ficheiros.c"
#include "utilidades.c"
*/

/// @brief Esta função acede ao menu de interação
void main()
{
	int op;
	RC* topoC = NULL;
	RG* topoG = NULL;
	RM* topoM = NULL;
	RA* topoA = NULL;

    topoC = conteudoRC();
	topoG = conteudoRG();
	topoM = conteudoRM();
	topoA = conteudoRA();

    do
    {
        limparTela();
        printf("Introduza a opcao que desejar:\n1 - Login\n2 - Registro\n0 - Sair\n");
        scanf("%d", &op);
        limparTela();
        switch(op)
        {
            case 1:
            {
                menuLogin(&topoC, &topoG, &topoM, &topoA);
                break; 
            }
            case 2:
            {
                menuRegistro(&topoC, &topoG, &topoM, &topoA);
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

    adicionarFicheiro(topoC, topoG, topoM, topoA);
    adicionarFicheiroBin(topoC, topoG, topoM, topoA);
}