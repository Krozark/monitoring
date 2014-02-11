#include <Monitoring/sys.hpp>

namespace sys
{
    void close()
    {
        Cpu::close();
        memory::Virtual::close();
        memory::Physical::close();
    }
}
