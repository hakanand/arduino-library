#include <Arduino.h>
#include <DigitalPin.h>

DigitalPin ledPin(LED_BUILTIN, OUTPUT);
DigitalPin testPin(2, INPUT);
char test[128];

void setup() {
  Serial.begin(9600);
  ledPin.SetLow();
}

void loop() {
  // ledPin.ToggleValue();
  int result = testPin.GetValue();

  sprintf(test, "Value is %i", result);
  Serial.println(test);

  delay(1000);
}
