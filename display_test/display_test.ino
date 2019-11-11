/*

*/

#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t check[8] = {
	0b00000,
	0b00001,
	0b00011,
	0b10110,
	0b11100,
	0b01000,
	0b00000,
	0b00000
};


String stringToPrint = "hello world";

void setup()
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.createChar(0, check);
	Serial.begin(9600);
}

void loop()
{
	if (Serial.available()) {
		stringToPrint = Serial.readString();
		Serial.println("Retrieved new value from serial");
	}

	printDisplay(stringToPrint);
}

void printDisplay(String displayText)
{
	Serial.print("Printing value: ");
	Serial.println(displayText);
	lcd.clear();

	// set the cursor to (0,0):
	lcd.setCursor(0, 0);

	// print from 0 to 9:
	for (int charIndex = 0; charIndex < displayText.length(); charIndex++)
	{
		lcd.print(displayText.charAt(charIndex));
		delay(500);
	}
	lcd.write(byte(0));
	delay(500);

	// set the cursor to (16,1):
	lcd.setCursor(16, 1);
	// set the display to automatically scroll:
	lcd.autoscroll();
	// print from 0 to 9:
	for (int charIndex = 0; charIndex < displayText.length(); charIndex++)
	{
		lcd.print(displayText.charAt(charIndex));
		delay(500);
	}
	lcd.write(byte(0));
	delay(500);

	// turn off automatic scrolling
	lcd.noAutoscroll();

	// clear screen for the next loop:
	lcd.clear();
}
