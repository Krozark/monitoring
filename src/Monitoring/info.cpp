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
        <<std::endl;
    cout<<"Cpu::processors: "<<sys::Cpu::processors()<<endl;
    

    return 0;
}
