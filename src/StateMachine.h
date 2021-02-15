#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <State.h>
#include <PinEvent.h>

class StateMachine : public LinkedList
{
    private:
        LinkedList * _monitorPins;
    protected:
        char * _name;
    public:
        StateMachine(LinkedList * monitorPins);
        void Add(State * state);
};

#endif
