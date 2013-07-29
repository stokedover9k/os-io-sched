#ifndef __IO_REQUEST_H__
#define __IO_REQUEST_H__

#include "IOEvent.h"

namespace iosim
	{

	struct IORequest: public IOEvent
		{

		IORequest(IOAccess* sectorAccess);

		virtual void execute();

		virtual unsigned int getTime() const;

		virtual int getPriority() const;

		};

	}
;

#endif //__IO_REQUEST_H__
