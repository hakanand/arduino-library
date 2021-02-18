#include <arduino.h>
#include <DigitalPin.h>
#include <AnaloguePin.h>
#include <Event.h>
#include <EventController.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>
#include <StateSource.h>

#include "Handler.h"
#include "StateMachine.h"
#include "State.h"

void InitializeStateMachine();

EventController * events = new EventController();
StateMachine * machine;

// Input pin for button.
DigitalPin * pinButton = new DigitalPin(4, INPUT);
DigitalPin * pinAcAttached = new DigitalPin(5, INPUT);

// Digital Out pins
DigitalPin * pinRelayMain = new DigitalPin(8, OUTPUT);
DigitalPin * pinRelayMeter = new DigitalPin(9, OUTPUT);
DigitalPin * pinLedMain = new DigitalPin(10, OUTPUT);
DigitalPin * pinLedOperation = new DigitalPin(11, OUTPUT);

// Display Pins
// Analogue as digital pins A0-A5 (pin 14-19)
// DigitalPin * displayEnable = new DigitalPin(14, OUTPUT);
AnaloguePin * displayEnable = new AnaloguePin(A0, 12.6, 680000, 1000000);
DigitalPin * displayData1 = new DigitalPin(15, OUTPUT);
DigitalPin * displayData2 = new DigitalPin(16, OUTPUT);
DigitalPin * displayData3 = new DigitalPin(17, OUTPUT);
DigitalPin * displayData4 = new DigitalPin(18, OUTPUT);

//
// Setup operations
//
void setup()
{
  Serial.begin(9600);
  
    // Button is on PIN2 and the button handler manage Pin10-12 which is sent along as referenced data and is used in event-handler for ButtonEvent.
  DigitalPin * pins[] = { pinLedMain, pinLedOperation, pinRelayMeter, pinButton, pinAcAttached, pinRelayMain };
  ButtonEvent * bEvent = new ButtonEvent(pinButton, Handler::HandleButtonPress, Handler::HandleButtonLongPress, Handler::HandleButtonDoublePress, Handler::HandleButtonDown, NULL, pins);
  events->InsertLast(bEvent);

  InitializeStateMachine();

  Serial.println("Initialized");

  // Controller On Led
  pinLedMain->ToggleValue();
}

// 
// Main Loop
// 
void loop() 
{
  events->Loop(50);
  machine->Loop(50);
}

void InitializeStateMachine()
{
  void * monitorItems[] = { pinAcAttached, pinRelayMain };
  machine = new StateMachine(monitorItems);

  State * s = new State((char *)"Initial", Handler::StateChangeDefault, new DigitalCompare[2] { DigitalCompare::Never, DigitalCompare::Never }, NULL);
  machine->Add(s);
}
