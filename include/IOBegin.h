#ifndef __IO_BEGIN_H__
#define __IO_BEGIN_H__

#include "IOEvent.h"

namespace iosim
	{

	struct IOBegin: public IOEvent
		{

		IOBegin(IOAccess* sectorAccess);

		virtual void execute();  // TODO:

		virtual unsigned int getTime() const;

		virtual int getPriority() const;

	protected:
		virtual void printTrace() const;
		};

	}
;

#endif //__IO_BEGIN_H__
