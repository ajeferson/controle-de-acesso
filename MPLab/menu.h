#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/** Contem as funcoes relacionadas aos menus */

/** Definicoes */

/** Printa no LCD o menu com as opcoes de cadastro, remocao e logar */
void menuInicial();


/** Implementacoes */

void menuInicial() {
	char linha1[16] = "Contr. de acesso";
	char linha2[16] = "1Cad 2Del 3Entra";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 16);
	lcdInicioLinha2();
	lcdEscrevePalavra(linha2, 16);
}

#endif