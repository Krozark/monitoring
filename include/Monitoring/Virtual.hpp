#ifndef SYS_MEMORY_HPP
#define SYS_MEMORY_HPP

#include <stdint.h>

namespace sys
{
    namespace memory
    {
        /**
         * \brief a class to get the virtual memory info.
         */
        class Virtual
        {
            public:
                /**
                 * \return in bytes.
                 */
                static uint64_t total();

                /**
                 * \return in bytes.
                 */
                static uint64_t used();

                /**
                 * \return in bytes.
                 */
                static uint64_t usedByProc();

                static void close();

            private:
                friend class Physical;

                Virtual() = delete;
                Virtual(const Virtual&) = delete;
                Virtual& operator=(const Virtual&) = delete;

                #ifdef __linux 
                static int parseLine(char* line);
                #endif

                static void init();
                static bool is_init;

        };
    }
}
#endif
