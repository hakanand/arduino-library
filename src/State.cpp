#include "State.h"

State::State(char * name, StateChangeFunction function, DigitalCompare * enterCriteria, DigitalCompare * exitCriteria) : ListItem(name)
{
    _enterCriteria = enterCriteria;
    _exitCriteria = exitCriteria;
    _stateChangeFunction = function;
}
