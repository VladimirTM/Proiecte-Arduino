#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define RST_PIN 5          
#define SS_PIN 53         

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte accessUID[4] = {0xDA, 0xC8, 0x7D, 0x91};
int greenPin = 2;
int redPin = 3;
int buzzerPin = 4;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
	Serial.begin(9600);
	while (!Serial);
	SPI.begin();
	mfrc522.PCD_Init();
	delay(4);
  lcd.begin(16, 2);
}

void loop() {
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	if(mfrc522.uid.uidByte[0] == accessUID[0] && mfrc522.uid.uidByte[1] == accessUID[1] && mfrc522.uid.uidByte[2] == accessUID[2] && mfrc522.uid.uidByte[3] == accessUID[3])
  {
    lcd.setCursor(0, 0);
    lcd.print("Bine ai venit");
    lcd.setCursor(0, 1);
    lcd.print("acasa Vladimir !");
    digitalWrite(greenPin, HIGH);
    delay(2500);
    digitalWrite(greenPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Intrus detectat!");
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(5000);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("                ");
  }
  
  mfrc522.PICC_HaltA();
}
