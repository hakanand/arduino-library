#ifndef _ANALOGUEPIN_H
#define _ANALOGUEPIN_H

#include <Arduino.h>
#include <Pin.h>

class AnaloguePin : public Pin
{
    private:
        float _maxVoltage = 5.0;

    protected:
        double _value;
        long _resistor1, _resistor2;

    public:
        AnaloguePin(int pin, int direction);
        AnaloguePin(int pin, int res1, int res2);
        AnaloguePin(int pin, double measureMax, int resistor1, int resistor2);

        double GetVoltage();
        void SetVoltage(double voltage);
};

#endif