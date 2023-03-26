#ifndef FICHEIROS_H
#define FICHEIROS_H

typedef struct registo_cliente RC;
typedef struct registo_gestor RG;
typedef struct registo_meio RM;
typedef struct registo_alugueres RA;

//				FICHEIROS DE TEXTO

RC* conteudoRC();

RG* conteudoRG();

RM* conteudoRM();

RA* conteudoRA();

void adicionarFicheiro(RC* auxC, RG* auxG, RM* auxM, RA* auxA);


//				FICHEIROS BINÁRIOS

RC* conteudoBinRC();

RG* conteudoBinRG();

RM* conteudoBinRM();

RA* conteudoBinRA();

void adicionarFicheiroBin(RC* auxC, RG* auxG, RM* auxM, RA* auxA);

#endif