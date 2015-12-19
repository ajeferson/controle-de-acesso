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

/** Mostra uma mensagem de memoria cheia */
void menuSemEspacoDisponivel();

/** Mostra o menu que pede o numero do usuario a ser deletado. */
void menuRemoveUsuario();

/** Menu alertando que nao ha usuarios cadastrados */
void menuNenhumUsuario();

/** Menu mostrando que um usuario e invalido */
void menuUsuarioInvalido();

/** Menu mostrando que um usuario foi removido */
void menuUsuarioRemovido(char usuario);

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

void menuSemEspacoDisponivel() {
	char linha1[14] = "Memoria cheia";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 13);
}

void menuRemoveUsuario() {
	char linha1[17] = "Num. do usuario:";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 16);
}

void menuNenhumUsuario() {
	char linha1[15] = "Nenhum usuario";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 14);
}

void menuUsuarioInvalido() {
	char linha1[17] = "Usuario invalido";
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 16);
}

void menuUsuarioRemovido(char usuario) {
	char linha1[10] = "Usuario X";
	char linha2[9] = "deletado";
	linha1[8] = usuario + 48;
	lcdLimpa();
	lcdInicioLinha1();
	lcdEscrevePalavra(linha1, 9);
	lcdInicioLinha2();
	lcdEscrevePalavra(linha2, 8);
}

#endif