#ifndef __STATE_H
#define __STATE_H

#include <Arduino.h>
#include <ListItem.h>
#include <Pin.h>
#include <Event.h>

class State;

enum DigitalCompare
{
    False,
    True,
    NA,
    Never
};

enum CanChangeStateReplies
{
    Yes,
    No,
    Must
};

enum StateFunctionOptions
{
    ShouldEnter,
    CanExit,
    Process
};

typedef CanChangeStateReplies (*StateChangeFunction)(State * state, StateFunctionOptions options, bool * values);

class State : public ListItem
{
    protected:
        StateChangeFunction _stateChangeFunction;
    public:
        DigitalCompare * _enterCriteria, * _exitCriteria;
        State(char * name, StateChangeFunction function);
        State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria);

        bool Enter(bool * values);
        bool Exit(bool * values);
        CanChangeStateReplies ShouldEnter(bool * values);
        CanChangeStateReplies CanExit(bool * values);
};

#endif
