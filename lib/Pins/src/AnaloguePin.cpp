#include <Arduino.h>
#include <math.h>
#include "AnaloguePin.h"

AnaloguePin::AnaloguePin(int pin, int direction) : Pin(pin, direction, PinType::Analogue)
{
}

void AnaloguePin::SetVoltage(float voltage)
{
    // Make sure that value is between 0 and 5
    voltage = min(max(0, voltage), 5.0);

    int value = voltage / 5.0 * 1024;
    SetValue(value);
}

float AnaloguePin::GetVoltage()
{
    int value = GetValue();
    return value / 1024 * 5.0;
}
