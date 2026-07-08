#include <SevSeg.h>

SevSeg sevseg;

const int RL1    = 46;
const int RL2    = 48;
const int RL3    = 50;
const int GL     = 52;
const int Button = 13;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {12, 9, 8, 6};
  byte segmentPins[] = {11, 7, 4, 2, 1, 10, 5, 3};

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, false, false, false, false);
  sevseg.setBrightness(90);

  pinMode(RL1,    OUTPUT);
  pinMode(RL2,    OUTPUT);
  pinMode(RL3,    OUTPUT);
  pinMode(GL,     OUTPUT);
  pinMode(Button, INPUT_PULLUP);

  randomSeed(analogRead(A0));
}

void loop() {
  // Red LEDs build up
  blinkyDelay(RL1, 1000);
  blinkyDelay(RL2, 1000);
  blinkyDelay(RL3, 1000);

  // Random wait then green on
  displayDelay(random(0, 3001));
  digitalWrite(GL, HIGH);
  long startTime = millis();

  // Wait for button
  while (digitalRead(Button) == HIGH) {
    sevseg.refreshDisplay();
  }

  long reactionTime = millis() - startTime;

  // LEDs off
  digitalWrite(GL,  LOW);
  digitalWrite(RL1, LOW);
  digitalWrite(RL2, LOW);
  digitalWrite(RL3, LOW);

  // Show reaction time for 3 seconds
  sevseg.setNumber(reactionTime, 3);
  long showStart = millis();
  while (millis() - showStart < 3000) {
    sevseg.refreshDisplay();
  }

  delay(500);
}

void blinkyDelay(int pin, int duration) {
  digitalWrite(pin, HIGH);
  long start = millis();
  while (millis() - start < duration) {
    sevseg.refreshDisplay();
  }
}

void displayDelay(long duration) {
  long start = millis();
  while (millis() - start < duration) {
    sevseg.refreshDisplay();
  }
}