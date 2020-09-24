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

    public:
        AnaloguePin(int pin, int direction);

        float GetVoltage();
        void SetVoltage(float voltage);
};

#endif