#include <TimerEvent.h>

TimerEvent::TimerEvent(unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData)
{
    unsigned long * delays = (unsigned long *)malloc(sizeof(unsigned long) * 2);
    delays[0] = delay;
    delays[1] = 0;

    Init(delays, removeAfterUse, func, pin, relatedData);
}

TimerEvent::TimerEvent(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData)
{
    Init(delay, removeAfterUse, func, pin, relatedData);
}

TimerEvent::TimerEvent(char * name, unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData) : Event(name)
{
    unsigned long * delays = (unsigned long *)malloc(sizeof(unsigned long) * 2);
    delays[0] = delay;
    delays[1] = 0;

    Init(delays, removeAfterUse, func, pin, relatedData);
}

TimerEvent::TimerEvent(char * name, unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData) : Event(name)
{
    Init(delay, removeAfterUse, func, pin, relatedData);
}

TimerEvent::~TimerEvent()
{
    if(_delays != NULL)
    {
        free(_delays);
        _delays = NULL;
    }
}

EventResult TimerEvent::Loop()
{
    unsigned long now = millis();
    EventResult result;

    if (now - _lastOperation >= _delays[_timerOrder])
    {
        
        if (_onTimer != NULL && _enabled == true)
        {
            _onTimer(this, _pin, _timerOrder);
        }

         _timerOrder++;
        _lastOperation = now;

        if(_timerOrder >= _arrayItemCount)
        {
            result._hasExecuted = true;
            _timerOrder = 0;
        }

        // char message[128];
        // sprintf(message, "Timer delay item is %i for %lu ms", _timerOrder, _delays[_timerOrder]);
        // Serial.println(message);
    }

    return result;
}

void TimerEvent::Init(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData)
{
    _relatedData = relatedData;
    _removeAfterUse = removeAfterUse;
    _onTimer = func;
    _pin = pin;
    
    // Calculate how many items that are present.
    for(int i = 0; i < 100; ++i)
    {
        if (delay[i] == 0)
        {
            break;
        }
        _arrayItemCount++;
    }

    _delays = (unsigned long *)malloc(sizeof(unsigned long) * _arrayItemCount);
    memcpy(_delays, delay, sizeof(unsigned long) * _arrayItemCount);

    _lastOperation = millis();
    Enable();
}