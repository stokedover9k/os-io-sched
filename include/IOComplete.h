#ifndef __IO_COMPLETE_H__
#define __IO_COMPLETE_H__

#include "IOEvent.h"

namespace iosim
  {

  struct IOComplete: public IOEvent
    {

    IOComplete(IOAccess* sectorAccess);

    virtual void execute();  // TODO:

    virtual unsigned int getTime() const;

    virtual int getPriority() const;

    };

  }
;

#endif //__IO_COMPLETE_H__
