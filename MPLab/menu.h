#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/** Contem as funcoes relacionadas aos menus */

/** Definicoes */

/** Printa no LCD o menu com as opcoes de cadastro, remocao e logar */
void menuInicial();

/** Mostra o menu que pede para o usuário digitar a senha. */
void menuSenha();

/** Mostra o menu para colocar a senha de um novo usuário */
void menuSenhaCadastro();

/** Mostra no LCD um menu dizendo que um usuario foi cadastrado */
void menuUsuarioCadastrado(char usuario);

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

void menuSenha() {
	char linha1[15] = "Digite a senha:";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 15);
}

void menuSenhaCadastro() {
	char linha1[17] = "Cadastro usuario";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 16);
}

void menuUsuarioCadastrado(char usuario) {
	char linha1[10] = "Usuario X";
	char linha2[11] = "cadastrado";
	linha1[8] = usuario + 48;
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 9);
	lcdInicioLinha2();
	lcdEscrevePalavra(linha2, 10);
}

#endif