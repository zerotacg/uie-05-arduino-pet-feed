#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "state.h"
#include "container.h"
#include "countdown.h"
#include "display.h"

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
Servo servo;
const byte incButtonPin = 3;
const byte startButtonPin = 2;
const byte servoPin = 10;

State state;
Countdown countdown(state);
Display display(state, lcd);
Container container(state, servo);
volatile unsigned long inc_prev, inc_curr;
volatile unsigned long start_prev, start_curr;

void setup() {
  Serial.begin(19200);
  lcd.begin(16, 2);
  lcd.print(" UIE Pet-Feeder");
  servo.attach(servoPin);

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
  container.update();
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

