Calamares
=========

Distribution-independent installer framework

* Backend
 * lib should only depend on QtCore >=5.3, possibly boost
 * common functions like partitioning
 * works as job queue and executor
 * plugin based to bet distro-specific tasks done in a distro-specific order
* Frontend
 * themeable so branding can be done easily (plugin-based)
 * presents a bunch of pages in a scripted order, enqueues jobs in the backend lib
