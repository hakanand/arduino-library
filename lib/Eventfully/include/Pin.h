#ifndef _PIN_H
#define _PIN_H

#include <Arduino.h>
#include <ListItem.h>

enum PinType
{
    Digital,
    Analogue
};

class Pin : public ListItem
{
    protected:
        int _pin;
        int _direction;
        int _value;
        PinType _pinType;
        bool _iverted = false;

    public:
        Pin(int pin, int direction, PinType type);
        void SetValue(int value);
        int GetValue();
        
        // From StateSource
        virtual bool GetDigitalValue();
		virtual const char * GetType() { return "Pin"; };
};

#endif