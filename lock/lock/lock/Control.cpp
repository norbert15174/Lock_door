/* BIBLIOTEKI */
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Control.h"
#include <stdio.h>
#include <avr/io.h>


/* UTWORZENIE KLASY EKRAN I USTAWIENIE WYSWIETLANIA (DLATEGO W C++ , PONIWAZ UZYWANA JEST KLASA) */
LiquidCrystal_I2C ekran(0x27, 16, 2);

/*FUNKCJE DO KONTROLI WYSWIETLACZA */
void ustawienie_ekranu_1(){
	ekran.clear();
	ekran.begin(16,2);
	ekran.init();
	ekran.backlight();
	ekran.setCursor(0,0);
}
void ustawienie_ekranu_2(){
	ekran.clear();
	ekran.begin(16,2);
	ekran.init();
	ekran.backlight();
	ekran.setCursor(0,0);
}
void ustawienie_ekranu_1_2(char * linia1, char * linia2){
	ekran.clear();
	ekran.begin(16,2);
	ekran.init();
	ekran.backlight();
	ekran.setCursor(0,0);
	ekran.print(linia1);
	ekran.setCursor(0,1);
	ekran.print(linia2);
}

void ekran_startowy(){
	ustawienie_ekranu_1();
	ekran.print("Wprowadz PIN:");
}

void poprawne_haslo(){
	ustawienie_ekranu_1();
	ekran.print("OTWARTE");
}

void zle_haslo(){
	ustawienie_ekranu_1_2("Zle haslo","Spr. Ponow.");

	_delay_ms(2000);
	ekran_startowy();
}
void PIN(char * wyswietl){
		ekran.setCursor(0,1);
		ekran.print(wyswietl);
}
void Zmiana_hasla(){
	ustawienie_ekranu_1_2("NOWE HASLO","****");
}
void blokada_drzwi(){
	ustawienie_ekranu_1_2("BLOKADA!","****************");
}