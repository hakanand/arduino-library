#ifndef __HANDLER_H
#define __HANDLER_H

#include <DigitalPin.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>
#include <State.h>

#define PIN_LEDMAIN 0
#define PIN_LEDOPERATION 1
#define PIN_RELAY_METER 2
#define PIN_BUTTON 3
#define PIN_AC_ATTACHED 4
#define PIN_RELAY_MAIN 5

class Handler
{
    private:
        static void SetOrExtendTimeForPinOff(Event * event, DigitalPin * pin, unsigned long milleSeconds, char * turnOffName);
    public:
        static int HandleButtonPress(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonDown(ButtonEvent * event, DigitalPin * pin);
        static int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin);
        static int StateChangeDefault(State * state);

        // NOP
        static int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin);
        static int HandleTimerPressCompleted(TimerEvent * event, Pin * pin, int order);
};

#endif