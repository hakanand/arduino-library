#ifndef __HANDLER_H
#define __HANDLER_H

#include <DigitalPin.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>

class Handler
{
    public:
        static int HandleButtonPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin);
        static int HandleTimerLongPressCompleted(TimerEvent * event, Pin * pin, int order);
        static int TogglePinForSosMessage(TimerEvent * event, Pin * pin, int order);
        static int SampleFunction(Event * event, Pin * pin);
};

#endif