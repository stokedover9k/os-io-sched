#include <libio.h>
#include <list>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#include "output.h"
#include "IOAccess.h"
#include "IORequest.h"
#include "EventQueue.h"
#include "Event.h"
#include "Disk.h"
#include "IOStrategy.h"
#include "IOStrategyFIFO.h"
#include "IOStrategySSTF.h"
#include "IOSimAdaptors.h"

#define __MAIN_IO_SCHED__
#include "Main.h"

//================== MAIN =====================//

int main(int argc, char *argv[])
{
  using namespace std;

  OutputToFile::Stream() = stdout;
  OutFilePrinter::ReportingMode() = SUMMARY|TRACE|INFO|DEBUG;

  //------------ parse arguments -------------//
  try { parse_args(argc, argv); }
  catch (std::invalid_argument const& ia) {
    cerr << "Error (INVALID ARGUMENT): " << ia.what() << "\n\t" << USAGE_STR << '\n';
    exit(1); }

  //------------ set up input stream ---------//
  ifstream infile(PARAMS::inputfile);
  if( !infile ) {
    cerr << "Error: could not open input file" << "\n\t" << USAGE_STR << '\n';
    exit(2);
  }

  //----------- set up components ---------------//
  des::EventQueue eventQueue;
  iosim::Disk disk;
  iosim::IOStrategy * strategy;
  {
		switch(PARAMS::schedalgo)
			{
		case 'f':  strategy = new iosim::IOStrategyFIFO();   break;
		case 's':  strategy = new iosim::IOStrategySSTF(0);  break;
		default:
			cerr << "Error: unknown scheduling algorithm requested - " << PARAMS::schedalgo << ".\n";
			exit(3);
			}



		iosim::IOEvent::dispatchFollowUpEvent = iosim::EventDispatcher(&eventQueue);
		iosim::IOEvent::enqueueIORequest = iosim::EnqueueSectorRequest(strategy);
		iosim::IOEvent::getNextSectorAccess = iosim::NextSectorRequest(strategy);
		iosim::IOEvent::isDiskIdle = iosim::DiskIdle(&disk);
		iosim::IOEvent::setDiskToIdle = iosim::DiskSetIdle(&disk);
		iosim::IOEvent::accessSectorOnDisk = iosim::AccessSector(&disk);
		iosim::IOEvent::isIORequestPending = iosim::RequestPending(strategy);
		iosim::IOEvent::diskHeadAtSector = iosim::DiskHeadAtSector(&disk);
  }

  //----------- initialize access request list ---------------//
  std::list<iosim::IOAccess> accessList;
  {
    string line;
    int time, track_accessed;

    while( infile.peek() == '#' )
      std::getline(infile, line);

    while( infile >> time >> track_accessed )
    {
      accessList.push_back( iosim::IOAccess(accessList.size(), track_accessed, time) );

      while( infile.peek() == '#' )
        std::getline(infile, line);
    }
  }

  //----------- initialize simulation ------------//
  for(auto access = accessList.begin(); access != accessList.end(); ++access)
    eventQueue.pushEvent( new iosim::IORequest( &*access ) );

  //----------- run simulation ---------------//
  {
  	OUT(TRACE) << "TRACE";
		while( eventQueue.size() )
			{
			des::Event * e = eventQueue.popEvent();
			e->execute();
			delete e;
			}
  }

  //----------- collect IO statistics and print IO Requests summary ----------//
	OUT(TRACE) << "IOREQS INFO";
	{
		unsigned int total_time = 0;
		unsigned long total_turnaround = 0;
		unsigned long total_wait = 0;
		unsigned int max_wait = 0;
		unsigned long total_movement = disk.getTotalHeadMovement();

		for( auto a = accessList.begin(); a != accessList.end(); a++ )
		{
			OUT(TRACE) << std::setw(5) << a->getId() << ": "
								 << std::setw(5) << a->getRequestTime() << ' '
								 << std::setw(5) << a->getBeginTime() << ' '
								 << std::setw(5) << a->getCompleteTime();

			total_time = std::max( a->getCompleteTime(), total_time );
			total_turnaround += a->getCompleteTime() - a->getRequestTime();
			total_wait += a->getBeginTime() - a->getRequestTime();
			max_wait = std::max( a->getBeginTime() - a->getRequestTime(), max_wait );
		}

		double avg_turnaround = static_cast<double>(total_turnaround) / accessList.size();
		double avg_wait = static_cast<double>(total_wait) / accessList.size();

		OUT(SUMMARY) << std::fixed << std::setprecision(2)
		             << "SUM: "
				         << total_time + 1 << ' '
				         << total_movement << ' '
				         << avg_turnaround << ' '
				         << avg_wait << ' '
				         << max_wait;
	}
}
