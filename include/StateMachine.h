#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <State.h>
#include <PinEvent.h>

class StateMachine : public LinkedList, public Event
{
    private:
        unsigned long _lastExecution = 0;
        ListItem ** _monitorItems;
        int _itemCount;
    protected:
        State * _currentState = NULL;
        void AssignAndExecute(State * state);
        bool * GetMonitorItems();
    public:
        StateMachine(ListItem * monitorItems[]);
        bool * GetMonitorItemValues();
        virtual EventResult Loop();
        void Add(State * state);
		virtual const char * GetType() { return "StateMachine"; };
};

#endif
