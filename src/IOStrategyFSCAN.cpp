#include "IOStrategyFSCAN.h"

namespace iosim
	{

	void ScanWithSetHead::addBucket(unsigned int sector)
		{
		_queue[sector];
		}

	void ScanWithSetHead::setCurrentHead(unsigned int sector)
		{
		_currentHead = _queue.find(sector);
		}

	void ScanWithSetHead::eraseLastAccess()
		{
		if (_currentHead->second.empty())
			_queue.erase(_currentHead);

		_currentHead = CSCANQueue::iterator();
		}

	void ScanWithSetHead::setDirection(bool directionForward)
		{
		forward = directionForward;
		}

	bool ScanWithSetHead::directionForward() const
		{
		return forward;
		}

	unsigned int ScanWithSetHead::getLastAccess() const
		{
		return _currentHead->first;
		}

	bool ScanWithSetHead::currentHeadValid() const
		{
		return _currentHead != CSCANQueue::iterator();
		}

	IOStrategyFSCAN::IOStrategyFSCAN() :
			activeQueue(&q1)
		{
		}

	void IOStrategyFSCAN::addIOAccessRequest(IOAccess* access)
		{
		bufferingQueue()->addIOAccessRequest(access);
		}

	IOAccess* IOStrategyFSCAN::getNextIOAccessRequest()
		{
		if (activeQueue->pendingRequestCount() == 0)
			{
			if (activeQueue->currentHeadValid())
				{
				unsigned int sector = activeQueue->getLastAccess();
				activeQueue->eraseLastAccess();
				bufferingQueue()->addBucket(sector);
				bufferingQueue()->setCurrentHead(sector);
				//              bufferingQueue()->setDirection(activeQueue->directionForward());
				bufferingQueue()->setDirection(true);
				}
			switchQueues();
			}
		return activeQueue->getNextIOAccessRequest();
		}

	unsigned int IOStrategyFSCAN::pendingRequestCount() const
		{
		return q1.pendingRequestCount() + q2.pendingRequestCount();
		}

	ScanWithSetHead* IOStrategyFSCAN::bufferingQueue()
		{
		return activeQueue == &q1 ? &q2 : &q1;
		}

	void IOStrategyFSCAN::switchQueues()
		{
		activeQueue = bufferingQueue();
		}

	}
