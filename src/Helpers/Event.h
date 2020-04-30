#ifndef __EVENT_H
#define __EVENT_H

#include <arduino.h>
#include "ListItem.h"

typedef int (*EventFunction)();

class Event : public ListItem
{
    private:
        unsigned int _lapCounter = 0;
        int _runEveryLaps = 1;
        unsigned long _lastExecuted;
        unsigned long _runEveryMilliseconds = 0;

    protected:
        bool _enabled;
        EventFunction _function = NULL;
        void Enable() { _enabled = true; }
        void Disable() { _enabled = false; } 

    public:
        Event();
        Event(EventFunction func);
        Event(EventFunction func, int runEveryLaps);
        Event(EventFunction func, unsigned long runEveryMilliseconds);
        Event(char * name, EventFunction func);
        Event(char * name, EventFunction func, int runEveryLaps);
        Event(char * name, EventFunction func, unsigned long runEveryMilliseconds);

        virtual int Loop();
        bool IsEnabled();
        int SampleEventFunction();
};

#endif