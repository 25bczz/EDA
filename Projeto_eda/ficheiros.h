#ifndef FICHEIROS_H
#define FICHEIROS_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;
typedef struct registo_vertices VTC;
typedef struct registo_arestas GRAFO;

//				FICHEIROS DE TEXTO

RC* conteudoRC();

RG* conteudoRG();

RM* conteudoRM();

RA* conteudoRA();

VTC* conteudoVTC();

GRAFO* conteudoGRAFO();


void adicionarFicheiro(RC* auxC, RG* auxG, RM* auxM, RA* auxA, VTC* auxVTC, GRAFO* auxGRAFO);


//				FICHEIROS BINÁRIOS

RC* conteudoBinRC();

RG* conteudoBinRG();

RM* conteudoBinRM();

RA* conteudoBinRA();

VTC* conteudoBinVTC();

GRAFO* conteudoBinGRAFO();

void adicionarFicheiroBin(RC* auxC, RG* auxG, RM* auxM, RA* auxA, VTC* auxVTC, GRAFO* auxGRAFO);

#endif