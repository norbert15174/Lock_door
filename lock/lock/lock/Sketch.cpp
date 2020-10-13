/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include <Wire.h>   
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include "stdio.h"
#include "avr/io.h"
#include <util/delay.h>
#include <string.h>
//Biblioteki
#include "Control.h"
#include "SERWO.h"
#include "keypad.h"


char Wprowadz_PIN[] = "aaaa";
int ilosc = 0;
#define F_CPU 16000000

/* wskaznik na Wprowadz_PIN uzywany do zmiany zawartosci komorki w pamieci pod adres &Wprowadz_Pin */
char *PIN_wpisany = Wprowadz_PIN;


int a=0;
void setup()  
{
	ekran_startowy();
}

void loop() 
{	
	key();
}
