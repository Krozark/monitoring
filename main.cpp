#include <Monitoring/sys.hpp>

#include <iostream>
#include <stdlib.h>


using namespace std;

int main(int argc,char* argv[])
{
    cout<<"Cpu::processors: "<<sys::Cpu::processors()<<endl;
    
    const int max = 10;
    uint64_t mem = 0;
    for(int i=0;i<max;++i)
    {
        cout<<"CPU:\n\tused "<<sys::Cpu::used()<<"\n\tusedByProc: "<<sys::Cpu::usedByProc()<<endl;

        size_t aloc = 1024*1024;
        mem +=aloc;
        malloc(aloc);

        cout<<"memory::Physical\n\ttotal: "<<sys::memory::Physical::total()<<"\n\tused: "<<sys::memory::Physical::used()<<"\n\tusedByProc: "<<sys::memory::Physical::usedByProc()<<endl;

        cout<<"memory::Virtual\n\ttotal: "<<sys::memory::Virtual::total()<<"\n\tused: "<<sys::memory::Virtual::used()<<"\n\tusedByProc: "<<sys::memory::Virtual::usedByProc()<<endl;

        cout<<"Alocated: "<<mem<<endl;

        std::cout<<"--------------"<<std::endl;
    }
    return 0;
}
