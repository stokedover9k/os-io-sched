#ifndef __IO_STRATEGY_CSCAN_H__
#define __IO_STRATEGY_CSCAN_H__

#include "IOStrategy.h"
#include <list>
#include <map>

namespace iosim
	{
	struct IOAccess;

	struct IOStrategyCSCAN: public iosim::IOStrategy
		{
		IOStrategyCSCAN();

		void addIOAccessRequest(IOAccess* access);

		IOAccess* getNextIOAccessRequest();

		virtual unsigned int pendingRequestCount() const;

	protected:
		typedef unsigned int SectorKey;
		typedef std::list<IOAccess*> CSCANBucket;
		typedef std::map<SectorKey, CSCANBucket> CSCANQueue;

		virtual void advanceHead();

	private:
		unsigned int _pending;
	protected:
		CSCANQueue _queue;
		CSCANQueue::iterator _currentHead;
		};

	}

#endif //__IO_STRATEGY_CSCAN_H__
