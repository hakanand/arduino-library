#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <State.h>

class StateMachine : public LinkedList
{
    protected:
        char * _name;
    public:
        StateMachine(char * name);
};

#endif
