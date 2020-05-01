#ifndef __BUTTONCONTROLLER_H
#define __BUTTONCONTROLLER_H

#include <arduino.h>
#include <DigitalPin.h>
#include "Event.h"

class ButtonController
{
    public:
        static int _iterator;
        
    public:
        ButtonController();
        static int SampleFunction(Event * event, Pin * pin);
};

#endif