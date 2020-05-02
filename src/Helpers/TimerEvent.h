#ifndef __TIMEREVENT_H
#define __TIMEREVENT_H

#include "Pin.h"
#include "Event.h"

class TimerEvent;

typedef int (*TimerEventFunction)(TimerEvent *, Pin *, int order);

class TimerEvent : public Event
{
    private:
        TimerEventFunction _onTimer = NULL;
        int _arrayItemCount = 0;
        int _timerOrder = 0;
        unsigned int _lastOperation = 0;

    public:
        bool _removeAfterUse = false;
        unsigned long * _delays = NULL;
        void * _relatedData = NULL;
        Pin * _pin = NULL;

        TimerEvent(unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        TimerEvent(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        ~TimerEvent();

        virtual int Loop();
};

#endif
