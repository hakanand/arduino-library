#include <arduino.h>
#include <DigitalPin.h>
#include "Helpers\ButtonController.h"
#include "Helpers\Event.h"
#include "Helpers\EventController.h"

// DigitalPin testPin(2, INPUT);

EventController * events = new EventController();
ButtonController * controller;
Event * event;

void setup() 
{
  Serial.begin(9600);
  controller = new ButtonController();
  event = new Event(controller->SampleFunction, 500);
  events->InsertLast(event);


}

void loop() 
{
  events->Loop(5);
}
