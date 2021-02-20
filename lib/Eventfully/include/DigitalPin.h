#ifndef _DIGITALPIN_H
#define _DIGITALPIN_H

#include <Arduino.h>
#include <Pin.h>

class DigitalPin : public Pin
{
    private:

    protected:

    public:
        DigitalPin(int pin, int direction);
		virtual const char * GetType() { return "DigitalPin"; };

        void SetLow();
        void SetHigh();
        bool ToggleValue();
        bool GetValue();
        void SetValue(int value);
};

#endif