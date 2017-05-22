#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

enum Mode {
    INIT,
    RUNNING,
    DONE
};

struct State {
    State(): offset(0), timer(0), mode(INIT) {}
    unsigned long offset;
    unsigned long timer;
    Mode mode;
};

#endif /* STATE_H */

