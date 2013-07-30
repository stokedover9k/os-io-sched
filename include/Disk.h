#ifndef __DISK_H__
#define __DISK_H__

#include <algorithm>

namespace iosim
	{

	struct Disk
		{

		Disk();
		unsigned int accessSector(unsigned int sector);

		bool isIdle() const;
		void setIdle();
		unsigned long getTotalHeadMovement() const;

		unsigned int getCurrentSector() const;

	private:
		bool _idle;
		unsigned int _headAtSector;
		unsigned long _totalHeadMovement;
		};

	}
;

#endif //__DISK_H__
