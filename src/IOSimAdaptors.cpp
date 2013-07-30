#include "IOSimAdaptors.h"
#include "EventQueue.h"
#include "IOStrategy.h"
#include "Disk.h"

namespace iosim
	{

	EventDispatcher::EventDispatcher(des::EventQueue* eventQueue) :
			_eventQueue(eventQueue)
		{
		}

	void EventDispatcher::operator ()(des::Event* event)
		{
		_eventQueue->pushEvent(event);
		}

	EnqueueSectorRequest::EnqueueSectorRequest(IOStrategy* strategy) :
			_strategy(strategy)
		{
		}

	void EnqueueSectorRequest::operator ()(IOAccess* a)
		{
		_strategy->addIOAccessRequest(a);
		}

	NextSectorRequest::NextSectorRequest(IOStrategy* strategy) :
			_strategy(strategy)
		{
		}

	IOAccess* NextSectorRequest::operator ()()
		{
		return _strategy->getNextIOAccessRequest();
		}

	DiskIdle::DiskIdle(Disk* disk) :
			_disk(disk)
		{
		}

	bool DiskIdle::operator ()()
		{
		return _disk->isIdle();
		}

	DiskSetIdle::DiskSetIdle(Disk* disk) :
			_disk(disk)
		{
		}

	void DiskSetIdle::operator ()()
		{
		return _disk->setIdle();
		}

	AccessSector::AccessSector(Disk* disk) :
			_disk(disk)
		{
		}

	unsigned int AccessSector::operator ()(unsigned int sector)
		{
		return _disk->accessSector(sector);
		}

	RequestPending::RequestPending(IOStrategy* strategy) :
			_strategy(strategy)
		{
		}

	bool RequestPending::operator ()()
		{
		return _strategy->pendingRequestCount() != 0;
		}

	DiskHeadAtSector::DiskHeadAtSector(Disk* disk) :
			_disk(disk)
		{
		}

	unsigned int DiskHeadAtSector::operator ()()
		{
		return _disk->getCurrentSector();
		}

	}
