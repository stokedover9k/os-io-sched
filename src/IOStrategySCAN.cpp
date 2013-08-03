#include "IOStrategySCAN.h"
namespace iosim
	{

	IOStrategySCAN::IOStrategySCAN() :
			IOStrategyCSCAN(), forward(true)
		{
		}

	void IOStrategySCAN::advanceHead()
		{
		if (forward)
			{
			++_currentHead;
			if (_currentHead == _queue.end())
				{
				forward = false;
				--_currentHead;
				--_currentHead;
				}
			}
		else // if back (!forward)
			{
			if (_currentHead == _queue.begin())
				{
				forward = true;
				++_currentHead;
				}
			else
				--_currentHead;
			}
		}

	}
