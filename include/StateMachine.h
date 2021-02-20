#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <PinEvent.h>
#include "State.h"

class StateMachine : public LinkedList, public Event
{
    private:
        unsigned long _lastExecution = 0;
        ListItem ** _monitorItems;
        bool * _monitorValues;
        bool * _lastUsedValues;
        int _itemCount;
    protected:
        State * _currentState = NULL;
        void AssignAndExecute(State * state);
        bool * GetMonitorItems();
        bool MonitorValuesHasChanged(bool * previousValues, bool * newValues);
    public:
        StateMachine(ListItem * monitorItems[]);
        ~StateMachine();

        bool * GetMonitorItemValues();
        virtual EventResult Loop();
        void Add(State * state);
		virtual const char * GetType() { return "StateMachine"; };
};

#endif
