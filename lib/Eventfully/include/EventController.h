#ifndef __EVENTCONTROLLER_H
#define __EVENTCONTROLLER_H

#include <arduino.h>
#include <LinkedList.h>
#include <Event.h>

class EventController : public LinkedList
{
    private:
        unsigned long _lastExecution = 0;

    public:
        EventController();
		virtual const char * GetType() { return "EventController"; };
        int Loop(unsigned long loopMinLapLimit = 0);
};

#endif