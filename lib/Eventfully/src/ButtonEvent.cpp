#include "ButtonEvent.h"

ButtonEvent::ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress, void * relatedData) : Event()
{
    _pin = pin;
    _lastValue = _pin->GetValue();
    _onPress = onPress;
    _onHold = onHold;
    _onDoublePress = onDoublePress;
    _relatedData = relatedData;

    Enable();
}

EventResult * ButtonEvent::Loop()
{
    bool value = _pin->GetValue();
    unsigned long now = millis();

    if (now - _startPressTime < SKIPPRESS_WITHIN_TIME)
    {
        // To quick press (buttons fault)
    }
    else if (value == _lastValue && value == true && _startPressTime > 0)
    {
        // Long press (On Hold)
        if (now - _startPressTime > LONGPRESS_MILLIS && _onHold != NULL)
        {
            _onHold(this, _pin);
            _previousPressTime = _startPressTime = 0;
        }
        // Double press
        else if (_onDoublePress != NULL && _startPressTime - _previousPressTime <= DOUBLEPRESS_MILLIS)
        {
            _onDoublePress(this, _pin);
            _previousPressTime = _startPressTime = 0;
        }
    }
    else if (value != _lastValue)
    {
        if (value == true)
        {
            _previousPressTime = _startPressTime;
            _startPressTime = now;
        }

        _lastValue = value;
    }
    else if (_startPressTime > 0 && now - _startPressTime > DOUBLEPRESS_MILLIS)
    {
        _onPress(this, _pin);
        _previousPressTime = _startPressTime = 0;
    }

    return &_result;
}
