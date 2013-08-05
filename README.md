os-io-sched
===========

IO Scheduling lab for Franke's OS course

COMPILE
==========================
To compile the IO scheduling simulator, execute the following (assuming that you've already extracted the archive, via e.g. tar -zxvf io-sched.tar.gz) in the directory containing os-io-sched/:

mkdir build
cd build
cmake -D CMAKE_CXX_COMPILER=g++ ../os-io-sched
make

USAGE
==========================
The main executable created by the commands described above is called "iosched".

Usage: ./iosched [-v] -s<schedalgo> <inputfile>
where
  -v is an optional verbose flag (to produce *_long output),
  -s is the scheduling algorithm flag followed by one of these values: 
    * C     C-SCAN
    * f     FIFO
    * F     F-SCAN
    * s     SSTF
    * S     SCAN

Additionally, an executable "iosched_test" will be produced. This program runs unit tests.

-----------
To import into Eclipse, create a directory as a sibling to the project directory and cd into it. Assuming that the root project directory is "os-io-sched", execute:

cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../os-io-sched
