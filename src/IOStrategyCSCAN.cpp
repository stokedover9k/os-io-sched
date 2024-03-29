#include "IOStrategyCSCAN.h"
#include "IOAccess.h"

namespace iosim
	{

	IOStrategyCSCAN::IOStrategyCSCAN() :
			_pending(0), _currentHead(CSCANQueue::iterator())
		{
		}

	void IOStrategyCSCAN::addIOAccessRequest(IOAccess* access)
		{
		_queue[access->getSector()].push_back(access);
		_pending++;
		}

	IOAccess* IOStrategyCSCAN::getNextIOAccessRequest()
		{
		if (_currentHead == CSCANQueue::iterator() ) // if first time = uninitialized
			_currentHead = _queue.begin();
		else if (_currentHead->second.empty())
			{
			CSCANQueue::iterator p = _currentHead;
			advanceHead();
			_queue.erase(p);
			}

		IOAccess* ret = _currentHead->second.front();
		_currentHead->second.pop_front();
		_pending--;
		return ret;
		}

	unsigned int IOStrategyCSCAN::pendingRequestCount() const
		{
		return _pending;
		}

	void IOStrategyCSCAN::advanceHead()
		{
		_currentHead++;
		if (_currentHead == _queue.end())
			// if reached end
			_currentHead = _queue.begin();
		}

	}
