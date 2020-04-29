#ifndef _DIGITALPIN_H
#define _DIGITALPIN_H

#include <Arduino.h>
#include <Pin.h>

class DigitalPin : Pin
{
    private:

    protected:

    public:
        DigitalPin(int pin, int direction);

        void SetLow();
        void SetHigh();
        bool ToggleValue();
        bool GetValue();
        void SetValue(int value);
};

#endif