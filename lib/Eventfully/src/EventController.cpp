#include <EventController.h>

EventController::EventController()
{  
}

int EventController::Loop(unsigned long loopMinLapLimit)
{
    int numberOfCallItems = 0;

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

    Event * item = (Event *)GetFirstItem();
    while(item != NULL)
    {
        bool removal = false;
    
        if (item->IsEnabled())
        {
            ++numberOfCallItems;
            EventResult * result = item->Loop();

            if ((result->_hasExecuted && item->_removeAfterUse == true) || result->_shouldRemoveEvent == true)
            {
                removal = true;
                item = (Event *)Remove(item);
            }
        }

        if (removal == false)
        {
            item = (Event *)GetNextItem();
        }
    }

    return numberOfCallItems;
}
