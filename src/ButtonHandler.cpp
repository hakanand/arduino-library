#include "ButtonHandler.h"

int HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    Serial.println("ButtonPress");
    return 0;
}

int HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    Serial.println("ButtonLongPress");
    return 0;
}

int HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    Serial.println("ButtonDoublePress");
    return 0;
}