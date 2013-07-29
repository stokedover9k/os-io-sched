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
		strategy = new iosim::IOStrategyFIFO();

		iosim::IOEvent::dispatchFollowUpEvent = iosim::EventDispatcher(&eventQueue);
		iosim::IOEvent::enqueueIORequest = iosim::EnqueueSectorRequest(strategy);
		iosim::IOEvent::getNextSectorAccess = iosim::NextSectorRequest(strategy);
		iosim::IOEvent::isDiskIdle = iosim::DiskIdle(&disk);
		iosim::IOEvent::setDiskToIdle = iosim::DiskSetIdle(&disk);
		iosim::IOEvent::accessSectorOnDisk = iosim::AccessSector(&disk);
		iosim::IOEvent::isIORequestPending = iosim::RequestPending(strategy);
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
      accessList.push_back( iosim::IOAccess(time, track_accessed) );

      // ...
      // TODO: set up components
      // ...
      while( infile.peek() == '#' )
        std::getline(infile, line);
    }
  }

  //----------- initialize simulation ------------//
  for(auto access = accessList.begin(); access != accessList.end(); ++access)
    eventQueue.pushEvent( new iosim::IORequest( &*access ) );

  //----------- run simulation ---------------//
  {
		while( eventQueue.size() )
			{
			des::Event * e = eventQueue.popEvent();
			e->execute();
			delete e;
			}
  }
}
