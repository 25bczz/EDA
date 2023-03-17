	#include <stdio.h>
    #include <stdlib.h>

    void limparTela()
	{
		system("@cls||clear");
	}

	void limparBuffer()
	{
		fflush(stdin);
	}

	void enterContinuar()
	{
		limparBuffer();
		printf("Pressione ENTER para continuar..");
		getchar();
	}