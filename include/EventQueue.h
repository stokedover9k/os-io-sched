#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__ 

#include "Event.h"
#include <set>
#include <iostream>
#include <sstream>

namespace des
{

//  struct Event;



  struct EventTimePriorityOrder
  {
    bool operator ()(const Event* a, const Event* b);
  };



  struct EventQueue
  {
    void pushEvent(Event* e);

    Event * popEvent();

    unsigned int size() const;
    
  private:
    std::multiset<Event *, EventTimePriorityOrder> queue;
  };

};

#endif //__EVENT_QUEUE_H__
