#ifndef __IO_STRATEGY_SSTF_H__
#define __IO_STRATEGY_SSTF_H__

#include "IOStrategy.h"
#include <map>
#include <list>

namespace iosim
	{
	struct IOAccess;

	struct IOStrategySSTF: public iosim::IOStrategy
		{
		IOStrategySSTF(unsigned int startSector = 0);

		void addIOAccessRequest(IOAccess* access);

		IOAccess* getNextIOAccessRequest();

		virtual unsigned int pendingRequestCount() const;

	private:
		typedef unsigned int SectorKey;
		typedef std::list<IOAccess*> SSTFBucket;
		typedef std::map<SectorKey, SSTFBucket> SSTFQueue;

		SSTFQueue _queue;
		SSTFQueue::iterator _currentHead;
		unsigned int _pending;
		};

	}
;
#endif //__IO_STRATEGY_SSTF_H__
