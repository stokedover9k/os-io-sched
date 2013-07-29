#include "IOBegin.h"
#include "IOComplete.h"

namespace iosim
	{

	IOBegin::IOBegin(IOAccess* sectorAccess) :
			IOEvent(sectorAccess)
		{
		}

	void IOBegin::execute()
		{
		printTrace();

		unsigned int accessTime = accessSectorOnDisk(getSectorAccess()->getSector());
		getSectorAccess()->setCompleteTime( getTime() + accessTime );
		dispatchFollowUpEvent( new IOComplete(getSectorAccess()) );
		}

	unsigned int IOBegin::getTime() const
		{
		return this->getSectorAccess()->getBeginTime();
		}

	int IOBegin::getPriority() const
		{
		return 3;
		}

	}
