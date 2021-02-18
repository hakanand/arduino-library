#ifndef _PIN_H
#define _PIN_H

#include <Arduino.h>
#include <ListItem.h>
#include <StateSource.h>

enum PinType
{
    Digital,
    Analogue
};

class Pin : ListItem, public StateSource
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
        
        // From StateSource
        virtual bool GetDigitalValue();
		virtual const char * GetType() { return "Pin"; };
};

#endif