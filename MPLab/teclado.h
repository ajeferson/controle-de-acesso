#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

// Definicoes

/** Faz a varredura do teclado e retorna a tecla apertada. */
char varreTeclado();

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

#endif