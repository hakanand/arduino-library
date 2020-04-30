#include "ButtonEvent.h"

ButtonEvent::ButtonEvent(DigitalPin * pin, EventFunction onPress, EventFunction onHold, EventFunction onDoublePress) : Event()
{
    _pin = pin;
    _lastValue = _pin->GetValue();
    _onPress = onPress;
    _onHold = onHold;
    _onDoublePress = onDoublePress;

    Enable();
}

int ButtonEvent::Loop()
{
    bool value = _pin->GetValue();
    unsigned long now = millis();

    if (value == _lastValue && value == true && _startPressTime > 0)
    {
        if (now - _startPressTime > LONGPRESS_MILLIS && _onHold != NULL)
        {
            Serial.println("OnHold()");
            _onHold();
            _startPressTime = 0;
        }
    }
    else if (value != _lastValue)
    {
        if (value == true)
        {
            Serial.println("StartPress = Now()");
            _startPressTime = millis();
        }
        else if (value == false && _startPressTime > 0)
        {
            if (_onPress != NULL && now - _startPressTime <= LONGPRESS_MILLIS)
            {
                Serial.println("OnPress()");
                _onPress();
            }
            else if (_onDoublePress != NULL && _startPressTime - _previousPressTime <= DOUBLEPRESS_MILLIS)
            {
                Serial.println("OnDoublePress()");
                _onDoublePress();
            }

            _previousPressTime = _startPressTime;
            _startPressTime = 0;
        }

        return 0;
    }
}