#include "IOStrategySSTF.h"
#include "IOAccess.h"

#include <climits>
#include <algorithm>

namespace iosim
	{

	IOStrategySSTF::IOStrategySSTF(unsigned int startSector) :
			_pending(0)
		{
		_queue[startSector]; // add a dummy element for current head
		_currentHead = _queue.begin();
		}

	void IOStrategySSTF::addIOAccessRequest(IOAccess* access)
		{
		_pending++;
		_queue[access->getSector()].push_back(access);
		}

	IOAccess* IOStrategySSTF::getNextIOAccessRequest()
		{
		if (_currentHead->second.empty())
			{
			unsigned int previousDistance = UINT_MAX;
			auto previous = _currentHead;
			if (_currentHead != _queue.begin())
				{
				previous--;
				previousDistance = std::max(_currentHead->first, previous->first)
						- std::min(_currentHead->first, previous->first);
				}

			unsigned int nextDistance = UINT_MAX;
			auto next = _currentHead;
			next++;
			if (next != _queue.end())
				{
				nextDistance = std::max(_currentHead->first, next->first)
						- std::min(_currentHead->first, next->first);
				}

			_queue.erase(_currentHead);
			_currentHead = (previousDistance <= nextDistance) ? previous : next;
			}

		IOAccess* ret = _currentHead->second.front();
		_currentHead->second.pop_front();
		_pending--;
		return ret;
		}

	unsigned int IOStrategySSTF::pendingRequestCount() const
		{
		return _pending;
		}

	}
