#include <Pin.h>

Pin::Pin(int pin, int direction, PinType type)
{
    _pin = pin;
    _direction = direction;
    _pinType = type;

    pinMode(_pin, _direction);
}


void Pin::SetValue(int value)
{
    _value = value;

    if (_pinType == PinType::Digital)
    {
        digitalWrite(_pin, _value);
    }
    else if (_pinType == PinType::Analogue)
    {
        analogWrite(_pin, _value);
    }
}

int Pin::GetValue()
{
    int returnValue = -1;

    if (_pinType == PinType::Digital)
    {
        returnValue = digitalRead(_pin);
    }
    else if (_pinType == PinType::Analogue)
    {
        returnValue = analogRead(_pin);
    }

    return returnValue;
}
