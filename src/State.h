#ifndef __STATE_H
#define __STATE_H

#include <Pin.h>
#include <Event.h>

class State : public ListItem
{
    protected:
        char * _name;
    public:
        State(char * name);

};

#endif
