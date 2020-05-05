#include <arduino.h>
#include <DigitalPin.h>
#include <Event.h>
#include <EventController.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>
#include "Handler.h"

EventController * events = new EventController();

DigitalPin * pin13 = new DigitalPin(13, OUTPUT);
DigitalPin * pin12 = new DigitalPin(12, OUTPUT);
DigitalPin * pin2 = new DigitalPin(2, INPUT);

int iter = 0;

void setup() 
{
  Serial.begin(9600);
 
  Event * event = new Event(Handler::SampleFunction, 2000UL, pin13);
  events->InsertLast(event);

  // Referenced data used in event-handler for ButtonEvent.
  // Button is on PIN2 and the handlers manage Pin10-12.
  DigitalPin * pins[] = { new DigitalPin(10, OUTPUT), new DigitalPin(11, OUTPUT), new DigitalPin(12, OUTPUT) };
  ButtonEvent * bEvent = new ButtonEvent(pin2, Handler::HandleButtonPress, Handler::HandleButtonLongPress, Handler::HandleButtonDoublePress, pins);
  events->InsertLast(bEvent);

  // Emulate morse code SOS on PIN12 where one perod is 180ms. Notice last time is set to 0 to end the array.
  const unsigned long p = 180;
  unsigned long times[] = { p*7, p, p, p, p, p, p, p*3, p, p*3, p, p*3, p, p, p, p, p, p, 0 };
  TimerEvent * tEvent = new TimerEvent("SOS", times, false, Handler::TogglePinForSosMessage, pin12);
  events->InsertLast(tEvent);

  Serial.println("Initialized");
}

void loop() 
{
  events->Loop();
}
