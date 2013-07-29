/*
 * IOStrategyFIFO.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: yuriy
 */

#include "IOStrategyFIFO.h"

namespace iosim
	{

	IOStrategyFIFO::IOStrategyFIFO()
		{
		}

	void IOStrategyFIFO::addIOAccessRequest(IOAccess* access)
		{
		queue.push_back(access);
		}

	IOAccess* IOStrategyFIFO::getNextIOAccessRequest()
		{
		IOAccess* a = queue.front();
		queue.pop_front();
		return a;
		}

	} /* namespace iosim */
