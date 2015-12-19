#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

char senha[16];
char deslocamento = 0;

char countSenhas = 1;
char senhas[11][16] = {
	{1, 2, 3, 4, 5, 6, '\0'}
};

// Definicoes

/** Executa alguma acao de acordo com a tecla pressionada pelo usuario */
char processaTecla(char tecla, char estado);

/** Processa uma tecla apertada estando no menu inicial */
char processaMenuInicial(char tecla, char estado);

/** Processa uma tecla digitada estando no menu de inserir senha */
char processaSenha(char tecla, char secreto);

/** Verifica se a senha passada pertence a algum dos usuarios cadastrados */
char checaSenha(char senha[]);

// Implementacoes

char processaTecla(char tecla, char estado) {

	if(tecla != 'K') {
		// Menu inicial
		if(estado == 1) {
			return processaMenuInicial(tecla, estado);
		} else if(estado == 2) {
			return processaSenha(tecla, 1);
		} else if(estado == 3) {
			menuInicial();
			return 1;
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

	if(tecla != '*') {
		
		if(tecla != '#') {

			lcdInicioLinha2();

			for(i=0; i<deslocamento; i++) {
				lcdDeslocaDireita();
			}

			if(secreto) {
				lcdEscreveCaracter('*');
			} else {
				lcdEscreveCaracter(tecla + 48); // Offset dos chars dos numeros
			}

			senha[deslocamento] = tecla;
			deslocamento++;

		} else {

			// Digitou toda a senha
			senha[deslocamento] = '\0';

			if(checaSenha(senha) >= 0) {
				lcdAcessoPermitido();	
			} else {
				lcdAcessoNegado();
			}

			return 3;

		}
	}

	return 2;

}

char checaSenha() {
	int i;
	for(i=0; i<countSenhas; i++) {
		if(strcmp(senhas[i], senha) == 0) {
			return i;
		}
	}
	return -1;
}

#endif