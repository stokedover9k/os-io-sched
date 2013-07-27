#ifndef __IO_EVENTS_H__
#define __IO_EVENTS_H__

#include "event.h"
#include <functional>

namespace iosim
	{

  using namespace des;

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

	/*
	 * Incoming request for IO
	 */
	struct IORequest: public IOEvent, public PriorityType<1>
		{
		IORequest(unsigned int time, unsigned int sector);

		virtual void execute();

		static std::function<bool(void)> & isDiskIdleChecker();
		};

	/*
	 * Disk begins to satisfy a previous IO request.
	 */
	struct IOBegin: public IOEvent, public PriorityType<2>
		{
		IOBegin(unsigned int time, unsigned int sector);

		virtual void execute();
		};

	/*
	 * Disk completes the satisfaction of a previous IO request.
	 */
	struct IOComplete: public IOEvent, public PriorityType<3>
		{
		IOComplete(unsigned int time, unsigned int sector);

		virtual void execute();

		static std::function<bool(void)> & isIORequestPendingChecker();
		};

	/*
	 * IO request to satisfy is chosen and a disk access is issued.
	 */
  struct IODispatch: public Event, public PriorityType<3>
    {
		IODispatch(unsigned int time);

		virtual void execute();
    };

  //------------------------------------------------------------------------

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
