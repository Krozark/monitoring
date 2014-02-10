#ifndef SYS_CPU_HPP
#define SYS_CPU_HPP

#include <stdint.h>

namespace sys
{
    /**
     * \brief A class to manage Cpu info
     */
    class Cpu
    {
        public:
            
            /**
             * \return the number of processors
             */
            static int processors();

            /**
             * \return in percent.
             */
            static double used();

            /**
             * \return in percent.
             */
            static double usedByProc();


        private:
            Cpu() = delete;
            Cpu(const Cpu&) = delete;
            Cpu& operator=(const Cpu&) = delete;
            
            static void init();

            static bool is_init;
    };
}
#endif
