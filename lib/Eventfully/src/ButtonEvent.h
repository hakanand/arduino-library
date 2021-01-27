#ifndef __BUTTONEVENT_H
#define __BUTTONEVENT_H

#include <DigitalPin.h>
#include "Event.h"

class ButtonEvent;

typedef int (*ButtonEventFunction)(ButtonEvent *, DigitalPin *);

#define LONGPRESS_MILLIS 1100
#define DOUBLEPRESS_MILLIS 200
#define SKIPPRESS_WITHIN_TIME 30

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
        void * _relatedData;

        ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress, void * relatedData = NULL);
        EventResult * Loop();
};

#endif
