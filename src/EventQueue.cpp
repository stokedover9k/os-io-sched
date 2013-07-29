#include "EventQueue.h"
#include "Event.h"

namespace des
	{

	bool EventTimePriorityOrder::operator()(const Event* a, const Event* b)
		{
		return
				a->getTime() == b->getTime() ?
						(a->getPriority() < b->getPriority()) :
						(a->getTime() < b->getTime());
		}

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
