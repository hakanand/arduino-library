#ifndef __BUTTONEVENT_H
#define __BUTTONEVENT_H

#include <arduino.h>
#include "Event.h"
#include "DigitalPin.h"

class ButtonEvent;

typedef int (*ButtonEventFunction)(ButtonEvent *, DigitalPin *);

#define LONGPRESS_MILLIS 1100
#define DOUBLEPRESS_MILLIS 180

class ButtonEvent : public Event
{
    private:
        ButtonEventFunction _onPress;
        ButtonEventFunction _onHold;
        ButtonEventFunction _onDoublePress;
        DigitalPin * _pin;
        bool _lastValue;
        unsigned long _startPressTime = 0;
        unsigned long _previousPressTime = 0;

    public:
        ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress);
        virtual int Loop();
};

#endif
