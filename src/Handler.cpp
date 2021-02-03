#include <TimerEvent.h>
#include <LinkedList.h>
#include "Handler.h"

const char * turnOffName = "TurnOff";

// Timer Events
int Handler::HandleTimerPressCompleted(TimerEvent * event, Pin * pin, int order)
{
    ((DigitalPin *)pin)->SetLow();

    return 0;
}

// Button events
int Handler::HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * relayPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_METER];
    DigitalPin * pinLedOperation = ((DigitalPin**)event->_relatedData)[PIN_LEDOPERATION];

    // Check if we now are turning the battery on
    if (relayPin->GetValue() == false)
    {
        relayPin->SetHigh();
    }

    pinLedOperation->SetHigh();

    Serial.println("Handling ButtonPress");

    return 1;
}

int Handler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * relayPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_METER];
    DigitalPin * pinLedOperation = ((DigitalPin**)event->_relatedData)[PIN_LEDOPERATION];

    relayPin->SetLow();
    pinLedOperation->SetLow();

    Serial.println("Handling ButtonLongPress");

    return 1;
}

int Handler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    Serial.println("Handling ButtonDoublePress (NOP)");
    return 0;
}

void Handler::SetOrExtendTimeForPinOff(Event * event, DigitalPin * pinLedOperation, unsigned long milliSeconds, char * turnOffName)
{
    pinLedOperation->SetHigh();

    // Check if there already is a pending "turn off diod".
    LinkedList * list = event->GetOwner();
    ListItem * l = list->LocateName(turnOffName);
    if (l != NULL)
    {
        list->Remove(l);
    }

    list->InsertLast(new TimerEvent((char *)turnOffName, milliSeconds, true, Handler::HandleTimerPressCompleted, pinLedOperation));
}
