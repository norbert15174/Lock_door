#ifndef keypad_H_
#define keypad_H_
#include "keypad.c"
unsigned char keypad[4][3] = { {'1','2','3'},
							   {'4','5','6'},
							   {'7','8','9'},
							   {'*','0','#'} };
/*		WIERSZE    */
#define PORT_W PORTD
#define DDR_W DDRD
/*    KOLUMNY      */
#define PORT_K PORTC
#define DDR_K DDRC
#define PIN_K PINC
#define PIN_K0 PINC0 // pierwsza kolumna
#define PIN_K1 PINC1 // druga kolumna
#define PIN_K2 PINC2 // trzecia kolumna

char key();
void init_UART(void);
int uart_putchar(char c, FILE *stream);
#endif