#ifndef __IO_STRATEGY_SCAN_H__
#define __IO_STRATEGY_SCAN_H__

#include "IOStrategyCSCAN.h"

namespace iosim
	{
	struct IOStrategySCAN: public IOStrategyCSCAN
		{
		IOStrategySCAN();

	protected:

		virtual void advanceHead();

	private:
		bool forward;
		};

	}

#endif //__IO_STRATEGY_SCAN_H__
