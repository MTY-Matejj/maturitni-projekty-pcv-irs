
#include <Arduino.h>
#include <LiquidTWI2.h>

LiquidTWI2 lcd(0x20);

const int button = 9;
const int led13 = 13;
int kostka = 0;
int mem1 = 0;
int mem2 = 0;
int mem3 = 0;
int memory = 1;

bool last_button_state = LOW;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(led13, OUTPUT);
  pinMode(button, INPUT);
  randomSeed(analogRead(A0));
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hod kostkou!");
}

void loop() {

  bool button_state = digitalRead(button);

  if (button_state == HIGH && last_button_state == LOW) {
    if (digitalRead(button) == HIGH) {
      kostka = random(1, 7);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Stav: ");
      lcd.print(kostka);
      Serial.print("Momentalni stav: ");
      Serial.println(kostka);

      switch (memory) {
        case 1:
          mem1 = kostka;
          memory = 2;
          break;
        case 2:
          mem2 = kostka;
          memory = 3;
          break;
        case 3:
          mem3 = kostka;
          memory = 1;
          break;
      }

      lcd.setCursor(0, 1);
      lcd.print("A:");
      lcd.print(mem1);
      lcd.print(" B:");
      lcd.print(mem2);
      lcd.print(" C:");
      lcd.print(mem3);
      Serial.print(" A: ");
      Serial.print(mem1);
      Serial.print(" B: ");
      Serial.print(mem2);
      Serial.print(" C: ");
      Serial.println(mem3);

      for (int i = 0; i < kostka; i++) {
        digitalWrite(led13, HIGH);
        delay(500);
        digitalWrite(led13, LOW);
        delay(500);
      }
    }
  }

  last_button_state = button_state;
}
