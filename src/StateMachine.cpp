#include <ButtonEvent.h>
#include "StateMachine.h"

StateMachine::StateMachine(ListItem * monitorItems[])
{
    _monitorItems = monitorItems;
    _itemCount = sizeof(_monitorItems) / sizeof(void *);
    _monitorValues = (bool *)malloc(_itemCount * sizeof(bool));
}

StateMachine::~StateMachine()
{
    if(_itemCount > 0)
    {
        free(_monitorValues);
    }
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
            _currentState->Exit(values);
            newState->Enter(values);

            _currentState = newState;
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
        if (strcmp(type, "DigitalPin") == 0 || strcmp(type, "AnaloguePin") == 0 || strcmp(type, "Pin") == 0)
        {
            _monitorValues[i] = ((Pin *)_monitorItems[i])->GetDigitalValue();
        }
        else if (strcmp(type, "ButtonEvent") == 0)
        {
            _monitorValues[i] = ((ButtonEvent *)_monitorItems[i])->GetDigitalValue();
        }
    }

    return _monitorValues;
}

// Is used to skip checks (for performance) if no montitorvalues have changed.
bool StateMachine::MonitorValuesHasChanged(bool * previousValues, bool * newValues)
{
    bool hasChanged = false;
 
    for(int i = 0; i < _itemCount; ++i)
    {
        if (previousValues[i] != newValues[i])
        {
            hasChanged = true;
            break;
        }
    }
    
    return hasChanged;
}