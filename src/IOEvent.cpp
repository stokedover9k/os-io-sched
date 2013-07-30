#include "IOEvent.h"

namespace iosim
	{

	std::function<void(des::Event*)>          IOEvent::dispatchFollowUpEvent;
	std::function<void(IOAccess*)>            IOEvent::enqueueIORequest;
	std::function<IOAccess *(void)>           IOEvent::getNextSectorAccess;
	std::function<bool(void)>                 IOEvent::isDiskIdle;
	std::function<unsigned int(unsigned int)> IOEvent::accessSectorOnDisk;
	std::function<bool(void)>                 IOEvent::isIORequestPending;
	std::function<void(void)>                 IOEvent::setDiskToIdle;
	std::function<unsigned int(void)>         IOEvent::diskHeadAtSector;

	IOEvent::IOEvent(IOAccess* sectorAccess) :
			_sectorAccess(sectorAccess)
		{
		}

	unsigned int IOEvent::getSector() const
		{
		return _sectorAccess->getSector();
		}

	}
