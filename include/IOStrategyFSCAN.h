#ifndef __IO_STRATEGY_FSCAN_H__
#define __IO_STRATEGY_FSCAN_H__

#include "IOStrategySCAN.h"

namespace iosim
	{

	struct ScanWithSetHead: public IOStrategySCAN
		{
		void addBucket(unsigned int sector);

		void setCurrentHead(unsigned int sector);

		void eraseLastAccess();

		void setDirection(bool directionForward);

		bool directionForward() const;

		unsigned int getLastAccess() const;

		bool currentHeadValid() const;
		};

	struct IOStrategyFSCAN: public IOStrategy
		{
		IOStrategyFSCAN();

		virtual void addIOAccessRequest(IOAccess* access);

		virtual IOAccess* getNextIOAccessRequest();

		virtual unsigned int pendingRequestCount() const;

	private:
		ScanWithSetHead* bufferingQueue();

		void switchQueues();

		ScanWithSetHead q1, q2;
		ScanWithSetHead * activeQueue;
		};

	}

#endif //__IO_STRATEGY_FSCAN_H__
