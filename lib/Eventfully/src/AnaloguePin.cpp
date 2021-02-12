#include <Arduino.h>
#include <math.h>
#include "AnaloguePin.h"

AnaloguePin::AnaloguePin(int pin, int direction) : Pin(pin, direction, PinType::Analogue)
{
    res1 = 0;
    res2 = 1;
}

AnaloguePin::AnaloguePin(int pin, int resistor1, int resistor2) : Pin(pin, INPUT, PinType::Analogue)
{
    res1 = resistor1;
    res2 = resistor2;
}

AnaloguePin::AnaloguePin(int pin, double measureMax, int resistor1, int resistor2) : Pin(pin, INPUT, PinType::Analogue)
{
    res1 = resistor1;
    res2 = resistor2;
    maxVoltage = measureMax;
}

void AnaloguePin::SetVoltage(double voltage)
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

float AnaloguePin::GetResultingVoltage()
{
    int value = GetValue();
    return value / (res1 + res2) * res2 / 1024 * maxVoltage;
}
