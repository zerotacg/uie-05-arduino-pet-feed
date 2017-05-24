#include <Arduino.h>
#include <LiquidCrystal.h>
#include "state.h"
#include "countdown.h"
#include "display.h"

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
const byte incButtonPin = 3;
const byte startButtonPin = 2;

State state;
Countdown countdown(state);
Display display(state, lcd);
volatile unsigned long inc_prev, inc_curr;
volatile unsigned long start_prev, start_curr;

void setup() {
  Serial.begin(19200);
  lcd.begin(16, 2);
  lcd.print(" UIE Pet-Feeder");

  attachInterrupt(digitalPinToInterrupt(incButtonPin), inc, RISING);
  attachInterrupt(digitalPinToInterrupt(startButtonPin), start, RISING);
}

void loop() {
  update();
  Serial.println(state.timer);
  Serial.println(state.mode);
}

void update() {
  countdown.update();
  display.update();
}

void inc() {
  inc_curr = micros();

  if (inc_curr > inc_prev) {
    inc_prev = inc_curr + 3000;
    countdown.inc();
  }
}

void start() {
  start_curr = micros();

  if (start_curr > start_prev) {
    start_prev = start_curr + 3000;
    countdown.start();
  }
}

