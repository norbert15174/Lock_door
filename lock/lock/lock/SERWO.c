#include <avr/io.h>
#include "Control.h"
void lock(int x)
{
	DDRB = (1<<PORTB1);
	TCNT1 = 0;
	ICR1 = 4998;
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10) | (1<<CS11);
	OCR1A = x;
}
/*
TCNT1 - Counter1
ICR1 = 4998 - defines Counter1 TOP value (Input Capture Register 1)
TCCR1A - Counter1 Control Register A 
	WGM11 - FAST PWM (Waveform Generation Mode)
	COM1A1 - clear OC1A on Compare match (Compare Output Mode)
TCCR1B - Counter1 Control Register B
	WGM13, WGM12 - FAST PWM (Waveform Generation Mode)
	CS10, CS11 - clk/64 prescaler (Clock select)
OCR1A - compared with TCNT1 value (Output Compare Register 1 A) 	


Dzia³a tylko na porcie B1(OCR1A) !!!
Ustawiæ go jako wyjœcie !!!


OCR1A=190 ~ +90 stopni - zamek  zamkniety
OCR1A=445 ~ 0 stopni - zamek otwarty
OCR1A=700 ~ +90 stopni
*/