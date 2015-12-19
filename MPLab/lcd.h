#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

/** Cont�m todas as funcoes relacionadas ao LCD.  */

/** Definicoes */

/** Envia um valor a ser escrito no barramento do LCD. Para enviar instru��o, o parametro tipo dever ser 1. Para dado, tipo = 0; */
void lcdEnvia(char instrucao, int tipo);

/** Envia uma instru��o para o display LCD */
void lcdEnviaInstrucao(char instrucao);

/** Envia um dado para o display LCD */
void lcdEnviaDado(char dado);

/** Limpa o LCD */
void lcdLimpa();

/** Configuracao inicial do LCD. */
void lcdInicializa();

/** Escreve uma palavra no LCD */
void lcdEscrevePalavra(char palavra[],  int size);

/** Escreve um caracter no LCD */
void lcdEscreveCaracter(char caracter);

/** Faz o cursor do LCD ir para o inicio da linha 1 */
void lcdInicioLinha1();

/** Faz o cursor do LCD ir para o inicio da linha 2 */
void lcdInicioLinha2();

/** Desloca o cursor do LCD para direita */
void lcdDeslocaDireita();

/** Mostra a mensagem de acesso permitido */
void lcdAcessoPermitido();

/** Mostra a mensagem de acesso negado para o usu�rio */
void lcdAcessoNegado();

/** Implementacoes */

void lcdEnvia(char instrucao, int tipo) {

	LCD_RS = !tipo;
	LCD_RW = 0;
	LCD_E = 1;
	
	// Delay de 1 us
	Delay1TCY();
	Delay1TCY();

	LCD_DATA = instrucao; // Escreve instru��o
	LCD_E = 0; // Desabilita o E para a instru��o ir, de fato

	Delay10TCYx(8); // D� delay de 40us aproximadamente
}

void lcdEnviaInstrucao(char instrucao) {
	lcdEnvia(instrucao, 1);
}

void lcdEnviaDado(char dado) {
	lcdEnvia(dado, 0);
}

void lcdLimpa() {
	lcdEnviaInstrucao(0x01); // Instru��o que limpa o display, de fato
	Delay1KTCYx(4); // Delay de 2 ms (mas s� precisa 1.6 ms)
}

void lcdInicializa() {
	lcdEnviaInstrucao(0x30); // Comando que inicializa o LCD (???);
	Delay1KTCYx(8); // Delay de 4ms
	lcdEnviaInstrucao(0x38);
	//lcdLimpa();

	lcdEnviaInstrucao(0x0c); // Liga LCD sem cursor
	//lcdEnviaInstrucao(0x0e); // Liga LCD com cursor
	lcdEnviaInstrucao(0x06); // Sentido do cursor para a direita
	Delay10TCYx(8);
	lcdLimpa();

	//lcdEnviaInstrucao(0x0d); // Cursor piscante
	//Delay10TCYx(8); // Delay de 40 us
}

void lcdEscrevePalavra(char palavra[],  int size) {
	int i;
	for(i=0; i<size; i++) {
		lcdEnviaDado(palavra[i]);
	}
}

void lcdEscreveCaracter(char caracter) {
	lcdEnviaDado(caracter);
}

void lcdInicioLinha1() {
	lcdEnviaInstrucao(0x80);
}

void lcdInicioLinha2() {
	lcdEnviaInstrucao(0xc0);
}

void lcdDeslocaDireita() {
	lcdEnviaInstrucao(0x14);
}

void lcdAcessoPermitido() {
	char linha1[16] = "Acesso Permitido";
	lcdLimpa();
	lcdEscrevePalavra(linha1, 16);
}

void lcdAcessoNegado() {
	char linha1[13] = "Acesso Negado";
	lcdLimpa();
	lcdEscrevePalavra(linha1, 13);
}

#endif