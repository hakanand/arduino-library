#ifndef __BUTTONCONTROLLER_H
#define __BUTTONCONTROLLER_H

#include <arduino.h>
#include <DigitalPin.h>

class ButtonController
{
    private:

    public:
        ButtonController()
        {
        }

        static int SampleFunction()
        {
            DigitalPin pin(LED_BUILTIN, OUTPUT);
            return pin.ToggleValue();
        }
};

#endif