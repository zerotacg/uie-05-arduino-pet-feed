#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <Arduino.h>
#include "state.h"

class Countdown {
  private:
    const unsigned long step_ = 15000;
    State& state_;
  
  public:
    Countdown(State &state) : state_(state) {}
  
    void inc() {
      state_.timer += step_;
    }

    void start() {
      state_.mode = RUNNING;
      state_.offset = state_.timer + millis();
    }

    void update() {
      if ( state_.mode == RUNNING && millis() > state_.offset) {
        state_.mode = DONE;
      }
    }
};


#endif /* COUNTDOWN_H */

