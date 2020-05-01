#include <arduino.h>
#include <DigitalPin.h>
#include "Helpers\ButtonController.h"
#include "Helpers\Event.h"
#include "Helpers\EventController.h"
#include "Helpers\ButtonEvent.h"
#include "ButtonHandler.h"

// DigitalPin testPin(2, INPUT);
/*
TimedEvent(controller->SampleFunction(*events), )
*/

EventController * events = new EventController();
ButtonController * controller = new ButtonController();
ButtonHandler * buttonHandler = new ButtonHandler();

DigitalPin pin(13, OUTPUT);
DigitalPin pin2(2, INPUT);

int iter = 0;

void setup() 
{
  Serial.begin(9600);
 
  Event * event = new Event(controller->SampleFunction, 2, &pin);
  events->InsertLast(event);

  ButtonEvent * bEvent = new ButtonEvent(&pin2, buttonHandler->HandleButtonPress, buttonHandler->HandleButtonLongPress, buttonHandler->HandleButtonDoublePress);
  events->InsertLast(bEvent);

  Serial.println("Initialized");
}

void loop() 
{
  char message[1024];
  sprintf(message, "Loop %i", iter++);
  Serial.println(message);

  delay(1000);
  events->Loop();
}
