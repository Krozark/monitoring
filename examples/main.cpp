#include <Monitoring/sys.hpp>

#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

int main(int argc,char* argv[])
{
    cout<<"Cpu::processors: "<<sys::Cpu::processors()<<endl;
    
    uint64_t mem = 0;

    double max_mem = (double)sys::memory::Physical::total();

    while(true)
    {
        cout<<"CPU:\n\tused "<<sys::Cpu::used()<<"\n\tusedByProc: "<<sys::Cpu::usedByProc()<<endl;

        size_t aloc = 1024*64;
        mem +=aloc;
        void* buffer = malloc(aloc);
        memset(buffer,0,aloc);

        cout<<"memory::Physical\n\ttotal: "<<sys::memory::Physical::total()<<"\n\tused: "<<sys::memory::Physical::used()<<"\n\tusedByProc: "<<sys::memory::Physical::usedByProc()<<endl;

        cout<<"memory::Virtual\n\ttotal: "<<sys::memory::Virtual::total()<<"\n\tused: "<<sys::memory::Virtual::used()<<"\n\tusedByProc: "<<sys::memory::Virtual::usedByProc()<<endl;

        cout<<"Alocated: "<<mem<<endl;

        std::cout<<"--------------"<<std::endl;

        if (sys::memory::Physical::usedByProc()/max_mem > 0.7 )
        {
            cout<<"70% of the memory is used by this program. stop"<<endl;
            break;
        }
    }
    return 0;
}
