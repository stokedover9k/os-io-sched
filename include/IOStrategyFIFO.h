
#ifndef __IO_STRATEGY_FIFO_H__
#define __IO_STRATEGY_FIFO_H__

#include "IOStrategy.h"
#include <list>

namespace iosim
	{
	struct IOAccess;

	struct IOStrategyFIFO: public iosim::IOStrategy
		{
		IOStrategyFIFO();

		void addIOAccessRequest(IOAccess* access);

		IOAccess* getNextIOAccessRequest();

		private:
			std::list<IOAccess *> queue;
		};

	}
;
#endif //__IO_STRATEGY_FIFO_H__
