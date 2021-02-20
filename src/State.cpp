#include "State.h"

State::State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria) : ListItem(name)
{
    _enterCriteria = enterCriteria;
    _exitCriteria = exitCriteria;
    _stateChangeFunction = function;
}

bool State::Enter(bool * values)
{
    return false;
}

bool State::Exit(bool * values)
{
    return false;
}

CanChangeStateReplies State::ShouldEnter(bool * values)
{
    return CanChangeStateReplies::Yes;
}

CanChangeStateReplies State::CanExit(bool * values)
{
    return CanChangeStateReplies::Yes;
}
