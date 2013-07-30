#include "IOAccess.h"

namespace iosim
	{

	IOAccess::IOAccess(unsigned int id, unsigned int sector, unsigned int requestTime) :
			_id(id), _sector(sector), _requestTime(requestTime), _beginTime(0), _completeTime(0)
		{
		}

	unsigned int IOAccess::getRequestTime() const
		{
		return _requestTime;
		}

	unsigned int IOAccess::getBeginTime() const
		{
		return _beginTime;
		}

	void IOAccess::setBeginTime(unsigned int beginTime)
		{
		_beginTime = beginTime;
		}

	unsigned int IOAccess::getCompleteTime() const
		{
		return _completeTime;
		}

	void IOAccess::setCompleteTime(unsigned int completeTime)
		{
		_completeTime = completeTime;
		}

	unsigned int IOAccess::getSector() const
		{
		return _sector;
		}

	unsigned int IOAccess::getId() const
		{
		return _id;
		}

	}
