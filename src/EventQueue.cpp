#include "EventQueue.h"
#include "Event.h"

namespace des
	{

	void EventQueue::pushEvent(Event *e)
		{
		queue.insert(e);
		}

	Event * EventQueue::popEvent()
		{
		Event * e = *queue.begin();
		queue.erase(queue.begin());
		return e;
		}

	unsigned int EventQueue::size() const
		{
		return queue.size();
		}

	}
