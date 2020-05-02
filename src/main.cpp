#include <arduino.h>
#include <DigitalPin.h>
#include "Helpers\ButtonController.h"
#include "Helpers\Event.h"
#include "Helpers\EventController.h"
#include "Helpers\ButtonEvent.h"
#include "Helpers\TimerEvent.h"
#include "ButtonHandler.h"

// DigitalPin testPin(2, INPUT);
/*
TimedEvent(controller->SampleFunction(*events), )
*/

EventController * events = new EventController();

DigitalPin pin(13, OUTPUT);
DigitalPin * pin12 = new DigitalPin(12, OUTPUT);
DigitalPin pin2(2, INPUT);

int iter = 0;

void setup() 
{
  Serial.begin(9600);
 
  Event * event = new Event(ButtonController::SampleFunction, 2000UL, &pin);
  events->InsertLast(event);

  DigitalPin * pins[] = { new DigitalPin(10, OUTPUT), new DigitalPin(11, OUTPUT), new DigitalPin(12, OUTPUT) };
  ButtonEvent * bEvent = new ButtonEvent(&pin2, ButtonHandler::HandleButtonPress, ButtonHandler::HandleButtonLongPress, ButtonHandler::HandleButtonDoublePress, pins);
  events->InsertLast(bEvent);

  const unsigned long period = 180;
  unsigned long times[] = { period*7, period, period, period, period, period, period, period*3, period, period*3, period, period*3, period, period, period, period, period, period, 0 };
  TimerEvent * tEvent = new TimerEvent(times, true, ButtonHandler::TogglePinForSosMessage, pin12);
  events->InsertLast(tEvent);

  Serial.println("Initialized");
}

void loop() 
{
  // int value = digitalRead(2);
  // char message[1024];
  // sprintf(message, "Loop %i (%i)", iter++, value);
  // Serial.println(message);

  events->Loop();
}
