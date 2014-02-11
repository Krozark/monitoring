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
        #ifdef _WIN32
        #elif __linux        
        FILE* proc_self_status_v;
        #endif
        bool Virtual::is_init = false;

        uint64_t Virtual::total()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            res = memInfo.ullTotalPageFile;

            #elif __linux
            struct sysinfo memInfo;
            sysinfo (&memInfo);
            res = memInfo.totalram;
            //Add other values in next statement to avoid int overflow on right hand side...
            res += memInfo.totalswap;
            res *= memInfo.mem_unit;
            #endif
            return res;
        }

        #ifdef __linux 
        int Virtual::parseLine(char* line)
        {
            int i = strlen(line);
            while (*line < '0' || *line > '9') line++;
            line[i-3] = '\0';
            i = atoi(line);
            return i;
        }
        #endif


        uint64_t Virtual::used()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            res = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

            #elif __linux        
            struct sysinfo memInfo;
            sysinfo (&memInfo);
            res = memInfo.totalram - memInfo.freeram;
            //Add other values in next statement to avoid int overflow on right hand side...
            res += memInfo.totalswap - memInfo.freeswap;
            res *= memInfo.mem_unit;
            #endif
            return res;
        }
        
        uint64_t Virtual::usedByProc()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            res = pmc.PrivateUsage;

            #elif __linux
            if(not is_init)
                init();

            fseek(proc_self_status_v,0,SEEK_SET);
            char line[128];

            while (fgets(line, 128, proc_self_status_v) != NULL)
            {
                if (strncmp(line, "VmSize:", 7) == 0)
                {
                    res = parseLine(line);
                    break;
                }
            }
            res *= 1024;
            #endif
            return res;
        }

        void Virtual::init()
        {
            proc_self_status_v = fopen("/proc/self/status", "r");
            is_init = true;
        }

        void Virtual::close()
        {
            if(is_init)
            {
                is_init = false;
                fclose(proc_self_status_v);
            }
        }
    }
}
