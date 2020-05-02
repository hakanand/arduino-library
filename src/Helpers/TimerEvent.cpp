#include "TimerEvent.h"

TimerEvent::TimerEvent(unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData)
{
    _relatedData = relatedData;
    _removeAfterUse = removeAfterUse;
    _onTimer = func;
    _pin = pin;
    _arrayItemCount = 1;

    _delays = (unsigned long *)malloc(sizeof(unsigned long));
    _delays[0] = delay;

    Enable();
}

TimerEvent::TimerEvent(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData)
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

    char message[128];
    sprintf(message, "Item Count is %i", _arrayItemCount);
    Serial.println(message);
    
    _delays = (unsigned long *)malloc(sizeof(unsigned long) * _arrayItemCount);
    memcpy(_delays, delay, sizeof(unsigned long) * _arrayItemCount);

    Enable();
}

TimerEvent::~TimerEvent()
{
    if(_delays != NULL)
    {
        free(_delays);
        _delays = NULL;
    }
}

int TimerEvent::Loop()
{
    unsigned long now = millis();

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
            _timerOrder = 0;
        }

        // char message[128];
        // sprintf(message, "Timer delay item is %i for %lu ms", _timerOrder, _delays[_timerOrder]);
        // Serial.println(message);
    }

    return 0;
}