#include <arduino.h>
#include <DigitalPin.h>
#include "Helpers\ButtonController.h"
#include "Helpers\Event.h"

// DigitalPin testPin(2, INPUT);

ButtonController * controller;
Event * event;

void setup() 
{
  Serial.begin(9600);
  controller = new ButtonController();
  event = new Event(controller->SampleFunction, (unsigned long)5000);
}

void loop() 
{
  event->Loop();
}
