monitoring
==========

a lib to determine CPU /memory consumption.


Current build status: [![Build Status](https://travis-ci.org/Krozark/monitoring.png?branch=master)](https://travis-ci.org/Krozark/monitoring)


Examples
========

Make a look to files in examples directory to see them.


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
