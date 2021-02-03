#ifndef __HANDLER_H
#define __HANDLER_H

#include <DigitalPin.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>

#define PIN_LEDMAIN 0
#define PIN_LEDOPERATION 1
#define PIN_RELAY_METER 2
#define PIN_BUTTON 3
#define PIN_AC_ATTACHED 4

class Handler
{
    private:
        static void SetOrExtendTimeForPinOff(Event * event, DigitalPin * pinLedOperation, unsigned long milleSeconds, char * turnOffName);
    public:
        static int HandleButtonPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin);
 
        // NOP
        static int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin);
        static int HandleTimerPressCompleted(TimerEvent * event, Pin * pin, int order);
};

#endif