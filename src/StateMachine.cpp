#include "StateMachine.h"

StateMachine::StateMachine(ListItem * monitorItems[])
{
    _monitorItems = monitorItems;
    _itemCount = sizeof(_monitorItems) / sizeof(void *);
}

void StateMachine::Add(State * state)
{
    Add(state);

    if (_currentState == NULL && state != NULL)
    {
        _currentState = state;
    }
}

EventResult StateMachine::Loop()
{
    CanChangeStateReplies changeAllowed = CanChangeStateReplies::Yes;
    State * newState = NULL;

    bool * values = GetMonitorItemValues();

    // Check if the selected item allows change based upon the existing values.
    if  (_currentState != NULL)
    {
        // A typical state of fire and someone wants to turn off the water... Not allowed.
        changeAllowed = _currentState->CanExit(values);
    }

    if (changeAllowed != CanChangeStateReplies::No)
    {
        // Go through all items and see if somebody wants to take the State.
        State * item = (State *)GetFirstItem();
        while (item != NULL)
        {
            CanChangeStateReplies result = item->ShouldEnter(values);
            if (result == CanChangeStateReplies::Must)
            {
                // Dont break until we have went through all items or finds one that must have the state.
                newState = item;
                break;
            }
            else if (result == CanChangeStateReplies::Yes && newState == NULL)
            {
                // Well somebody wanted the state but if it was not first (newState == NULL) it will not get it.
                // If however someone MUST have the state they can get it based upon since we are traversing everything and breaking.
                newState = item;
            }

            // Another one?
            item = (State *)GetNext();
        }

        // Was a new state approved?
        if (newState != NULL)
        {
            newState->Enter(values);
        }
    }

    return EventResult(newState != NULL, false);
}

bool * StateMachine::GetMonitorItemValues()
{
    for(int i=0; i < _itemCount; ++i)
    {
        // Check what type of supported class this is.
        const char * type = _monitorItems[i]->GetType();
        if (strcmp(type, "DigitalPin"))
        {

        }
    }

    return new bool[2] { true, false };
}