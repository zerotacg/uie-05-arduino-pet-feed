#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "state.h"

class Display {
  private:
    const State &state_;
    LiquidCrystal &lcd_;

  public:
    Display(const State &state, LiquidCrystal &lcd) : state_(state), lcd_(lcd) {}

    void update() {
        switch (state_.mode) {
            case INIT:
                showTime();
                break;
            case RUNNING:
                showCountdown();
                break;
            case DONE:
                showDone();
                break;
        }
    }

    void showCountdown() {
        unsigned long countdown = 0;
        unsigned long current = millis();
        if (state_.offset > current) {
            countdown = state_.offset - current;
        }

        show(countdown);
    }

    void show(unsigned long time) {
        unsigned long seconds = (time / 1000) % 60;
        unsigned long minutes = (time / 60000) % 60;
        lcd_.setCursor(9, 1);
        if ( minutes < 10 ) {
          lcd_.print(0);
        }
        lcd_.print(minutes);
        lcd_.print(":");
        if ( seconds < 10 ) {
          lcd_.print(0);
        }
        lcd_.print(seconds);
    }

    void showTime() {
        lcd_.setCursor(0, 1);
        lcd_.print("food in:");
        show(state_.timer);
    }

    void showDone() {
        lcd_.setCursor(0, 0);
        lcd_.print("(o.o)");
                  //0123456789012345
        lcd_.setCursor(0, 1);
        lcd_.print("(\")\") eat!      ");
    }
};


#endif /* DISPLAY_H */

