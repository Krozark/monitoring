#include <Monitoring/sys.hpp>

#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

int main(int argc,char* argv[])
{
    cout<<"Sys infos:\n\tosName: "<<sys::osName()
        <<"\n\tosBit: "<<sys::osBit()
        <<"\n\tosNameBit: "<<sys::osNameBit()
        <<"\n\tcheckBit: "<<sys::checkBit()
        <<"\n\tmemory Physical:"
        <<"\n\t\ttotal: "<<sys::memory::Physical::total()
        <<"\n\t\tused: "<<sys::memory::Physical::used()
        <<"\n\t\tusedByProc: "<<sys::memory::Physical::usedByProc()
        <<"\n\tmemory Virtual:"
        <<"\n\t\ttotal: "<<sys::memory::Virtual::total()
        <<"\n\t\tused: "<<sys::memory::Virtual::used()
        <<"\n\t\tusedByProc: "<<sys::memory::Virtual::usedByProc()
        <<std::endl;
    cout<<"Cpu::processors: "<<sys::Cpu::processors()<<endl;
    

    return 0;
}
