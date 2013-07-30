#ifndef __EVENT_TIME_PRIORITY_ORDER_H__
#define __EVENT_TIME_PRIORITY_ORDER_H__

namespace des
	{

	struct Event;

	struct EventTimePriorityOrder
		{
		bool operator ()(const Event* a, const Event* b);
		};

	}
;
#endif //__EVENT_TIME_PRIORITY_ORDER_H__
