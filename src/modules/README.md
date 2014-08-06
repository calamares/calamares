Calamares modules
===

Calamares modules are plugins that provide features like installer pages, batch jobs, etc.
Each Calamares module lives in its own directory.

All modules are installed in `$DESTDIR/lib/calamares/modules`.

### Module directory and descriptor
A Calamares module must have a *module descriptor file*, named `module.desc`, this file must be placed in the module's
directory.
The module descriptor file is a YAML 1.2 document which defines the module's name, type, interface and possibly other
properties. The name of the module as defined in `module.desc` must be the same as the name of the module's directory.

There are two types of Calamares module:
* viewmodule,
* jobmodule.

There are three interfaces for Calamares modules:
* qtplugin,
* python,
* process.

### Module-specific configuration
A Calamares module *may* read a module configuration file, named `<modulename>.conf`. If such a file is present in the
module's directory, it is shipped as a *default* configuration file.
The module configuration file, if it exists, is a YAML 1.2 document which contains a YAML map of anything.
All default module configuration files are installed in `$DESTDIR/share/calamares/modules` but can be overridden by
files with the same name placed manually (or by the packager) in `/etc/calamares/modules`.

### Qt plugin viewmodules

Currently the only way to write a module which exposes one or more installer pages (viewmodule) is through a Qt plugin.
Viewmodules should implement `Calamares::ViewStep`. They can also implement `Calamares::Job` to provide jobs.

To add a Qt plugin module, put it in a subdirectory and make sure it has a `module.desc` and a `CMakeLists.txt` with a
`calamares_add_plugin` call. It will be picked up automatically by our CMake magic.


### Python and process jobmodules

Batch jobs for Calamares can be written as Python scripts or as generic commands (shell scripts, external programs, etc.).
To add a Python or process jobmodule, put it in a subdirectory and make sure it has a `module.desc`.
It will be picked up automatically by our CMake magic.

`CMakeLists.txt` is *not* used for Python and process jobmodules.

A Python jobmodule is a Python program which imports libcalamares and has a function `run()` as entry point.
`run()` must return `None` if everything went well, or a tuple `(str,str)` with an error message and description if
something went wrong.

Calamares offers a Python API for module developers, the core Calamares functionality is exposed as `libcalamares.job`
for job data, `libcalamares.globalstorage` for shared data and `libcalamares.utils` for generic utility functions.
Documentation is inline.

All code in Python job modules must obey PEP8, the only exception are `libcalamares.globalstorage` keys, which should
always be camelCaseWithLowerCaseInitial.

For testing and debugging we provide the `testmodule.py` script which fakes a limited Calamares Python environment for
running a single jobmodule. 