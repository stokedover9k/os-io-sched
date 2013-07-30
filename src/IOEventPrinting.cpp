#include "IOEvent.h"
#include "IORequest.h"
#include "IOBegin.h"
#include "IOComplete.h"

#include "output.h"
#include <iomanip>

namespace iosim
	{
	void IOEvent::printTrace() const
		{
		OUT(TRACE) << "IOEvent<" << getTime() << ' ' << getSector() << '>';
		}

	void IORequest::printTrace() const
		{
		OUT(TRACE) << getTime() << ": "
				<< std::setw(5) << getSectorAccess()->getId()
				<< " add " << getSectorAccess()->getSector();
		}

	void IOBegin::printTrace() const
	{
		OUT(TRACE) << getTime() << ": "
				<< std::setw(5) << getSectorAccess()->getId()
		    << " issue " << getSectorAccess()->getSector()
		    << ' ' << diskHeadAtSector();
	}

	void IOComplete::printTrace() const
	{
		OUT(TRACE) << getTime() << ": "
		<< std::setw(5) << getSectorAccess()->getId()
		<< " finish " << (getTime() - getSectorAccess()->getRequestTime());
	}

	}
;
