### Umount Module
---------
This module represents the last part of the installation, the unmounting of partitions used for the install.  It is also the last place where it is possible to copy files to the target system, thus the best place to copy an installation log.

To be able to use the copy an installation log of this module you will need to include a log creation to your launcher script or add it to the used calamares.desktop, example of a launcher script:

```
#!/bin/sh
sudo /usr/bin/calamares -d > installation.log 
```
Example desktop line:
```
Exec=sudo /usr/bin/calamares -d > installation.log
```
Set the source and destination path of your install log in umount.conf
If you do not wish to use the copy of an install log feature, no action needed, the module will not execute the copy of a log code if no log is present.

