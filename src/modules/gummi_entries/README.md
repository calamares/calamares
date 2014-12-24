# Gummiboot

The idea behind this module is not to make something gummiboot is not (a bootmanager), 
but rather make some simple enhancements to this bootloader.

Gummiboot, by design, automatically adds entries for UEFI Windows systems and any other 
OS already using gummiboot.  But that leaves installs using the grub bootmanager as not 
visible in the gummiboot menu.

## Task of this Module

To add a gummiboot .conf of an existing grub using OS, this module only reads the 
EFI System Partition (ESP) used during the install.  It will not try to find installs part 
of another partition then the /boot used in the bootloader module.  It is not in line with 
gummiboot capabilities to work with distribution not mounted in the same ESP.

At this point, best results come with using a variety of search paths in the mounted /boot to
find an already existing grub.cfg.  It then reads the first seven characters of the found 
distribution's name, the used kernel image (initrd), kernel and UUID, and copies those to a unique 
gummiboot .conf

In the settings.conf the grub module needs to be disabled, bootloader module enabled, run the
gummi_entries after the bootloader to ensure the correct directories are set.

