#ifndef __STATE_H
#define __STATE_H

#include <Arduino.h>
#include <ListItem.h>
#include <Pin.h>
#include <Event.h>

typedef int (*StateChangeFunction)(char * stateName);

enum DigitalCompare
{
    False,
    True,
    NA,
    Never
};

class State : public ListItem
{
    protected:
        StateChangeFunction _stateChangeFunction;
    public:
        DigitalCompare * _enterCriteria, * exitCriteria;
        State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria);
};

#endif
