#include <TimerEvent.h>
#include <LinkedList.h>
#include "Handler.h"

const char * turnOffName = "TurnOnOffMeter";

// Timer Events
int Handler::HandleTimerPressCompleted(TimerEvent * event, Pin * pin, int order)
{
    ((DigitalPin *)pin)->SetLow();

    return 0;
}

int Handler::HandleButtonDown(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * meterPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_METER];
    SetOrExtendTimeForPinOff(event, meterPin, 15000, (char *)turnOffName);

    return 1;
}

int Handler::StateChangeDefault(State * state)
{
  return 0;
}

// Button events
int Handler::HandleButtonPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * operationLedPin = ((DigitalPin**)event->_relatedData)[PIN_LEDOPERATION];
    DigitalPin * mainRelayPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_MAIN];

    // Check if we now are turning the battery on
    operationLedPin->SetHigh();
    mainRelayPin->SetHigh();

    Serial.println("Handling ButtonPress");

    return 1;
}

int Handler::HandleButtonLongPress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * meterPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_METER];
    DigitalPin * operationLedPin = ((DigitalPin**)event->_relatedData)[PIN_LEDOPERATION];
    DigitalPin * mainRelayPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_MAIN];

    meterPin->SetLow();
    operationLedPin->SetLow();
    mainRelayPin->SetLow();

    Serial.println("Handling ButtonLongPress");

    return 1;
}

int Handler::HandleButtonDoublePress(ButtonEvent * event, DigitalPin * pin)
{
    DigitalPin * relayPin = ((DigitalPin**)event->_relatedData)[PIN_RELAY_MAIN];
    relayPin->ToggleValue();

    Serial.println("Handling ButtonDoublePress (Toggle RelayPin)");
    return 0;
}

void Handler::SetOrExtendTimeForPinOff(Event * event, DigitalPin * meterPin, unsigned long milliSeconds, char * turnOffName)
{
    if (meterPin->GetValue() == false)
    {
        meterPin->SetHigh();
    }

    // Check if there already is a pending "turn off diod".
    LinkedList * list = event->GetOwner();
    ListItem * l = list->LocateName(turnOffName);
    if (l != NULL)
    {
        list->Remove(l);
    }

    list->InsertLast(new TimerEvent((char *)turnOffName, milliSeconds, true, Handler::HandleTimerPressCompleted, meterPin));
}
