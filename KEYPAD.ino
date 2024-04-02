#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 3;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};
byte rowPins[ROWS] = {7, 6, 5};
byte colPins[COLS] = {4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

#define password_length 5

char data[password_length];
char passcode[password_length] = "1234";

byte count = 0, tries = 3, i;
char customKey;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int greenPin = 53;
int redPin = 52;
int buzzerPin = 50;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  customKey = customKeypad.getKey();
  if (customKey) {
    data[count] = customKey;
    lcd.setCursor(count, 1);
    lcd.print(data[count]);
    count++;
  }
  if (count == password_length - 1) {
    lcd.clear();
    if (!strcmp(data, passcode)) {
      lcd.print("    Correct");
      lcd.setCursor(0,1);
      lcd.print("    Password");
      tries = 3;
      digitalWrite(greenPin, HIGH);
      delay(2500);
      digitalWrite(greenPin, LOW);
    }
    else {
      lcd.print("    Incorrect");
      lcd.setCursor(0,1);
      lcd.print("    Password");
      tries = tries - 1;
      digitalWrite(redPin, HIGH);
      delay(2500);
      digitalWrite(redPin, LOW);
    }
    lcd.clear();
    delay(100);
    if(tries == 0)
    {
      lcd.print("Maximum attempts");
      lcd.setCursor(0,1);
      lcd.print("reached ");
      digitalWrite(redPin, HIGH);
      for(i = 10; i > 0; i--)
      {
        lcd.setCursor(8,1);
        if(i == 10)
        {
          lcd.print(i);  
        }
        else
        {
          lcd.print("0");
          lcd.print(i);
        }
        if(i % 2 == 0)
        {
          digitalWrite(buzzerPin, HIGH);
        }
        else
        {
          digitalWrite(buzzerPin, LOW);
        }
        delay(1000);
      }
      digitalWrite(redPin, LOW);
    }
    lcd.clear();
    clearData();
  }
}

void clearData() {
  while (count != 0) {
    data[count--] = 0;
  }
  return;
}
