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

void setup() 
{
  // Allow floating point operations in printf
  asm(".global _printf_float");

  Serial.begin(9600);
  
    // Button is on PIN2 and the button handler manage Pin10-12 which is sent along as referenced data and is used in event-handler for ButtonEvent.
  DigitalPin * pins[] = { pinLedMain, pinLedOperation, pinRelayMeter, pinButton, pinAcAttached, pinRelayMain };
  ButtonEvent * bEvent = new ButtonEvent(pinButton, Handler::HandleButtonPress, Handler::HandleButtonLongPress, Handler::HandleButtonDoublePress, Handler::HandleButtonDown, NULL, pins);
  events->InsertLast(bEvent);

  InitializeStateMachine();

  // Controller On Led
  pinLedMain->ToggleValue();

  Serial.println("Initialized");
}

float prevVoltage;
void loop() 
{
  float value = displayEnable->GetVoltage();
  if(value != prevVoltage)
  {
    Serial.println("Val changed"); //value);
    prevVoltage = value;
  }

  events->Loop();
}

class Test
{
  public:
    static int StateChangeDefault(char * stateName);
};

int Test::StateChangeDefault(char * stateName)
{
  return 0;
}

void InitializeStateMachine()
{
  void * monitorItems[] = { pinAcAttached, pinRelayMain };
  machine = new StateMachine(monitorItems);

  DigitalCompare * a = new DigitalCompare[2] { DigitalCompare::Never, DigitalCompare::Never };

  State * s = new State((char *)"Initial", Test::StateChangeDefault, new DigitalCompare[2] { DigitalCompare::Never, DigitalCompare::Never }, NULL );
  machine->Add(s);
}
