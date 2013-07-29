#include "IORequest.h"
#include "IOBegin.h"

namespace iosim
	{

	IORequest::IORequest(IOAccess* sectorAccess) :
			IOEvent(sectorAccess)
		{
		}

	void IORequest::execute()
		{

		enqueueIORequest( getSectorAccess() );

		if( isDiskIdle() )
  		{
  			IOAccess * sectorAccess = getNextSectorAccess();
  			sectorAccess->setBeginTime( getTime() );
  			dispatchFollowUpEvent( new IOBegin(sectorAccess) );
  		}
		}

	unsigned int IORequest::getTime() const
		{
		return this->getSectorAccess()->getRequestTime();
		}

	int IORequest::getPriority() const
		{
		return 1;
		}

	}
