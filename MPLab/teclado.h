#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

// Definicoes

/** Faz a varredura do teclado e retorna a tecla apertada. */
char varreTeclado();

/** Executa alguma acao de acordo com a tecla pressionada pelo usuario */
char processaTecla(char tecla, char estado);

/** Processa uma tecla apertada estando no menu inicial */
char processaMenuInicial(char tecla, char estado);

/** Processa uma tecla digitada estando no menu de inserir senha */
char processaSenha(char tecla, char secreto);

static char deslocamento = 0;

// Implementacoes

char varreTeclado() {
	Linha_1=1; //varrendo a primeira linha
	Linha_2=0;
	Linha_3=0;
	Linha_4=0;

	if (Coluna_1) { while (Coluna_1) {} return 1;}
	if (Coluna_2) { while (Coluna_2) {} return 2;}
	if (Coluna_3) { while (Coluna_3) {} return 3;}
	if (Coluna_4) { while (Coluna_4) {} return 'A';}

	Linha_1=0; //varrendo a segunda linha
	Linha_2=1;
	Linha_3=0;
	Linha_4=0;
	if (Coluna_1) { while (Coluna_1) {} return 4;}
	if (Coluna_2) { while (Coluna_2) {} return 5;}
	if (Coluna_3) { while (Coluna_3) {} return 6;}
	if (Coluna_4) { while (Coluna_4) {} return 'B';}
	Linha_1=0; //varrendo a terceira linha
	Linha_2=0;	
	Linha_3=1;
	Linha_4=0;
	if (Coluna_1) { while (Coluna_1) {} return 7;}
	if (Coluna_2) { while (Coluna_2) {} return 8;}
	if (Coluna_3) { while (Coluna_3) {} return 9;}
	if (Coluna_4) { while (Coluna_4) {} return 'C';}

	Linha_1=0; //varrendo a quarta linha
	Linha_2=0;
	Linha_3=0;
	Linha_4=1;
	if (Coluna_1) { while (Coluna_1) {} return '*';}
	if (Coluna_2) { while (Coluna_2) {} return 0;}
	if (Coluna_3) { while (Coluna_3) {} return '#';}
	if (Coluna_4) { while (Coluna_4) {} return 'D';}

	return 'K';

}

char processaTecla(char tecla, char estado) {

	if(tecla != 'K') {
		// Menu inicial
		if(estado == 1) {
			return processaMenuInicial(tecla, estado);
		} else if (estado == 2) {
			return processaSenha(tecla, 1);
		}
	}

	return estado;
}

char processaMenuInicial(char tecla, char estado) {
	switch(tecla) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			deslocamento = 0;
			menuSenha();
			return 2; // Menu de digitar senha
	}

	return estado;

}

char processaSenha(char tecla, char secreto) {
	
	int i;

	if(tecla != '*' && tecla != '#') {

		lcdInicioLinha2();

		for(i=0; i<deslocamento; i++) {
			lcdDeslocaDireita();
		}

		if(secreto) {
			lcdEscreveCaracter('*');
		} else {
			lcdEscreveCaracter(tecla + 48); // Offset dos chars dos numeros
		}

		deslocamento++;
	}
	return 2;
}

#endif