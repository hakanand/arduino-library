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
        Event()
        {
        }

        Event(EventFunction func)
        {
            _function = func;
            Enable();
        }

        Event(EventFunction func, int runEveryLaps)
        {
            _function = func;
            _runEveryLaps = runEveryLaps;
            Enable();
        }

        Event(EventFunction func, unsigned long runEveryMilliseconds)
        {
            _function = func;
            _runEveryMilliseconds = runEveryMilliseconds;
            Enable();
        }

        Event(char * name, EventFunction func) : ListItem(name)
        {
            _function = func;
            Enable();
        }

        Event(char * name, EventFunction func, int runEveryLaps) : ListItem(name)
        {
            _function = func;
            _runEveryLaps = runEveryLaps;
            Enable();
        }

        Event(char * name, EventFunction func, unsigned long runEveryMilliseconds) : ListItem(name)
        {
            _function = func;
            _runEveryMilliseconds = runEveryMilliseconds;
            Enable();
        }

        virtual int Loop() {
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

        bool IsEnabled()
        {
            return _enabled;
        }

        int SampleEventFunction()
        {
          Serial.println("SampleEventFunction()");

          return 0;
        }
};

#endif