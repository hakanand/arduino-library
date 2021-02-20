#ifndef __BUTTONEVENT_H
#define __BUTTONEVENT_H

#include <DigitalPin.h>
#include <Event.h>

class ButtonEvent;

typedef int (*ButtonEventFunction)(ButtonEvent *, DigitalPin *);

#define LONGPRESS_MILLIS 1100
#define DOUBLEPRESS_MILLIS 200
#define SKIPPRESS_WITHIN_TIME 30

enum LatestOperationType
{
    None,
    SinglePress,
    LongPress,
    DoublePress
};

class ButtonEvent : public Event
{
    private:
        ButtonEventFunction _onPress;
        ButtonEventFunction _onHold;
        ButtonEventFunction _onDoublePress;
        ButtonEventFunction _onDown = NULL;
        ButtonEventFunction _onUp = NULL;
        DigitalPin * _pin;
        bool _lastValue;
        unsigned long _startPressTime = 0;
        unsigned long _previousPressTime = 0;
        LatestOperationType _latestOperation = LatestOperationType::None;

    public:
        void * _relatedData;
		virtual const char * GetType() { return "ButtonEvent"; };

        ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress, void * relatedData = NULL);
        ButtonEvent(DigitalPin * pin, ButtonEventFunction onPress, ButtonEventFunction onHold, ButtonEventFunction onDoublePress, ButtonEventFunction onDown, ButtonEventFunction onUp, void * relatedData = NULL);
        EventResult Loop();

        LatestOperationType GetLastOperation();
        virtual bool GetDigitalValue();
};

#endif
