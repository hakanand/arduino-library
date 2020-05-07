#include <arduino.h>
#include <DigitalPin.h>
#include <Event.h>
#include <EventController.h>
#include <ButtonEvent.h>
#include <TimerEvent.h>
#include "Handler.h"

EventController * events = new EventController();

// Input pin for button.
DigitalPin * pin2 = new DigitalPin(2, INPUT);

// LED pins
DigitalPin * pin10 = new DigitalPin(10, OUTPUT);
DigitalPin * pin11 = new DigitalPin(11, OUTPUT);
DigitalPin * pin12 = new DigitalPin(12, OUTPUT);
DigitalPin * pin13 = new DigitalPin(13, OUTPUT);

int iter = 0;

void setup() 
{
  Serial.begin(9600);
 
  // Just do a continous blink every two seconds.
  Event * event = new Event(Handler::SampleFunction, 2000UL, pin13);
  events->InsertLast(event);

  // Button is on PIN2 and the button handler manage Pin10-12 which is sent along as Referenced data and is used in event-handler for ButtonEvent.
  DigitalPin * pins[] = { pin10, pin11, pin12 };
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
