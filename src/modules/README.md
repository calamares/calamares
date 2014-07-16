Calamares modules directory
===

Calamares modules are plugins that implement the Calamares module API and can provide features like installer pages, batch jobs, etc.

### Qt plugin viewmodules

Currently the only way to write a module which exposes one or more installer pages (viewmodule) is through a Qt plugin. Viewmodules should implement `Calamares::ViewStep`. They can also implement `Calamares::Job` to provide jobs.

To add a Qt plugin module, put it in a subdirectory and make sure it has a `module.conf` and a CMakeLists.txt with a `calamares_add_plugin` call. It will be picked up automatically by our CMake magic.


### Python and process jobmodules

Batch jobs for Calamares can be written as Python scripts or as generic commands (shell scripts, external programs, etc.). To add a Python or process jobmodule, put it in a subdirectory and make sure it has a `module.conf`. It will be picked up automatically by our CMake magic. CMakeLists.txt is not used for Python and process jobmodules.
