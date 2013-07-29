#ifndef __IO_STRATEGY_H__
#define __IO_STRATEGY_H__

namespace iosim
	{
	struct IOAccess;

	struct IOStrategy
		{
		virtual ~IOStrategy();
		virtual void addIOAccessRequest(IOAccess *access) = 0;
		virtual IOAccess * getNextIOAccessRequest() = 0;
		};

	}
;

#endif //__IO_STRATEGY_H__
