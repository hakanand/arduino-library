#ifndef __EVENTCONTROLLER_H
#define __EVENTCONTROLLER_H

#include <arduino.h>
#include "LinkedList.h"
#include "Event.h"

class EventController : public LinkedList
{
    private:
        unsigned long _lastExecution = 0;

    public:
        EventController()
        {
        }

        int Loop(unsigned long loopMinLapLimit = 0)
        {
            int numberOfCallItems = 0;

            // Check so that a delay is performed if this 
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
                    numberOfCallItems += item->Loop();
                }

                item = (Event *)GetNextItem();
            }

            return numberOfCallItems;
        }
};

#endif