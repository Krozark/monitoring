#ifndef SYS_SYS_HPP
#define SYS_SYS_HPP

#include <Monitoring/Cpu.hpp>
#include <Monitoring/Physical.hpp>
#include <Monitoring/Virtual.hpp>

#include <string>

// Check windows
#if _WIN32 || _WIN64
   #if _WIN64
     #define SYS_64BIT
  #else
    #define SYS_32BIT
  #endif
#endif

// Check GCC
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define SYS_64BIT
  #else
    #define SYS_32BIT
  #endif
#endif

namespace sys
{
    std::string osName();
    std::string osNameBit();
    int osBit();
    bool checkBit();
}

#endif
