#include "ButtonController.h"

ButtonController::ButtonController()
{
}

int ButtonController::SampleFunction()
{
    delay(80);
    DigitalPin * pin = new DigitalPin(LED_BUILTIN, OUTPUT);
    return pin->ToggleValue();
}

