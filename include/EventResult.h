#ifndef __EVENTRESULT_H
#define __EVENTRESULT_H

#include <arduino.h>

class EventResult
{
    public:
        bool _hasExecuted = false;
        bool _shouldRemoveEvent = false;
};

#endif