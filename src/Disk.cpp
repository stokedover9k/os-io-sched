#include "Disk.h"

namespace iosim
	{

	Disk::Disk() :
			_idle(true), _headAtSector(0)
		{
		}

	unsigned int Disk::accessSector(unsigned int sector)
		{
		_idle = false;
		unsigned int dif = std::max(_headAtSector, sector)
				- std::min(_headAtSector, sector);
		_headAtSector = sector;
		return dif;
		}

	bool Disk::isIdle() const
		{
		return _idle;
		}

	void Disk::setIdle()
		{
		_idle = true;
		}

	}
