#include "EventController.h"

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
            // char message[128];
            // sprintf(message, "Now executing sleep for %i ms", loopMinLapLimit - (now - _lastExecution));
            // Serial.println(message);
            delay(loopMinLapLimit - (now - _lastExecution));
        }

        _lastExecution = millis();
    }

    Event * item = (Event *)GetFirstItem();
    while(item != NULL)
    {
        if (item->IsEnabled())
        {
            Serial.println("Calling Event Loop function.");
            numberOfCallItems += item->Loop();
        }
        else
        {
            Serial.println("Skipping - Event not enabled.");
        }
        

        item = (Event *)GetNextItem();
    }

    return numberOfCallItems;
}
