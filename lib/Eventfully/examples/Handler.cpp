#include <TimerEvent.h>
#include <LinkedList.h>
#include "Handler.h"

// Timer Events
int Handler::HandleTimerLongPressCompleted(TimerEvent * event, Pin * pin, int order)
{
    DigitalPin * btnPin = new DigitalPin(11, OUTPUT);
    btnPin->SetLow();
    Serial.println("Turning of action for LongPress");

    return 0;
}

int Handler::TogglePinForSosMessage(TimerEvent * event, Pin * pin, int order)
{
    ((DigitalPin *)pin)->ToggleValue();

    return 0;
}

// Button events
int Handler::HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[0];
    btnPin->ToggleValue();

    return 1;
}

int Handler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    const char * turnOff15Name = "TurnOff15";
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[1];
    btnPin->SetHigh();

    // Check if there already is a pending "turn off diod".
    LinkedList * list = event->GetOwner();
    ListItem * l = list->LocateName((char*)turnOff15Name);
    if (l != NULL)
    {
        list->Remove(l);
    }

    list->InsertLast(new TimerEvent((char *)turnOff15Name, 15000, true, Handler::HandleTimerLongPressCompleted));
    Serial.println("Handling ButtonLongPress");

    return 1;
}

int Handler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    const char * sosTimerName = "SOS";
    DigitalPin * btnPin = ((DigitalPin**)event->_relatedData)[2];
    btnPin->ToggleValue();

    TimerEvent * evToggle = (TimerEvent *)event->GetOwner()->LocateName((char *)sosTimerName);
    if (evToggle != NULL)
    {
        evToggle->SetEnabled(!evToggle->IsEnabled());
    }

    Serial.println("Handling ButtonDoublePress");
    return 0;
}

int Handler::SampleFunction(Event * event, Pin * pin)
{
    return ((DigitalPin*)pin)->ToggleValue();
}
