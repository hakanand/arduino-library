#include <PinEvent.h>

PinEvent::PinEvent(Pin * pin, PinEventFunction function) : Event(pin)
{
    _pinType = PinType::Digital;
    _onEvent = function;
    _curSelected = (_pin->GetValue() == HIGH ? EventType::OnHigh : EventType::OnLow);
}

PinEvent::PinEvent(Pin * pin, PinEventFunction function, int low, int high) : Event(pin)
{
    _pinType = PinType::Analogue;
    _onEvent = function;
    _lowSetting = low;
    _highSetting = high;

    int value = _pin->GetValue();
    _curSelected =  (value >= low && value <= high ? EventType::InRange : EventType::OutOfRange);
}

EventResult PinEvent::Loop()
{
    int value = _pin->GetValue();
    EventType eventTypeForValue;
    EventResult result;

    if (_pinType == PinType::Digital)
    {
        eventTypeForValue = (value == HIGH ? EventType::OnHigh : EventType::OnLow);
    }
    else // if (_pinType == PinType::Analogue)
    {
        eventTypeForValue = (value >= _lowSetting && value <= _highSetting ? EventType::InRange : EventType::OutOfRange);
    }

    if (_curSelected != eventTypeForValue)
    {
        _onEvent(this, _pin, eventTypeForValue);
        _curSelected = eventTypeForValue;
        result._hasExecuted = true;
    }

    return result;
}