#ifndef __BUTTONEVENT_H
#define __BUTTONEVENT_H

#include <arduino.h>
#include "Event.h"
#include "DigitalPin.h"

#define LONGPRESS_MILLIS 3000
#define DOUBLEPRESS_MILLIS 500

class ButtonEvent : Event
{
    private:
        EventFunction _onPress;
        EventFunction _onRelease;
        EventFunction _onHold;
        EventFunction _onDoublePress;
        DigitalPin * _pin;
        bool _lastValue;
        unsigned long _startPressTime = 0;
        unsigned long _previousPressTime = 0;

    public:
        ButtonEvent(DigitalPin * pin, EventFunction onPress, EventFunction onRelease, EventFunction onHold, EventFunction onDoublePress) : Event()
        {
            _pin = pin;
            _lastValue = _pin->GetValue();
            _onPress = onPress;
            _onRelease = onRelease;
            _onHold = onHold;
            _onDoublePress = onDoublePress;

            Enable();
        }

        virtual int Loop()
        {
            int executions = 0;
            bool value = _pin->GetValue();
            if (value != _lastValue)
            {
                if (value == true)
                {
                    _startPressTime = millis();
                    if (_onPress != NULL)
                    {
                        _onPress();
                        executions++;
                    }

                    if (_startPressTime - _previousPressTime <= DOUBLEPRESS_MILLIS && _onDoublePress != NULL)
                    {
                        _onDoublePress();
                        executions++;
                    }
                }
                else if (value == false && _startPressTime != 0)
                {
                    // Check long press (3000ms)
                    unsigned long now = millis();
                    if (_onRelease != NULL)
                    {
                        _onRelease();
                        executions++;
                    }

                    if (now - _startPressTime > LONGPRESS_MILLIS && _onHold != NULL)
                    {
                        _onHold();
                        executions++;
                    }

                    _previousPressTime = _startPressTime;
                    _startPressTime = 0;
                }
            }

            return executions;
        }
};

#endif