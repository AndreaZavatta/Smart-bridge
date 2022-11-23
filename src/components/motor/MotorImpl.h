#ifndef __MOTORIMPL__
#define __MOTORIMPL__

#include <Servo.h>

class Motor {
    public:
        Motor(uint8_t pin);
        void autoMove(int angle);
        void pirMove(int pirValue);
    private:
        Servo servo;
        int pin;
};

#endif