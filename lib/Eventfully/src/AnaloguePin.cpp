#include <Arduino.h>
#include <math.h>
#include "AnaloguePin.h"

AnaloguePin::AnaloguePin(int pin, int direction) : Pin(pin, direction, PinType::Analogue)
{
    _resistor1 = 0;
    _resistor2 = 1;
    _maxVoltage = 5.0;
    _voltageLow = 2.5;
    _voltageHigh = 5.0;
}

AnaloguePin::AnaloguePin(int pin, unsigned long resistor1, unsigned long resistor2) : Pin(pin, INPUT, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
    _maxVoltage = 5.0;
    _voltageLow = 2.5;
    _voltageHigh = 5.0;
}

AnaloguePin::AnaloguePin(int pin, double measureMax, unsigned long resistor1, unsigned long resistor2) : Pin(pin, INPUT, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
    _maxVoltage = measureMax;
    _voltageLow = measureMax / 2;
    _voltageHigh = measureMax;
}

AnaloguePin::AnaloguePin(int pin, unsigned long resistor1, unsigned long resistor2, double voltageLow, double voltageHigh) : Pin(pin, INPUT, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
    _maxVoltage = 5.0;
    _voltageLow = voltageLow;
    _voltageHigh = voltageHigh;
}

AnaloguePin::AnaloguePin(int pin, double measureMax, unsigned long resistor1, unsigned long resistor2, double voltageLow, double voltageHigh) : Pin(pin, INPUT, PinType::Analogue)
{
    _resistor1 = resistor1;
    _resistor2 = resistor2;
    _maxVoltage = measureMax;
    _voltageLow = voltageLow;
    _voltageHigh = voltageHigh;
}

void AnaloguePin::SetVoltage(double voltage)
{
    // Make sure that value is between 0 and maxVoltage (5)
    voltage = min(max(0, voltage), _maxVoltage);
    int value = voltage / _maxVoltage * 1024;
    SetValue(value);
}

double AnaloguePin::GetVoltage()
{
    int value = Pin::GetValue();
    char output[32];
    
    double result = value / (_resistor1 + _resistor2) * _resistor2 / 1024 * _maxVoltage;
    return result;
}

bool AnaloguePin::GetDigitalValue()
{
    double voltage = GetVoltage();
    return voltage >= _voltageLow && voltage <= _voltageHigh;
}