#include "Disk.h"

namespace iosim
	{

	Disk::Disk() :
			_idle(true), _headAtSector(0), _totalHeadMovement(0)
		{
		}

	unsigned int Disk::accessSector(unsigned int sector)
		{
		_idle = false;
		unsigned int dif = std::max(_headAtSector, sector)
				- std::min(_headAtSector, sector);
		_headAtSector = sector;
		_totalHeadMovement += dif;

		return dif;  // really, return timeToScan(dif); but 1:1
		}

	bool Disk::isIdle() const
		{
		return _idle;
		}

	void Disk::setIdle()
		{
		_idle = true;
		}

	unsigned long Disk::getTotalHeadMovement() const
		{
		return _totalHeadMovement;
		}

	unsigned int Disk::getCurrentSector() const
		{
		return _headAtSector;
		}

	}
