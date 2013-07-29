#ifndef __IO_EVENT_H__
#define __IO_EVENT_H__

#include "Event.h"
#include "IOAccess.h"
#include <functional>

namespace iosim
	{

	struct IOEvent: public des::Event
		{
		IOEvent(IOAccess* sectorAccess);

		unsigned int getSector() const;

		static std::function<void(Event*)> dispatchFollowUpEvent;
		static std::function<void(unsigned int)> enqueueIORequest;
		static std::function<IOAccess *(void)> getNextSectorAccess;
		static std::function<bool(void)> isDiskIdle;
		static std::function<unsigned int(unsigned int)> accessSectorOnDisk;
		static std::function<bool(void)> isIORequestPending;
		static std::function<void(void)> setDiskToIdle;

	protected:
		IOAccess * getSectorAccess() const { return _sectorAccess; }

	private:
		IOAccess * _sectorAccess;
		};

	}
;

#endif //__IO_EVENT_H__
