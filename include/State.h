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

enum CanMoveChoices
{
    Yes,
    No,
    Must
};

class State : public ListItem
{
    protected:
        StateChangeFunction _stateChangeFunction;
    public:
        DigitalCompare * _enterCriteria, * _exitCriteria;
        State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria);

        bool Enter(bool * values);
        bool Exit(bool * values);
        CanMoveChoices ShouldEnter(bool * values);
        CanMoveChoices CanExit(bool * values);
};

#endif
