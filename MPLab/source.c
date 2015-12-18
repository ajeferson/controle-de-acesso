#include <p18f4550.h>
#include <delays.h>

// Configuração do microcontrolador para execução de instruções
#pragma config FOSC = HS    /// EXTERN CLOCK 8MHZ
#pragma config WDT = OFF   /// DISABLE WATCHDOG TIMER
#pragma config WDTPS = 32768 /// WATCHDOG TIMER 32768s
#pragma config PBADEN = OFF   /// PORTB.RB0,1,2,3,4 AS I/O DIGITAL
#pragma config MCLRE = OFF

// LCD variables
#define LCD_RS LATEbits.LATE0
#define LCD_RW LATEbits.LATE2
#define LCD_E LATEbits.LATE1
#define LCD_DATA LATD

// Include da galera
#include "lcd.h"
#include "menu.h"

#pragma mark Definicao das funcoes
void configuraSistema();
void lcdEnviaInstrucao(char instrucao);
void lcdEnviaDado(char dado);
void delay_us(int quantidade);

#pragma mark Implementacao da funcoes

/** Seta os tris da galera */
void configuraSistema() {
	ADCON1=0x0F;
	TRISD=0b00000000;  
	TRISE=0b11111000;
}

void main() {

	configuraSistema();

	lcdInicializa();

	menuInicial();
	menuSenha();
	appendaSenha('*', 0);
	appendaSenha('*', 1);
	appendaSenha('*', 2);
	appendaSenha('*', 3);

	while(1) {
	}
}