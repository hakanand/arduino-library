#include "StateMachine.h"

StateMachine::StateMachine(void * monitorItems[])
{
    _monitorItems = monitorItems;
}

void StateMachine::Add(State * state)
{
    if (_currentState == NULL && state != NULL)
    {
        _currentState = state;
    }
}

int StateMachine::Loop(unsigned long loopMinLapLimit)
{
    // Check so that a delay is performed if this is specified and the time for loop does not  
    if (loopMinLapLimit > 0)
    {
        unsigned long now = millis();
        if (now - _lastExecution < loopMinLapLimit)
        {
            delay(loopMinLapLimit - (now - _lastExecution));
        }

        _lastExecution = millis();
    }

    return 0;
}