Calamares
=========

Distribution-independent installer framework

### Dependencies
* CMake >= 2.8.12
* Qt >= 5.3
* yaml-cpp >= 0.5.1
* Python >= 3.3
* Boost.Python >= 1.55.0

### Building
```
$ git submodule init
$ git submodule update
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make
```

### Design notes
Calamares is currently split as follows:
* libcalamares - the backend library,
 * only depends on QtCore, yaml-cpp, Python and Boost.Python,
 * provides a job queue and generic jobs,
 * comes with 3 job interfaces: C++, Python and process (the latter is very limited);
* libcalamaresui - the frontend library,
 * same dependencies as libcalamares, plus QtWidgets and other Qt modules,
 * comes with a module loading system, for different kinds of plugins,
 * themeable so branding can be done easily (plugin-based, TBD),
 * presents a bunch of pages in a scripted order, enqueues jobs in the backend library;
* calamares - the main executable,
 * a thin wrapper around libcalamaresui, starts up and plugs together all the parts.

Some modules require additional dependencies: for example the partition viewmodule pulls in partitionmanager, which in turn requires a few KF5 libraries.
