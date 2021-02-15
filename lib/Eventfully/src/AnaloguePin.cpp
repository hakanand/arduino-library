#include <Arduino.h>
#include <math.h>
#include "AnaloguePin.h"

AnaloguePin::AnaloguePin(int pin, int direction) : Pin(pin, direction, PinType::Analogue)
{
    _resistor1 = 0;
    _resistor2 = 1;
}

AnaloguePin::AnaloguePin(int pin, int resistor1, int resistor2) : Pin(pin, INPUT_PULLUP, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
}

AnaloguePin::AnaloguePin(int pin, double measureMax, int resistor1, int resistor2) : Pin(pin, INPUT_PULLUP, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
    _maxVoltage = measureMax;
}

void AnaloguePin::SetVoltage(double voltage)
{
    // Make sure that value is between 0 and maxVoltage (5)
    voltage = min(max(0, voltage), _maxVoltage);
    int value = voltage / _maxVoltage * 1024;
    SetValue(value);
}

float AnaloguePin::GetVoltage()
{
    int value = GetValue();
    return value / 1024 * _maxVoltage;
}

float AnaloguePin::GetResultingVoltage()
{
    int value = GetValue();
    return value / (_resistor1 + _resistor2) * _resistor2 / 1024 * _maxVoltage;
}
