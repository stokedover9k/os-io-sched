#include "io_events.h"

namespace des
	{

	IOEvent::IOEvent(unsigned int time, unsigned int sector) :
			Event(time), _sector(sector)
		{
		}

	IORequest::IORequest(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IORequest::execute()
		{
		}

	IOBegin::IOBegin(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IOBegin::execute()
		{
		}

	IOComplete::IOComplete(unsigned int time, unsigned int sector) :
			IOEvent(time, sector)
		{
		}

	void IOComplete::execute()
		{
		}

	}
