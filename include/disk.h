#ifndef __DISK_H__
#define __DISK_H__

#include <algorithm>

namespace iosim
  {

  struct Disk
    {

    Disk() : _idle(true), _headAtSector(0) { }
    unsigned int accessSector(unsigned int sector)
      {
      _idle = false;
      unsigned int dif = std::max(_headAtSector, sector) - std::min(_headAtSector, sector);
      _headAtSector = sector;
      return dif;
      }

    bool isIdle() const { return _idle; }
    void setIdle() { _idle = true; }

  private:
    bool _idle;
    unsigned int _headAtSector;
    };

  };

#endif //__DISK_H__
