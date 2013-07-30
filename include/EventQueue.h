#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__ 

#include "EventTimePriorityOrder.h"
#include <set>

namespace des
	{

	struct EventQueue
		{
		void pushEvent(Event* e);

		Event * popEvent();

		unsigned int size() const;

	private:
		std::multiset<Event *, EventTimePriorityOrder> queue;
		};

	}
;

#endif //__EVENT_QUEUE_H__
