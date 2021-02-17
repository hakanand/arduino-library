#ifndef __PINEVENT_H
#define __PINEVENT_H

#include <DigitalPin.h>
#include <AnaloguePin.h>
#include <Event.h>

enum EventType
{
    InRange,
    OutOfRange,
    OnHigh,
    OnLow
};

class PinEvent;

typedef int (*PinEventFunction)(PinEvent *, Pin *, EventType);

class PinEvent : public Event
{
    private:
        PinEventFunction _onEvent = NULL;
        PinType _pinType;
        EventType _curSelected;
        int _lowSetting, _highSetting;
        
    public:
        PinEvent(Pin * pin, PinEventFunction digitalValueChanged);
        PinEvent(Pin * pin, PinEventFunction analogueRangeBoundsAltered, int low, int high);
        ~PinEvent();

        virtual EventResult Loop();
};

#endif