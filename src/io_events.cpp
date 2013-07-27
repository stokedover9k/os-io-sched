#include "io_events.h"
#include "output.h"
#include <iomanip>

namespace des
	{
	void outputEvent(IOEvent * e, char const * eventType)
		{
		OUT(TRACE) << e->getTime() << ": "
				<< std::setw(5) << eventType
				<< ' ' << e->getSector();
		}

	IOEvent::IOEvent(unsigned int time, unsigned int sector) :
			Event(time), _sector(sector)
		{
		}

	unsigned int IOEvent::getSector() const
		{
		return _sector;
		}

	IORequest::IORequest(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IORequest::execute()
		{
		outputEvent(this, "add");
		}

	IOBegin::IOBegin(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IOBegin::execute()
		{
		outputEvent(this, "issue");
		}

	IOComplete::IOComplete(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IOComplete::execute()
		{
		outputEvent(this, "finish");
		}

	}
