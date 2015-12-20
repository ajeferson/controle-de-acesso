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
void rtcLeDado(char comando);


// Implementacos

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

void rtcLeDado(char comando) {
	char resultado = 0b11111111;
	char kakaroto[9];

	RTC_SCLK = 0;
	RTC_RST = 1; // RST high

	rtcEnviaByte(comando); // Envia comando pro RTC
	
	TRISAbits.TRISA2 = 1; // IO com input

	// Lendo dados
	kakaroto[7] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[6] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[5] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[4] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[3] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[2] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[1] = RTC_IO;
	rtcSCKLEnviaPulso();

	kakaroto[0] = RTC_IO;
	rtcSCKLEnviaPulso();

	RTC_RST = 0;
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


#endif