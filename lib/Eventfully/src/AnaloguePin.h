#ifndef _ANALOGUEPIN_H
#define _ANALOGUEPIN_H

#include <Arduino.h>
#include <Pin.h>

class AnaloguePin : public Pin
{
    private:
        float maxVoltage = 5.0;

    protected:
        double value;
        long res1, res2;

    public:
        AnaloguePin(int pin, int direction);
        AnaloguePin(int pin, int res1, int res2);
        AnaloguePin(int pin, double measureMax, int resistor1, int resistor2);

        float GetVoltage();
        float GetResultingVoltage();
        void SetVoltage(double voltage);
};

#endif