#include <libio.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#include "output.h"

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

  //----------- run simulation ---------------//
  {
    string line;
    int time, track_accessed;

    while( infile.peek() == '#' )
      std::getline(infile, line);

    while( infile >> time >> track_accessed )
    {
      ////////////////////
      //  SIMULATION... //
      ////////////////////

      while( infile.peek() == '#' )
        std::getline(infile, line);
    }
  }
}
