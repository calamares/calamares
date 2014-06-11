Calamares
=========

Distribution-independent installer framework

### Dependencies
* CMake >= 2.8.12
* Qt >= 5.3

### Building
```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make
```

### Design notes
* Backend
 * lib should only depend on QtCore >=5.3, possibly boost::python
 * common functions like partitioning
 * works as job queue and executor
 * plugin based to let distro-specific tasks be done in a distro-specific order
* Frontend
 * QtWidgets >=5.3, other deps as needed
 * themeable so branding can be done easily (plugin-based)
 * presents a bunch of pages in a scripted order, enqueues jobs in the backend lib
