#include "Event.h"

Event::Event()
{
}

Event::Event(EventFunction func)
{
    _function = func;
    Enable();
}

Event::Event(EventFunction func, int runEveryLaps)
{
    _function = func;
    _runEveryLaps = runEveryLaps;
    Enable();
}

Event::Event(EventFunction func, unsigned long runEveryMilliseconds)
{
    _function = func;
    _runEveryMilliseconds = runEveryMilliseconds;
    Enable();
}

Event::Event(char * name, EventFunction func) : ListItem(name)
{
    _function = func;
    Enable();
}

Event::Event(char * name, EventFunction func, int runEveryLaps) : ListItem(name)
{
    _function = func;
    _runEveryLaps = runEveryLaps;
    Enable();
}

Event::Event(char * name, EventFunction func, unsigned long runEveryMilliseconds) : ListItem(name)
{
    _function = func;
    _runEveryMilliseconds = runEveryMilliseconds;
    Enable();
}

int Event::Loop() {
    int returnValue = 0; // Not executed
    unsigned long now = millis();

    if(_enabled && _function != NULL && _lapCounter % _runEveryLaps == 0 && (now - _lastExecuted > _runEveryMilliseconds || now < _lastExecuted))
    {
        _lastExecuted = now;
        returnValue = _function();
    }

    ++_lapCounter;

    return returnValue;
}

bool Event::IsEnabled()
{
    return _enabled;
}

int Event::SampleEventFunction()
{
    Serial.println("SampleEventFunction()");

    return 0;
}
