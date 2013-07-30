#include "EventTimePriorityOrder.h"

#include "Event.h"

namespace des
	{

	bool EventTimePriorityOrder::operator ()(const Event* a, const Event* b)
		{
		return
				a->getTime() == b->getTime() ?
						(a->getPriority() < b->getPriority()) :
						(a->getTime() < b->getTime());
		}

	}
