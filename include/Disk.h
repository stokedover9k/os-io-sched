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

	private:
		bool _idle;
		unsigned int _headAtSector;
		};

	}
;

#endif //__DISK_H__
