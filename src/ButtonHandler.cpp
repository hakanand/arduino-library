#include "ButtonHandler.h"
#include "Helpers\TimerEvent.h"
#include "Helpers\LinkedList.h"

int ButtonHandler::HandleTimerLongPressCompleted(TimerEvent * event, Pin * pin, int order)
{
    DigitalPin * btnPin = new DigitalPin(11, OUTPUT);
    btnPin->SetLow();

    return 0;
}

int ButtonHandler::TogglePinForSosMessage(TimerEvent * event, Pin * pin, int order)
{
    ((DigitalPin *)pin)->ToggleValue();

    return 0;
}

int ButtonHandler::HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = new DigitalPin(10, OUTPUT);
    btnPin->ToggleValue();

    Serial.println("Handling ButtonPress");
    return 0;
}

int ButtonHandler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = new DigitalPin(11, OUTPUT);
    btnPin->SetHigh();

    LinkedList * list = event->GetOwner();
    list->InsertLast(new TimerEvent(15000, true, ButtonHandler::HandleTimerLongPressCompleted));

    Serial.println("Handling ButtonLongPress");
    return 0;
}

int ButtonHandler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = new DigitalPin(12, OUTPUT);
    btnPin->ToggleValue();

    Serial.println("Handling ButtonDoublePress");
    return 0;
}

