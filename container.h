#ifndef CONTAINER_H
#define CONTAINER_H

#include <Arduino.h>
#include <Servo.h>
#include "state.h"

class Container {
  private:
    const State &state_;
    Servo &servo_;

  public:
    Container(const State &state, Servo &servo) : state_(state), servo_(servo) {}

    void update() {
        switch (state_.mode) {
            case INIT:
            case RUNNING:
                close();
                break;
            case DONE:
                open();
                break;
        }
    }

    void open() {
        Serial.println("open container");
        // implement opening of container
    }

    void close() {
        Serial.println("close container");
        // implement closing of container
    }
};


#endif /* CONTAINER_H */

