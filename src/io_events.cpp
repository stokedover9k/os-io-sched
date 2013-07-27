#include "io_events.h"
#include "output.h"
#include <iomanip>

namespace iosim
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

	std::function<bool(void)> & IORequest::isDiskIdleChecker()
		{
		static std::function<bool(void)> _idleDiskChecker;
		return _idleDiskChecker;
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

	std::function<bool(void)> & IOComplete::isIORequestPendingChecker()
		{
		static std::function<bool(void)> _pendingRequestChecker;
		return _pendingRequestChecker;
		}

	IODispatch::IODispatch(unsigned int time) :
			Event(time)
		{
		}

	void IODispatch::execute()
		{
		}

	}
