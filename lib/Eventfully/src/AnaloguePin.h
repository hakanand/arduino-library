#ifndef _ANALOGUEPIN_H
#define _ANALOGUEPIN_H

#include <Arduino.h>
#include <Pin.h>

class AnaloguePin : public Pin
{
    private:
        float _maxVoltage;

    protected:
        double _value, _voltageLow, _voltageHigh;
        long _resistor1, _resistor2;

    public:
        AnaloguePin(int pin, int direction);
        AnaloguePin(int pin, int direction, double voltageLow, double voltageHigh);
        AnaloguePin(int pin, unsigned long resistor1, unsigned long resistor2);
        AnaloguePin(int pin, double measureMax, unsigned long resistor1, unsigned long resistor2);
        AnaloguePin(int pin, unsigned long resistor1, unsigned long resistor2, double voltageLow, double voltageHigh);
        AnaloguePin(int pin, double measureMax, unsigned long resistor1, unsigned long resistor2, double voltageLow, double voltageHigh);

        double GetVoltage();
        void SetVoltage(double voltage);
        virtual bool GetDigitalValue();
};

#endif