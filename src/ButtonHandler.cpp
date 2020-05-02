#include "ButtonHandler.h"
#include "Helpers\TimerEvent.h"
#include "Helpers\LinkedList.h"

// Timer Events
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

// Button events
int ButtonHandler::HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[0];
    // DigitalPin * btnPin = new DigitalPin(10, OUTPUT);
    btnPin->ToggleValue();

    Serial.println("Handling ButtonPress");
    return 0;
}

int ButtonHandler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[1];
    // DigitalPin * btnPin = new DigitalPin(11, OUTPUT);
    btnPin->SetHigh();

    // Check if there already is a pending "turn off diod".
    LinkedList * list = event->GetOwner();
    ListItem * l = list->LocateName("TurnOff15");
    if (l != NULL)
    {
        Serial.println("Removing item from list.");
        list->Remove(l);
    }

    Serial.println("Adding new  item to list.");
    list->InsertLast(new TimerEvent("TurnOff15", 15000, true, ButtonHandler::HandleTimerLongPressCompleted));

    Serial.println("Handling ButtonLongPress");
    return 0;
}

int ButtonHandler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[2];
    // DigitalPin * btnPin = new DigitalPin(12, OUTPUT);
    btnPin->ToggleValue();

    Serial.println("Handling ButtonDoublePress");
    return 0;
}

