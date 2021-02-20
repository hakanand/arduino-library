#include "State.h"

State::State(char * name, StateChangeFunction function) : ListItem(name)
{
    _enterCriteria = NULL;
    _exitCriteria = NULL;
    _stateChangeFunction = function;
}

State::State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria) : ListItem(name)
{
    _enterCriteria = enterCriteria;
    _exitCriteria = exitCriteria;
    _stateChangeFunction = function;
}

bool State::Enter(bool * values)
{
    return _stateChangeFunction(this, StateFunctionOptions::Enter, values) == CanChangeStateReplies::Yes;
}

bool State::Exit(bool * values)
{
    return _stateChangeFunction(this, StateFunctionOptions::Exit, values) == CanChangeStateReplies::Yes;
}

CanChangeStateReplies State::ShouldEnter(bool * values)
{
    if (_enterCriteria != NULL)
    {
        return MatchValues(_enterCriteria, values);
    }
    else
    {
        return _stateChangeFunction(this, StateFunctionOptions::ShouldEnter, values);
    }
    
    return CanChangeStateReplies::No;
}

CanChangeStateReplies State::CanExit(bool * values)
{
    if (_exitCriteria != NULL)
    {
        return MatchValues(_exitCriteria, values);
    }
    else
    {
        return _stateChangeFunction(this, StateFunctionOptions::ShouldEnter, values);
    }
    
    return CanChangeStateReplies::Yes;
}

CanChangeStateReplies State::MatchValues(DigitalCompare * criteria, bool * values)
{
    CanChangeStateReplies result = CanChangeStateReplies::No;

    if (sizeof(criteria) / sizeof(DigitalCompare *) != sizeof(values) / sizeof(bool *))
    {
        Serial.println("Sizeof of DigitalCompare * criteria, bool * values differs. Skipping comparison.");
    }
    else
    {
        int items = sizeof(criteria) / sizeof(DigitalCompare *);

        for(int i = 0; i < items; ++i)
        {
            if (criteria[i] == DigitalCompare::Never)
            {
                return CanChangeStateReplies::No;
            }
            if ((criteria[i] == DigitalCompare::True || criteria[i] == DigitalCompare::NA) && values[i] == true)
            {
                // OK
            }
            else if (criteria[i] == DigitalCompare::True && values[i] == true)
            {
                // OK
            }
        }

    }

    return result;
}
