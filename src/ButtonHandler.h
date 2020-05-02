#ifndef __BUTTONHANDLER_H
#define __BUTTONHANDLER_H

#include <DigitalPin.h>
#include "Helpers\ButtonEvent.h"
#include "Helpers\TimerEvent.h"

class ButtonHandler
{
    public:
        static int HandleButtonPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin);
        static int HandleTimerLongPressCompleted(TimerEvent * event, Pin * pin, int order);
        static int TogglePinForSosMessage(TimerEvent * event, Pin * pin, int order);
};

#endif