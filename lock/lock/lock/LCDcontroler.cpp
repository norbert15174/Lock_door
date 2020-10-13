#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Ustawienie adresu ukladu na 0x27

void display_start(){
	  lcd.begin(16,2);
	  lcd.init();
	  lcd.backlight(); // zalaczenie podwietlenia
	  lcd.setCursor(0,0);
	  lcd.print("LCD & I2C");
	  lcd.setCursor(0,1);
	  lcd.print("**********");
}
