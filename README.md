monitoring
==========

a lib to determine CPU /memory consumption.


Current build status: [![Build Status](https://travis-ci.org/Krozark/monitoring.png?branch=master)](https://travis-ci.org/Krozark/monitoring)

Build
=====

Use cmake to build the lib.


Testing
=======

Ubuntu 12.04+ x86/32
Windows xp x86


Examples
========

Make a look to files in examples directory to see them.


Doc
===

You can build the documentation using doxygen, or "make doc"


Usage
=====

All class are under the sys namespace.

You can use them by include 
```c++
    <Monitoring/sys.hpp> //All files
    //or
    <Monitoring/Cpu.hpp>
    <Monitoring/Physical.hpp>
    <Monitoring/Virtual.hpp>
```


sys
---

```c++
    SYS_64BIT //defined is the OS is 64 bits
    SYS_32BIT ///defined is the os is 32 bits

    std::string osName();
    std::string osNameBit();
    int osBit();
    bool checkBit();
```


sys::Cpu
--------

```c++
    static int processors();
    static double used(); //in %
    static double usedByProc(); //in %
```


sys::memory::Physical
---------------------

```c++
    static uint64_t total();
    static uint64_t used();
    static uint64_t usedByProc();
```

sys::memory::Virtual
--------------------

```c++
    static uint64_t total();
    static uint64_t used();
    static uint64_t usedByProc();
```
