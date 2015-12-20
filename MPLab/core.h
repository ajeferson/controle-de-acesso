#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

char senha[16];
char deslocamento = 0;

char countSenhas = 1;
char senhas[11][17] = {
	{1, 2, 3, 4, 5, 6, '\0'},
	{'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}
};

// Definicoes

/** Executa alguma acao de acordo com a tecla pressionada pelo usuario */
char processaTecla(char tecla, char estado);

/** Processa uma tecla apertada estando no menu inicial */
char processaMenuInicial(char tecla, char estado);

/** Processa uma tecla digitada estando no menu de inserir senha */
char processaSenha(char tecla, char secreto, char estado);

/** Verifica se a senha passada pertence a algum dos usuarios cadastrados */
char checaSenha(char senha[]);

/** Coloca uma nova senha no array de senhas */
int cadastraUsuario();

/** Verifica se ainda ha espaco no array para o cadastro de usuarios. */
int verificaEspaco();

/** Remove um usuario do array */
char removeUsuario(char usuario);

/** Retorna o index do usuario na hora de deletar */
int indexDoUsuario();

// Implementacoes

char processaTecla(char tecla, char estado) {

	if(tecla != 'K') {
		if(estado == 1) { // Menu inicial
			return processaMenuInicial(tecla, estado);
		} else if(estado == 2 || estado == 4 || estado == 5 || estado == 6) {
			return processaSenha(tecla, 1, estado);
		} else if(estado == 3) { // Tela de mensagem
			menuInicial();
			return 1;
		} else if(estado == 7) { // Escolhendo usuario a remover
			return processaSenha(tecla, 0, estado);
		}
	}

	return estado;
}

char processaMenuInicial(char tecla, char estado) {
	switch(tecla) {
		case 1:
			if(verificaEspaco()) {
				deslocamento = 0;
				menuSenha();
				return 4;
			} else {
				menuSemEspacoDisponivel();
				return 3;
			}
		case 2:
			if(countSenhas > 1) {
				deslocamento = 0;
				menuSenha();
				return 6;
			} else {
				menuNenhumUsuario();
				return 3;
			}
		case 3:
			deslocamento = 0;
			menuSenha();
			return 2; // Menu de digitar senha
	}

	return estado;

}

char processaSenha(char tecla, char secreto, char estado) {
	
	int i;
	char usuario;

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

			if(deslocamento == 0) {
				return estado;
			}

			// Digitou toda a senha
			senha[deslocamento] = '\0';

			if(estado != 5 && estado != 7) {
				usuario = checaSenha(senha);
				if(usuario < 0) {
					lcdAcessoNegado();
					terminalEscreveTentativaLogin();
					return 3;
				}
			}

			if (estado == 2) { // Login
				lcdAcessoPermitido();
				terminalEscreveLoginRealizado(usuario);
				return 3;
			} else if (estado == 4) { // Pre-Cadastro
				if(usuario == 0) {
					deslocamento = 0;
					menuSenhaCadastro();
					terminalEscreveLoginRealizado(usuario);
					return 5;
				} else {
					lcdAcessoNegado();
					terminalEscreveTentativaLogin();
					return 3;
				}
			} else if (estado == 5) { // Cadastro
				usuario = cadastraUsuario();
				menuUsuarioCadastrado(usuario);
				terminalUsuarioCadastrado(usuario);
				return 3;
			} else if (estado == 6) { // Pre-remocao
				if(usuario == 0) {
					deslocamento = 0;
					menuRemoveUsuario();
					terminalEscreveLoginRealizado(usuario);
					return 7;
				} else {
					lcdAcessoNegado();
					terminalEscreveTentativaLogin();
					return 3;
				}
			} else if (estado == 7) {
				usuario = indexDoUsuario();
				if(usuario == 0) {
					menuUsuarioInvalido();
					return 3;
				} else {
					if(removeUsuario(usuario)) {
						menuUsuarioRemovido(usuario);
						terminalUsuarioDeletado(usuario);
					} else {
						menuUsuarioInvalido();
						terminalEscreveTentativaDelecao();
					}
					return 3;
				}
			}

		}
	}

	return estado;

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

int cadastraUsuario() {
	char i = 0;
	while(i<11 && senhas[i][0] != '\0') {
		i++;
	}
	strcpy(senhas[i], senha);
	countSenhas++;
	return i;
}

int verificaEspaco() {
	char i = 0;
	while(i<11) {
		if(senhas[i][0] == '\0') {
			return 1;
		}
		i++;
	}
	return 0;
}

char removeUsuario(char usuario) {
	if(usuario > 0 && usuario < 11 && senhas[usuario][0] != '\0') {
		senhas[usuario][0] = '\0';
		return 1;
	}
	return 0;
}

int indexDoUsuario() {
	char i;
	senha[deslocamento] = '\0';
	for(i=0;i<deslocamento;i++) {
		senha[i] = senha[i] + 48;
	}
	return atoi(senha);
}

#endif