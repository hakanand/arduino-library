#ifndef __EVENT_H
#define __EVENT_H

#include <Pin.h>
#include "ListItem.h"

class Event;

typedef int (*EventFunction)(Event *, Pin *);

class Event : public ListItem
{
    private:
        unsigned int _lapCounter = 0;
        int _runEveryLaps = 1;
        unsigned long _lastExecuted;
        unsigned long _runEveryMilliseconds = 0;

        void Init(EventFunction func, unsigned long runEveryMilliseconds, int runEveryLaps, Pin * relatedPin);

    protected:
        bool _enabled;
        Pin * _pin;
        EventFunction _function = NULL;

        void Enable() { _enabled = true; }
        void Disable() { _enabled = false; } 

    public:
        Event(Pin * pin = NULL);
        Event(EventFunction func, Pin * pin = NULL);
        Event(EventFunction func, int runEveryLaps, Pin * pin = NULL);
        Event(EventFunction func, unsigned long runEveryMilliseconds, Pin * pin = NULL);
        Event(char * name, EventFunction func, Pin * pin = NULL);
        Event(char * name, EventFunction func, int runEveryLaps, Pin * pin = NULL);
        Event(char * name, EventFunction func, unsigned long runEveryMilliseconds, Pin * pin = NULL);

        virtual int Loop();
        bool IsEnabled();
};

#endif