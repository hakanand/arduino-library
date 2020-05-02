#include "Event.h"

Event::Event(Pin * pin)
{
    // 0 for runEvery = Do Not Run (Inherited event)
    _pin = pin;
    Init(NULL, 0, 0, pin);
}

Event::Event(char * name) : ListItem(name)
{
    // 0 for runEvery = Do Not Run (Inherited event)
    Init(NULL, 0, 0, NULL);
}

Event::Event(EventFunction func, Pin * pin)
{
    Init(func, 0, 1, pin);
    Enable();
}

Event::Event(EventFunction func, int runEveryLaps, Pin * pin)
{
    Init(func, 0, runEveryLaps, pin);
    Enable();
}

Event::Event(EventFunction func, unsigned long runEveryMilliseconds, Pin * pin)
{
    Init(func, runEveryMilliseconds, 1, pin);
    Enable();
}

Event::Event(char * name, EventFunction func, Pin * pin) : ListItem(name)
{
    Init(func, 0, 1, pin);
    Enable();
}

Event::Event(char * name, EventFunction func, int runEveryLaps, Pin * pin) : ListItem(name)
{
    Init(func, 0, runEveryLaps, pin);
    Enable();
}

Event::Event(char * name, EventFunction func, unsigned long runEveryMilliseconds, Pin * pin) : ListItem(name)
{
    Init(func, runEveryMilliseconds, 1, pin);
    Enable();
}

void Event::Init(EventFunction func, unsigned long runEveryMilliseconds, int runEveryLaps, Pin * relatedPin)
{
    _function = func;
    _runEveryLaps = max(runEveryLaps, 1);
    _runEveryMilliseconds = max(runEveryMilliseconds, 0);
    _pin = relatedPin; 
}

EventResult * Event::Loop() {
    unsigned long now = millis();
    _result._hasExecuted = false;

    if(_enabled && _function != NULL && _lapCounter % _runEveryLaps == 0 && (now - _lastExecuted > _runEveryMilliseconds || now < _lastExecuted))
    {
        _lastExecuted = now;
        int returnValue = _function(this, _pin);

        if (returnValue > 0)
        {
            _result._hasExecuted = true;
        }
    }

    ++_lapCounter;

    return &_result;
}
