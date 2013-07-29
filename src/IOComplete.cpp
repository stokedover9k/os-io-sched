#include "IOComplete.h"
#include "IOBegin.h"

namespace iosim
  {

  IOComplete::IOComplete(IOAccess* sectorAccess) :
      IOEvent(sectorAccess)
    {
    }

  void IOComplete::execute()
    {
  	printTrace();

    setDiskToIdle();

    if( isIORequestPending() )
      {
      IOAccess * sectorAccess = getNextSectorAccess();
      sectorAccess->setBeginTime( getTime() );
      dispatchFollowUpEvent( new IOBegin(sectorAccess) );
      }
    }

  unsigned int IOComplete::getTime() const
    {
    return this->getSectorAccess()->getCompleteTime();
    }

  int IOComplete::getPriority() const
    {
    return 2;
    }

  }
