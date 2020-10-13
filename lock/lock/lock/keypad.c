#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"
#include "Control.h"
#include <string.h>
const char KOD_BEZPIECZENSTWA[] = "1234567890123456";
const int close = 190; 
const int open = 445;
void zerowanie_pinu(char *p,int ilosc){
	for(int i=0;i<ilosc;i++){
		p[i] = NULL;
	}
}
int usun_cyfre(char *p,int ilosc){
	if(ilosc!=0){		
			p[ilosc] = NULL;
			ilosc--;
			PIN("                ");
			PIN(p);
			return ilosc;
		}else{
			p[0] = NULL;
			PIN("                ");
			PIN(p);
			lock(close);  // zamyka zamek gdy wcisnê *
			ekran_startowy();
			return 0;
	}
	
}
int dobry_PIN(char *p,int ilosc,int blokada_ekranu){
	zerowanie_pinu(p,ilosc);
	lock(open);
	_delay_ms(1000);
	ilosc=0;
	blokada_ekranu = 0;
	poprawne_haslo();
	return ilosc, blokada_ekranu;
}
int zly_pin(int blokada_ekranu,int ilosc,char *p){
	zerowanie_pinu(p,ilosc);
	ilosc=0;
	DDRB = 1;
	PORTB = 1; // buzz on !
	_delay_ms(50);
	PORTB = 0; // buzz off
	DDRB = 0;
	zle_haslo();
    lock(close);
	blokada_ekranu++;
	return ilosc, blokada_ekranu;
	
}
int sprawdzenie_kodu(char *p,int blokada_ekranu, int ilosc){
		if(strcmp(p,KOD_BEZPIECZENSTWA)==0){
				DDRB = 0;
				PORTB = 0; // long buzz off 
				ekran_startowy();
				zerowanie_pinu(p,ilosc);
				blokada_ekranu = 0;
				return 0;
			}else{
				DDRB = 1;
				PORTB = 1; // long buzz !!!
				zerowanie_pinu(p,ilosc);
				blokada_drzwi();
				return 0;
		}
}
int dodaj_numer(char *p,int ilosc,char *nr){

	strcat(p,nr);
	ilosc++;
	PIN(p);
	return ilosc;
}
char key()
{
	
	DDRD = 0xFF; // wyjœcie
	PORTD = 0x00;
	
	DDRC = 0x00;  // wejœcie
	PORTC = 0xFF; // pullup (tylko starsza po³ówka)
	char p[16] = "";
	int ilosc = 0;
	char PIN_DOOR[16] = "9174";
	int PIN_zmiana = 0;
	int blokada_ekranu = 0;
	while(1){
		
		
		
		//WIERSZ 0
		PORTD=0b01111111;
		if(!(PINC & (1<<PINC0))){
				ilosc = dodaj_numer(p,ilosc,"1");
			}else if(!(PINC & (1<<PINC1))){
				ilosc = dodaj_numer(p,ilosc,"0");
			}else if(!(PINC & (1<<PINC2))){
			
			//Sprawdzenie ile razy byl wpisany bledny PIN
			if(blokada_ekranu!=1){
				//SPR pinu
				if(strcmp(p,PIN_DOOR) == 0){
					
					ilosc,blokada_ekranu = dobry_PIN(p,ilosc,blokada_ekranu);
					
					}else if(strcmp(p,KOD_BEZPIECZENSTWA)==0){
					//zmiana pinu
						PIN_zmiana = 1;
						zerowanie_pinu(p,ilosc);
						Zmiana_hasla();
					}else if(PIN_zmiana == 1){
					//akceptacja zmiany pinu
						ekran_startowy();
						PIN_zmiana = 0;
						strcpy(PIN_DOOR,p);
						zerowanie_pinu(p,ilosc);
					
					}else{
						ilosc,blokada_ekranu = zly_pin(blokada_ekranu,ilosc,p);
					
					}
				}else{
					//Blokada,odblokowywanie
					sprawdzenie_kodu(p,blokada_ekranu,ilosc);
				
			}
		}
		//WIERSZ 1
		PORTD=0b10111111;
		if(!(PINC & (1<<PINC0))){
			ilosc = usun_cyfre(p,ilosc);
		}else if(!(PINC & (1<<PINC1))){
				ilosc = dodaj_numer(p,ilosc,"8");
		}else if(!(PINC & (1<<PINC2))){
				ilosc = dodaj_numer(p,ilosc,"9");
		}
		//WIERSZ2
		PORTD=0b11011111;
		if(!(PINC & (1<<PINC0))){
				ilosc = dodaj_numer(p,ilosc,"7");
			}else if(!(PINC & (1<<PINC1))){
				ilosc = dodaj_numer(p,ilosc,"5");;
			}else if(!(PINC & (1<<PINC2))){
				ilosc = dodaj_numer(p,ilosc,"6");
		}
		//WIERSZ3
		PORTD=0b11101111;
		if(!(PINC & (1<<PINC0))){
				ilosc = dodaj_numer(p,ilosc,"4");
			}else if(!(PINC & (1<<PINC1))){
				ilosc = dodaj_numer(p,ilosc,"2");
			}else if(!(PINC & (1<<PINC2))){
				ilosc = dodaj_numer(p,ilosc,"3");
		}
		_delay_ms(300);
	}
}
