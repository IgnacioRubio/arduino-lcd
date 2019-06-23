// include the library code:
#include <LiquidCrystal.h>
#include <dht.h>
#include <Wire.h>
#include "RTClib.h"

dht DHT;

// rtc ds3231
RTC_DS3231 rtc;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int dhtPin = 7;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);

  // test rtc is connected + set time first time compiled
  if (! rtc.begin()) {
    Serial.println("There is not module RTC");
    while (1);
  }
  // comment after first compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DHT.read11(dhtPin);
  lcd.clear();

  // TEMP
  displayTemp();

  // HUM
  displayHum();

  delay(5000);

  // DATE + TIME
  lcd.clear();
  DateTime now = rtc.now();

  displayDate(now);
  displayTime(now);

  delay(5000);
}

void displayTemp() {
  lcd.setCursor(0, 0);
  lcd.print("TEM:");

  lcd.setCursor(5, 0);
  lcd.print(DHT.temperature);

  lcd.setCursor(11, 0);
  lcd.print("C");
}

void displayHum() {
  lcd.setCursor(0, 1);
  lcd.print("HUM:");

  lcd.setCursor(5, 1);
  lcd.print(DHT.humidity);

  lcd.setCursor(11, 1);
  lcd.print("%");
}

void displayDate(DateTime t) {
  lcd.setCursor(0, 0);
  lcd.print("DAT:");

  lcd.setCursor(5, 0);
  lcd.print(t.day());

  lcd.setCursor(7, 0);
  lcd.print("/");

  lcd.setCursor(8, 0);
  lcd.print(t.month());

  lcd.setCursor(10, 0);
  lcd.print("/");

  lcd.setCursor(11, 0);
  lcd.print(t.year());
}

void displayTime(DateTime t) {
  lcd.setCursor(0, 1);
  lcd.print("TIM:");

  lcd.setCursor(5, 1);
  lcd.print(t.hour());

  lcd.setCursor(7, 1);
  lcd.print(":");

  lcd.setCursor(8, 1);
  lcd.print(t.minute());

  lcd.setCursor(10, 1);
  lcd.print(":");

  lcd.setCursor(11, 1);
  lcd.print(t.second());
}
