#include <ButtonEvent.h>

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

ButtonEvent::ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress, ButtonEventFunction onDown, ButtonEventFunction onUp, void * relatedData) : ButtonEvent(pin, onPress, onHold, onDoublePress, relatedData)
{
    _onDown = onDown;
    _onUp = onUp;
}


EventResult ButtonEvent::Loop()
{
    bool value = _pin->GetValue();
    unsigned long now = millis();
    EventResult result;

    if (now - _startPressTime < SKIPPRESS_WITHIN_TIME)
    {
        // To quick press (buttons fault)
    }
    else if (value == _lastValue && value == true && _startPressTime > 0)
    {
        // Long press (On Hold)
        if (now - _startPressTime > LONGPRESS_MILLIS)
        {
            if (_onHold != NULL)
            {
                _onHold(this, _pin);
            }

            _previousPressTime = _startPressTime = 0;
            _latestOperation = LatestOperationType::LongPress;
        }
        // Double press
        else if (_startPressTime - _previousPressTime <= DOUBLEPRESS_MILLIS)
        {
            if (_onDoublePress != NULL)
            {
                _onDoublePress(this, _pin);
            }

            _previousPressTime = _startPressTime = 0;
            _latestOperation = LatestOperationType::DoublePress;
        }
    }
    else if (value != _lastValue)
    {
        if (value == true)
        {
            _previousPressTime = _startPressTime;
            _startPressTime = now;

            if (_onDown != NULL)
            {
                _onDown(this, _pin);
            }
        }
        else if (_onUp != NULL)
        {
            _onUp(this, _pin);
        }

        _lastValue = value;
    }
    else if (_startPressTime > 0 && now - _startPressTime > DOUBLEPRESS_MILLIS)
    {
        if (_onPress != NULL)
        {
            _onPress(this, _pin);
        }

        _previousPressTime = _startPressTime = 0;
        _latestOperation = LatestOperationType::LongPress;
    }

    return result;
}

// Get operation and clear it
LatestOperationType ButtonEvent::GetLastOperation()
{
    LatestOperationType returnValue = _latestOperation;
    _latestOperation = LatestOperationType::None;

    return returnValue;
}

bool ButtonEvent::GetDigitalValue()
{
    LatestOperationType type = GetLastOperation();

    if (type == LatestOperationType::SinglePress)
    {
        return true;
    }

    return false;
}