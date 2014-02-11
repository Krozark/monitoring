#ifndef SYS_MEMORY_PHYSICAL_HPP
#define SYS_MEMORY_PHYSICAL_HPP

#include <stdint.h>

namespace sys
{
    namespace memory
    {
        /**
        * \brief A class to get the physical memory (RAM) infos
        */
        class Physical
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
                Physical() = delete;
                Physical(const Physical&) = delete;
                Physical& operator=(const Physical&) = delete;

                static void init();
                static bool is_init;
        };
    }
}
#endif
