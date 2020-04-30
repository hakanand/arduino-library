#ifndef __BUTTONEVENT_H
#define __BUTTONEVENT_H

#include <arduino.h>
#include "Event.h"
#include "DigitalPin.h"

#define LONGPRESS_MILLIS 3000
#define DOUBLEPRESS_MILLIS 500

class ButtonEvent : Event
{
    private:
        EventFunction _onPress;
        EventFunction _onHold;
        EventFunction _onDoublePress;
        DigitalPin * _pin;
        bool _lastValue;
        unsigned long _startPressTime = 0;
        unsigned long _previousPressTime = 0;

    public:
        ButtonEvent(DigitalPin * pin, EventFunction onPress, EventFunction onHold, EventFunction onDoublePress);
        virtual int Loop();
};

#endif
