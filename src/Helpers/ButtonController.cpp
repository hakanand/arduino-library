#include "ButtonController.h"
#include <Pin.h>
#include "Event.h"

ButtonController::ButtonController()
{
    // ButtonController::_iterator = 1;
}

int ButtonController::SampleFunction(Event * event, Pin * pin)
{
    // char message[128];
    // sprintf(message, "Now toggling %i times", ButtonController::_iterator);
    // Serial.println(message);

    // ButtonController::_iterator++;

    return ((DigitalPin*)pin)->ToggleValue();
}
