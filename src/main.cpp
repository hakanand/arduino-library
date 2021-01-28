#include <arduino.h>
#include <DigitalPin.h>
#include <Event.h>
#include <EventController.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>
#include "Handler.h"

EventController * events = new EventController();

// Input pin for button.
DigitalPin * pinEmergencyStop = new DigitalPin(2, INPUT);
DigitalPin * pinButton = new DigitalPin(3, INPUT);
DigitalPin * pinAcAttached = new DigitalPin(4, INPUT);

// Digital Out pins
DigitalPin * pinLed = new DigitalPin(10, OUTPUT);
DigitalPin * pinRelayMain = new DigitalPin(11, OUTPUT);
DigitalPin * pinTimedOn = new DigitalPin(12, OUTPUT);

// Display Pins
// Analogue as digital pins A0-A5 (pin 14-19)
DigitalPin * displayEnable = new DigitalPin(14, OUTPUT);
DigitalPin * displayData1 = new DigitalPin(15, OUTPUT);
DigitalPin * displayData2 = new DigitalPin(16, OUTPUT);
DigitalPin * displayData3 = new DigitalPin(17, OUTPUT);
DigitalPin * displayData4 = new DigitalPin(18, OUTPUT);


void setup() 
{
  Serial.begin(9600);

  // Button is on PIN2 and the button handler manage Pin10-12 which is sent along as referenced data and is used in event-handler for ButtonEvent.
  DigitalPin * pins[] = { pinLed, pinRelayMain, pinTimedOn };
  ButtonEvent * bEvent = new ButtonEvent(pinButton, Handler::HandleButtonPress, Handler::HandleButtonLongPress, Handler::HandleButtonDoublePress, Handler::HandleButtonDownPress, NULL, pins);
  events->InsertLast(bEvent);

  // Controller On Led
  pinLed->ToggleValue();

  Serial.println("Initialized");
}

void loop() 
{
  events->Loop();
}
