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
  // ...
  // TODO: set up components
  // ...

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

      while( infile.peek() == '#' )
        std::getline(infile, line);
    }
  }

  //----------- initialize simulation ------------//
  des::EventQueue eventQueue;

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
