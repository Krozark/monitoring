#include <Monitoring/sys.hpp>

#include <iostream>


namespace sys
{
    std::string osName()
    {
        #ifdef _WIN32
        return "Windows";
        #elif _WIN64
        return "Windows";
        #elif __unix || __unix__
        return "Unix";
        #elif __APPLE__ || __MACH__
        return "MacOSX";
        #elif __linux__
        return "Linux";
        #elif __FreeBSD__
        return "FreeBSD";
        #else
        return "Unknow";
        #endif
    }

    std::string osNameBit()
    {
        return osName()+"-x"+std::to_string(osBit());
    }

    int osBit()
    {
        #if defined(SYS_64BIT)
            return 64;
        #elif defined (SYS_32BIT)
            return 32;
        #else
            #error "Must define either SYS_32BIT or SYS_64BIT"
        #endif
    }

    bool checkBit()
    {
        bool res = true;
        #if defined(SYS_64BIT)
        if (sizeof(void*) != 8)
        {
            std::cerr<<"SYS_64BIT: Error: pointer should be 8 bytes."<<std::endl;
            res = false;
        }
        #elif defined (SYS_32BIT)
        if (sizeof(void*) != 4)
        {
            std::cerr<<"SYS_32BIT: Error: pointer should be 4 bytes."<<std::endl;
            res = false;
        }
        #else
            #error "Must define either SYS_32BIT or SYS_64BIT".
        #endif
        return res;
    }
}
