#ifndef __TIMEREVENT_H
#define __TIMEREVENT_H

#include <Pin.h>
#include <Event.h>

class TimerEvent;

typedef int (*TimerEventFunction)(TimerEvent *, Pin *, int order);

class TimerEvent : public Event
{
    private:
        TimerEventFunction _onTimer = NULL;
        int _arrayItemCount = 0;
        int _timerOrder = 0;
        unsigned long _lastOperation = 0;

    public:
        unsigned long * _delays = NULL;
        void * _relatedData = NULL;
		virtual const char * GetType() { return "TimerEvent"; };

        TimerEvent(unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        TimerEvent(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        TimerEvent(char * name, unsigned long delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        TimerEvent(char * name, unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin = NULL, void * relatedData = NULL);
        ~TimerEvent();

        EventResult Loop();
        void Init(unsigned long * delay, bool removeAfterUse, TimerEventFunction func, Pin * pin, void * relatedData);
};

#endif
