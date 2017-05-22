#include <Arduino.h>
#include <LiquidCrystal.h>
#include "state.h"
#include "countdown.h"
#include "display.h"

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
const byte incButtonPin = 3;
const byte startButtonPin = 2;

State state;
volatile Countdown countdown(state);
Display display(state, lcd);
volatile unsigned long inc_prev, inc_curr;
volatile unsigned long start_prev, start_curr;

void setup() {
  lcd.begin(16, 2);
  lcd.print(" UIE Pet-Feeder");

  attachInterrupt(digitalPinToInterrupt(incButtonPin), inc, RISING);
  attachInterrupt(digitalPinToInterrupt(startButtonPin), start, RISING);
}

void loop() {
  update();
}

void update() {
  countdown.update();
  display.update();
}

void inc() {
  inc_curr = micros();

  if (inc_curr > inc_prev) {
    inc_prev = inc_curr + 2000;
    countdown.inc();
  }
}

void start() {
  start_curr = micros();

  if (start_curr > start_prev) {
    start_prev = start_curr + 2000;
    countdown.start();
  }
}

