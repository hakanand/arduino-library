#ifndef __BUTTONHANDLER_H
#define __BUTTONHANDLER_H

#include <arduino.h>
#include <DigitalPin.h>
#include "Helpers\ButtonEvent.h"

class ButtonHandler
{
    public:
        static int HandleButtonPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin);
};

#endif