#include <dht.h>
#include <LiquidCrystal.h>
#include "uRTCLib.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
dht DHT;
uRTCLib rtc(0x68);
int state = 0;
char daysOfTheWeek[7][12] = {"Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"};

#define DHT11_PIN 2
#define BUTTON_PIN 6

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  URTCLIB_WIRE.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void printDate( void )
{
  lcd.print(rtc.day());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.year());
  lcd.print("");
}

void printHour( void )
{
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.println(rtc.second());
}

void printMeasurements( void )
{
  lcd.print(" ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print(DHT.humidity);
  lcd.print("%");
}

void printState0( void )
{
  lcd.setCursor(0,0);
  printDate();
  lcd.print(" ");
  printHour();
  lcd.setCursor(0,1);
  printMeasurements();
}

void printState1( void )
{
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
}

void printState2( void )
{
  lcd.setCursor(0,0);
  lcd.print(rtc.day());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.year());

  lcd.print(" (");
  lcd.print(daysOfTheWeek[rtc.dayOfWeek()-1]); 
  lcd.print(") ");

  lcd.setCursor(0,1);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.println(rtc.second());
}

void printState( void )
{
  switch(state)
  {
    case 0:
    {
      printState0();
      break;
    }
    case 1:
    {
      printState1();
      break;
    }
    case 2:
    {
      printState2();
      break;
    }
    case 3:
    {
      lcd.clear();
      break;
    }
  }
}

void loop(){
  rtc.refresh();
  int chk = DHT.read11(DHT11_PIN);
  printState();
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    lcd.clear();
    state = (state + 1) % 4;
    Serial.println(state);
    delay(250);
  }
}