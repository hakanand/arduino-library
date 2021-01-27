#ifndef __PINEVENT_H
#define __PINEVENT_H

#include <Pin.h>
#include "Event.h"

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

    public:
        PinEvent(Pin * pin, PinEventFunction digitalValueChanged);
        PinEvent(Pin * pin, PinEventFunction analogueRangeBoundsAltered);
        ~PinEvent();
};

#endif