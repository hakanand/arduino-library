#include <Arduino.h>
#include <math.h>
#include "AnaloguePin.h"

AnaloguePin::AnaloguePin(int pin, int direction) : Pin(pin, direction, PinType::Analogue)
{
}

void AnaloguePin::SetVoltage(float voltage)
{
    // Make sure that value is between 0 and maxVoltage (5)
    voltage = min(max(0, voltage), maxVoltage);
    int value = voltage / maxVoltage * 1024;
    SetValue(value);
}

float AnaloguePin::GetVoltage()
{
    int value = GetValue();
    return value / 1024 * maxVoltage;
}
