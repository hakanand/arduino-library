#include "Event.h"

Event::Event(Pin * pin)
{
    _pin = pin;
    Init(NULL, 0, 0, pin);
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
    _runEveryMilliseconds = runEveryMilliseconds;
    _pin = relatedPin; 
}

int Event::Loop() {
    int returnValue = 0; // Not executed
    unsigned long now = millis();

    if(_enabled && _function != NULL && _lapCounter % _runEveryLaps == 0 && (now - _lastExecuted > _runEveryMilliseconds || now < _lastExecuted))
    {
        _lastExecuted = now;
        returnValue = _function(this, _pin);
    }

    ++_lapCounter;

    return returnValue;
}

bool Event::IsEnabled()
{
    return _enabled;
}
