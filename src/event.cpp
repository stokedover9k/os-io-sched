#include "event.h"

namespace des
{

Event::Event(unsigned int time) 
  : _time(time)
{ }

Event::~Event()
{ }

unsigned int Event::getTime() const
{
  return _time;
}

int Event::getPriority() const
{
  return 0;
}

}

