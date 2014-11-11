## initramfs module

This module is specific to Debian based distros. Post installation on Debian
the initramfs needs to be updated so as to not interrupt the boot process
with a error about fsck.ext4 not being found.

## Debian specific notes

If you're using live-build to build your ISO and setup the runtime env
make sure that you purge the live-\* packages on the target system
before running this module, since live-config dpkg-diverts update-initramfs
and can cause all sorts of fun issues.
