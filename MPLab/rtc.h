#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED

// Definicoes

/** Envia um pulso para o SCKL */
void rtcSCKLEnviaPulso();

/** Envia um byte para o RTC */
void rtcEnviaByte(char byte);

/** Seta os valores iniciais do RTC antes de transferir */
void rtcInicializa();

/** Le os dados do RTC */
void rtcLeDado(char comando, char *resultado);

/** Converte um nibble em um caractere */
char rtcNibbleParaChar(char *nibble);

/** Le o ano a partir do RTC */
void rtcLeAno(char *ano);

/** Le o mes a partir do RTC */
void rtcLeMes(char *mes);

/** Le o dia a partir do RTC */
void rtcLeDia(char *dia);

/** Le a hora a partir do RTC */
void rtcLeHora(char *hora);

/** Le o minuto a partir do RTC */
void rtcLeMinuto(char *minuto);

/** Le o segundo a partir do RTC */
void rtcLeSegundo(char *segundo);

/** Le a data a partir do RTC */
void rtcLeData(char *data);

// Implementacos

char rtcNibbleParaChar(char *nibble) {
	char i;
	char resultado = 0;

	if(nibble[0]) {
		resultado += 8;
	}

	if(nibble[1]) {
		resultado += 4;
	}

	if(nibble[2]) {
		resultado += 2;
	}

	if(nibble[3]) {
		resultado += 1;
	}

	return resultado + 48;

}

void rtcSCKLEnviaPulso() {
	RTC_SCLK = 0;
	RTC_SCLK = 1;
	Delay10TCYx(2); //delay 10us
	RTC_SCLK = 0;
	Delay10TCYx(2); //delay 10us
}

void rtcEnviaByte(char byte) {
	char i;
	char mask = 0b10000000;
	char aux;

	TRISAbits.TRISA2 = 0; // IO com output

	//Enviando byte
	aux = (byte << 7) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 6) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 5) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 4) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 3) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 2) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = (byte << 1) & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

	aux = byte & mask;
	RTC_IO = aux >> 7;
	rtcSCKLEnviaPulso();

}

void rtcEnviaComandoEDado(char comando, char dado) {
	RTC_SCLK = 0;	
	RTC_RST = 1;
	rtcEnviaByte(comando);
	rtcEnviaByte(dado);
	RTC_RST = 0;
}

void rtcLeDado(char comando, char *resultado) {
	char aux1[4], aux2[4];

	RTC_SCLK = 0;
	RTC_RST = 1; // RST high

	rtcEnviaByte(comando); // Envia comando pro RTC
	
	TRISAbits.TRISA2 = 1; // IO como input

	// Lendo dados
	aux2[3] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux2[2] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux2[1] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux2[0] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux1[3] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux1[2] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux1[1] = RTC_IO;
	rtcSCKLEnviaPulso();

	aux1[0] = RTC_IO;
	rtcSCKLEnviaPulso();

	RTC_RST = 0;

	resultado[0] = rtcNibbleParaChar(aux1);
	resultado[1] = rtcNibbleParaChar(aux2);
	resultado[2] = '\0';
	
}

void rtcInicializa() {
	/*RTC_RST = 1;
	RTC_IO = 0x8e;
	RTC_IO = 0x00; // desabilitando WP
	RTC_RST = 0;
	RTC_RST = 1;
	RTC_IO = 0x80;
	RTC_IO = 0x00;  // enabling oscilattor
	RTC_RST = 0;*/

	rtcEnviaComandoEDado(0x83, 0x00);
	rtcEnviaComandoEDado(0x80, 0x00);

	// Delay de 3s para estabilizar o cristal
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);

}

void rtcLeAno(char *ano) {
	rtcLeDado(0x8d, ano); // 10001101
}

void rtcLeMes(char *mes) {
	rtcLeDado(0x89, mes); // 10001001
}

void rtcLeDia(char *dia) {
	rtcLeDado(0x87, dia); // 10001011
}

void rtcLeHora(char *hora) {
	rtcLeDado(0x85, hora); // 10000101
}

void rtcLeMinuto(char *minuto) {
	rtcLeDado(0x83, minuto); // 10000011
}

void rtcLeSegundo(char *segundo) {
	rtcLeDado(0x81, segundo); // 10000001
}

void rtcLeData(char *data) {

	// Dia
	rtcLeDia(data);
	data[2] = '/';

	// Mes
	rtcLeMes(&data[3]);
	data[5] = '/';

	// Ano
	data[6] = '2';
	data[7] = '0';
	rtcLeAno(&data[8]);
	data[10] = ' ';

	// Hora
	rtcLeHora(&data[11]);
	data[13] = ':';
	
	// Minuto
	rtcLeMinuto(&data[14]);
	data[16] = ':';

	// Segundo
	rtcLeSegundo(&data[17]);
	data[19] = '\0';
}

#endif