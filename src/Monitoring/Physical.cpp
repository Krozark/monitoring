#include <Monitoring/Physical.hpp>
#include <Monitoring/Virtual.hpp>

#ifdef _WIN32 //_WIN64

#include <windows.h>
#include <psapi.h>

#elif __linux //|| __unix //or __APPLE__

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#else
    #error not defined for this platform
#endif

namespace sys
{
    namespace memory
    {
        uint64_t Physical::total()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            res = memInfo.ullTotalPhys;

            #elif __linux        
            struct sysinfo memInfo;

            sysinfo (&memInfo);
            res = memInfo.totalram;
            //Multiply in next statement to avoid int overflow on right hand side...
            res *= memInfo.mem_unit;
            #endif
            return res;
        }

        uint64_t Physical::used()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            res = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
            
            #elif __linux        
            struct sysinfo memInfo;

            sysinfo (&memInfo);
            res = memInfo.totalram - memInfo.freeram;
            //Multiply in next statement to avoid int overflow on right hand side...
            res *= memInfo.mem_unit;
            #endif
            return res;
        }

        uint64_t Physical::usedByProc()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            res = pmc.WorkingSetSize;

            #elif __linux        
            FILE* proc_self_status = fopen("/proc/self/status", "r");
            char line[128];

            while (fgets(line, 128, proc_self_status) != NULL)
            {
                if (strncmp(line, "VmRSS:", 6) == 0)
                {
                    printf("%s",line);
                    res = Virtual::parseLine(line);
                    break;
                }
            }
            fclose(proc_self_status);
            res*=1024;
            #endif
            return res;
        }
    }
}
