#include <Arduino.h>
#include <DigitalPin.h>

DigitalPin::DigitalPin(int pin, int direction) : Pin(pin, direction, PinType::Digital)
{
}

void DigitalPin::SetLow()
{
    SetValue(LOW);
}

void DigitalPin::SetHigh()
{
    SetValue(HIGH);
}

bool DigitalPin::ToggleValue()
{
    int value = digitalRead(_pin);

    if (value == HIGH)
    {
        value = LOW;
    }
    else
    {
        value = HIGH;
    }
    
    SetValue(value);
    return value;
}

void DigitalPin::SetValue(int value)
{
    _value = value;
    digitalWrite(_pin, _value);
}

bool DigitalPin::GetValue()
{
    _value = digitalRead(_pin);

    if (_value == LOW)
    {
        return false;
    }
    else
    {
        return true;
    }
}
