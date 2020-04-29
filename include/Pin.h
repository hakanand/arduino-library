#ifndef _PIN_H
#define _PIN_H

#include <Arduino.h>
#include "Helpers\ListItem.h"

enum PinType
{
    Digital,
    Analogue
};

class Pin : ListItem
{
    protected:
        int _pin;
        int _direction;
        int _value;
        PinType _pinType;

    public:
        Pin(int pin, int direction, PinType type);
        void SetValue(int value);
        int GetValue();
};

#endif