#include "IOEvent.h"

namespace iosim
	{

	std::function<void(des::Event*)>          IOEvent::dispatchFollowUpEvent;
	std::function<void(unsigned int)>         IOEvent::enqueueIORequest;
	std::function<IOAccess *(void)>           IOEvent::getNextSectorAccess;
	std::function<bool(void)>                 IOEvent::isDiskIdle;
	std::function<unsigned int(unsigned int)> IOEvent::accessSectorOnDisk;
	std::function<bool(void)>                 IOEvent::isIORequestPending;
	std::function<void(void)>                 IOEvent::setDiskToIdle;

	IOEvent::IOEvent(IOAccess* sectorAccess) :
			_sectorAccess(sectorAccess)
		{
		}

	unsigned int IOEvent::getSector() const
		{
		return _sectorAccess->getSector();
		}

	}