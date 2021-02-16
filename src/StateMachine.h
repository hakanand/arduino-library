#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <State.h>
#include <PinEvent.h>

class StateMachine : public LinkedList
{
    private:
        unsigned long _lastExecution = 0;
        void ** _monitorItems;
    protected:
        State * _currentState = NULL;
        void AssignAndExecute(State * state);
    public:
        StateMachine(void * monitorItems[]);
        void Add(State * state);
        int Loop(unsigned long loopMinLapLimit = 0);
};

#endif
