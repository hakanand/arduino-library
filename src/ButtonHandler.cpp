#include "ButtonHandler.h"
#include "Helpers\TimerEvent.h"
#include "Helpers\LinkedList.h"

// Timer Events
int ButtonHandler::HandleTimerLongPressCompleted(TimerEvent * event, Pin * pin, int order)
{
    DigitalPin * btnPin = new DigitalPin(11, OUTPUT);
    btnPin->SetLow();
    Serial.println("Turning of action for LongPress");

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

    return 1;
}

int ButtonHandler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    char * turnOff15Name = "TurnOff15";
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[1];
    btnPin->SetHigh();

    // Check if there already is a pending "turn off diod".
    LinkedList * list = event->GetOwner();
    ListItem * l = list->LocateName(turnOff15Name);
    if (l != NULL)
    {
        list->Remove(l);
    }

    list->InsertLast(new TimerEvent(turnOff15Name, 15000, true, ButtonHandler::HandleTimerLongPressCompleted));
    Serial.println("Handling ButtonLongPress");

    return 1;
}

int ButtonHandler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[2];
    // DigitalPin * btnPin = new DigitalPin(12, OUTPUT);
    btnPin->ToggleValue();

    TimerEvent * evToggle = (TimerEvent *)event->GetOwner()->LocateName("SOS");
    if (evToggle != NULL)
    {
        evToggle->SetEnabled(!evToggle->IsEnabled());
    }

    Serial.println("Handling ButtonDoublePress");
    return 0;
}

int ButtonHandler::SampleFunction(Event * event, Pin * pin)
{
    return ((DigitalPin*)pin)->ToggleValue();
}
