#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <cstdarg>

enum OutputMode
{
  DEBUG        = 1 << 0,
  INFO         = 1 << 1,
  TRACE        = 1 << 2,
  SUMMARY      = 1 << 3
};

////////////////////////////////////////////

template <typename OutputPolicy>
struct Printer
{
  ~Printer();

  std::ostringstream& Get(OutputMode mode);

  static unsigned int& ReportingMode();
  static long& InstructionCount();

protected:
  std::ostringstream os;
};

//------------------------------------------

template <typename OutputPolicy>
Printer<OutputPolicy>::~Printer() {
  OutputPolicy::Output( os.str() );
}

template <typename OutputPolicy>
std::ostringstream& Printer<OutputPolicy>::Get(OutputMode mode) {
  if( mode == DEBUG ) {
    os << "==> # DEBUG: ";
  }
  return os;
}

template <typename OutputPolicy>
unsigned int & Printer<OutputPolicy>::ReportingMode() {
  static unsigned int _reporting_mode = 0;
  return _reporting_mode;
}

template <typename OutputPolicy>
long & Printer<OutputPolicy>::InstructionCount() {
  static long _instruction_count = -1;
  return _instruction_count;
}

////////////////////////////////////////////

struct OutputToFile
{
  inline static void Output( const std::string& msg ) {
    FILE* pstream = Stream();
    if( pstream ) {
      fprintf(pstream, "%s\n", msg.c_str());
      fflush( pstream );
    }
  }

  inline static FILE*& Stream() {
    static FILE* pstream = stderr;
    return pstream;
  }
};

/////////////////////////////////////////////

typedef Printer<OutputToFile> OutFilePrinter;

#define OUT(mode) \
  if ( !(mode & OutFilePrinter::ReportingMode()) || !OutputToFile::Stream()) ; \
  else OutFilePrinter().Get(mode)

#endif //__OUTPUT_H__
