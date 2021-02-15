#include <EventResult.h>

EventResult::EventResult()
{
    _hasExecuted = false;
    _shouldRemoveEvent = false;
}

EventResult::EventResult(bool hasExecuted, bool shouldRemoveEvent)
{
    _hasExecuted = hasExecuted;
    _shouldRemoveEvent = shouldRemoveEvent;
}