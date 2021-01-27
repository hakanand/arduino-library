#ifndef _ANALOGUEPIN_H
#define _ANALOGUEPIN_H

#include <Arduino.h>
#include "Pin.h"

class AnaloguePin : public Pin
{
    private:
        const float maxVoltage = 5.0;

    protected:
        float value;
        long res1, res2;

    public:
        AnaloguePin(int pin, int direction);
        AnaloguePin(int pin, int res1, int res2);

        float GetVoltage();
        float GetResultingVoltage();
        void SetVoltage(float voltage);
};

#endif