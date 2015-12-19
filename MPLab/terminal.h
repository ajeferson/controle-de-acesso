#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

// Definicoes

/** Escreve uma letra no terminal */
void terminalEscreveLetra(char letra);

/** Escreve uma linha no terminal */
void terminalEscreveLinha(char *linha, int tamanho);


// Implementacoes

void terminalEscreveLetra(char letra) {

		char aux;
		char mask = 0b10000000;
		char delay = 20;

		TERMINAL = 1;
		Delay10TCYx(delay);

		TERMINAL = 0;
		Delay10TCYx(delay);

		aux = (letra << 7) & mask;
		aux = aux >> 7;
		TERMINAL = aux; // 1
		Delay10TCYx(delay);

		aux = (letra << 6) & mask;
		aux = aux >> 7;
		TERMINAL = aux; // 2
		Delay10TCYx(delay);

		aux = (letra << 5) & mask;
		aux = aux >> 7;			
		TERMINAL = aux; //3
		Delay10TCYx(delay);

		aux = (letra << 4) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //4
		Delay10TCYx(delay);

		aux = (letra << 3) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //5
		Delay10TCYx(delay);

		aux = (letra << 2) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //6
		Delay10TCYx(delay);

		aux = (letra << 1) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //7
		Delay10TCYx(delay);

		aux = (letra << 0) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //8
		Delay10TCYx(delay);

		TERMINAL = 1; // 1111
		Delay10TCYx(20);

}

void terminalEscreveLinha(char *linha, int tamanho) {
	int i;
	for(i=0; i<tamanho; i++) {
		terminalEscreveLetra(linha[i]);
	}
	terminalEscreveLetra(13);
}

#endif