#ifndef __IO_EVENTS_H__
#define __IO_EVENTS_H__

#include "event.h"

namespace des
	{

	struct IOEvent: public Event
		{
		IOEvent(unsigned int time, unsigned int sector);
		unsigned int getSector() const;

	private:
		unsigned int _sector;
		};

	template<int DefaultPriority = 0>
	struct PriorityType
		{
		int getPriority() const;

		static int& TypePriority();
		};

	struct IORequest: public IOEvent, public PriorityType<1>
		{
		IORequest(unsigned int time, unsigned int sector);

		virtual void execute();
		};

	struct IOBegin: public IOEvent, public PriorityType<2>
		{
		IOBegin(unsigned int time, unsigned int sector);

		virtual void execute();
		};

	struct IOComplete: public IOEvent, public PriorityType<3>
		{
		IOComplete(unsigned int time, unsigned int sector);

		virtual void execute();
		};

	template<int DefaultPriority>
	inline int PriorityType<DefaultPriority>::getPriority() const
		{
		return TypePriority();
		}

	template<int DefaultPriority>
	inline int& PriorityType<DefaultPriority>::TypePriority()
		{
		static int _priority = DefaultPriority;
		return _priority;
		}

	};

#endif //__IO_EVENTS_H__
