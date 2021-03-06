#include <Monitoring/Cpu.hpp>

#ifdef _WIN32 //_WIN64

#include <windows.h>
#include <psapi.h>
#include <TCHAR.h>

#include <Monitoring/Win/pdh.h>

#elif __linux //|| __unix //or __APPLE__

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/times.h>
#include <sys/vtimes.h>

#else
    #error not defined for this platform
#endif

namespace sys
{
    #ifdef _WIN32
    static PDH_HQUERY cpuQuery;
    static PDH_HCOUNTER cpuTotal;
    static ULARGE_INTEGER lastCPU,
                   lastSysCPU,
                   lastUserCPU;
    static HANDLE self;
    #elif __linux
    static uint64_t lastTotalUser,
             lastTotalUserLow,
             lastTotalSys,
             lastTotalIdle;
    static clock_t lastCPU = 0,
                   lastSysCPU = 0,
                   lastUserCPU = 0;
    #endif

    int Cpu::numProcessors = 0;

    int Cpu::processors()
    {
        if(numProcessors <=0)
        {
            #ifdef _WIN32
            #elif __linux

            char line[128];
            FILE* file = fopen("/proc/cpuinfo", "r");
            numProcessors = 0;

            while(fgets(line, 128, file) != NULL)
            {
                if (strncmp(line, "processor", 9) == 0)
                    ++numProcessors;
            }
            fclose(file);
            #endif
        }
        return numProcessors;
    }

    double Cpu::used()
    {
        double res = 0.f;

        #ifdef _WIN32
        PDH_FMT_COUNTERVALUE counterVal;

        PdhCollectQueryData(cpuQuery);
        PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

        res = counterVal.doubleValue;

        #elif __linux

        double percent;
        uint64_t totalUser, totalUserLow, totalSys, totalIdle, total;

        {
            FILE* proc_stats = fopen("/proc/stat", "r");
            fscanf(proc_stats, "cpu %Ld %Ld %Ld %Ld", &totalUser, &totalUserLow, &totalSys, &totalIdle);
            fclose(proc_stats);
        }
        if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow || totalSys < lastTotalSys || totalIdle < lastTotalIdle)
        {
            //Overflow detection. Just skip this value.
            percent = -1.0;
        }
        else
        {
            total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) + (totalSys - lastTotalSys);
            percent = total;
            total += (totalIdle - lastTotalIdle);
            percent /= total;
            percent *= 100;
        }


        lastTotalUser = totalUser;
        lastTotalUserLow = totalUserLow;
        lastTotalSys = totalSys;
        lastTotalIdle = totalIdle;

        res = percent;
        #endif

        return res;
    }

    double Cpu::usedByProc()
    {
        double res = 0.f;

        #ifdef _WIN32
        {
            FILETIME ftime, fsys, fuser;
            ULARGE_INTEGER now, sys, user;
            double percent;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&now, &ftime, sizeof(FILETIME));

            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&sys, &fsys, sizeof(FILETIME));
            memcpy(&user, &fuser, sizeof(FILETIME));
            percent = (sys.QuadPart - lastSysCPU.QuadPart) +(user.QuadPart - lastUserCPU.QuadPart);
            percent /= (now.QuadPart - lastCPU.QuadPart);
            percent /= numProcessors;
            lastCPU = now;
            lastUserCPU = user;
            lastSysCPU = sys;


            res = percent * 100;
        }
        #elif __linux
        {
            struct tms timeSample;
            clock_t now;
            double percent;


            now = times(&timeSample);
            if (now <= lastCPU || timeSample.tms_stime < lastSysCPU || timeSample.tms_utime < lastUserCPU)
            {
                //Overflow detection. Just skip this value.
                percent = -1.0;
            }
            else
            {
                percent = (timeSample.tms_stime - lastSysCPU) +  (timeSample.tms_utime - lastUserCPU);
                percent /= (now - lastCPU);
                percent /= numProcessors;
                percent *= 100;
            }
            lastCPU = now;
            lastSysCPU = timeSample.tms_stime;
            lastUserCPU = timeSample.tms_utime;


            res = percent;
        }
        #endif
        return res;
    }

   /* void Cpu::init()
    {
        #ifdef _WIN32
        {
            PdhOpenQuery(NULL, NULL, &cpuQuery);
            PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
            PdhCollectQueryData(cpuQuery);
        }

        {
            SYSTEM_INFO sysInfo;
            FILETIME ftime, fsys, fuser;

            GetSystemInfo(&sysInfo);
            numProcessors = sysInfo.dwNumberOfProcessors;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&lastCPU, &ftime, sizeof(FILETIME));

            self = GetCurrentProcess();
            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
            memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
        }
        #elif __linux
        {
        }
        #endif
    }*/
}
