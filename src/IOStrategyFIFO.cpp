#include "IOStrategyFIFO.h"

namespace iosim
	{

	IOStrategyFIFO::IOStrategyFIFO()
		{
		}

	void IOStrategyFIFO::addIOAccessRequest(IOAccess* access)
		{
		queue.push_back(access);
		}

	IOAccess* IOStrategyFIFO::getNextIOAccessRequest()
		{
		IOAccess* a = queue.front();
		queue.pop_front();
		return a;
		}

	unsigned int IOStrategyFIFO::pendingRequestCount() const
		{
		return queue.size();
		}
	}
