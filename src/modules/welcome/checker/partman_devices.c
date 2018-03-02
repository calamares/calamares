/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *
 *   Based on parted_devices.c, from partman-base.
 *   <http://anonscm.debian.org/cgit/d-i/partman-base.git>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "partman_devices.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#ifdef __linux__
/* from <linux/cdrom.h> */
#define CDROM_GET_CAPABILITY    0x5331  /* get capabilities */
#endif /* __linux__ */

#ifdef __FreeBSD_kernel__
#include <sys/cdio.h>
#include <errno.h>
#endif

#include <parted/parted.h>

#if defined(__linux__)
static int
is_cdrom(const char *path)
{
    int fd = -1;
    int ret = -1;

    fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd >= 0)
    {
        ret = ioctl(fd, CDROM_GET_CAPABILITY, NULL);
        close(fd);
    }

    if (ret >= 0)
        return 1;
    else
        return 0;
}
#elif defined(__FreeBSD_kernel__) /* !__linux__ */
static int
is_cdrom(const char *path)
{
    int fd;

    fd = open(path, O_RDONLY | O_NONBLOCK);
    ioctl(fd, CDIOCCAPABILITY, NULL);   
    close(fd);

    if (errno != EBADF && errno != ENOTTY)
        return 1;
    else
        return 0;
}
#else /* !__linux__ && !__FreeBSD_kernel__ */
#define is_cdrom(path) 0
#endif

#if defined(__linux__)
static int
is_floppy(const char *path)
{
    return (strstr(path, "/dev/floppy") != NULL ||
        strstr(path, "/dev/fd") != NULL);
}
#elif defined(__FreeBSD_kernel__) /* !__linux__ */
static int
is_floppy(const char *path)
{
    return (strstr(path, "/dev/fd") != NULL);
}
#else /* !__linux__ && !__FreeBSD_kernel__ */
#define is_floppy(path) 0
#endif

static long long
process_device(PedDevice *dev)
{
    if (dev->read_only)
        return -1;
    if (is_cdrom(dev->path) || is_floppy(dev->path))
        return -1;
    /* Exclude compcache (http://code.google.com/p/compcache/) */
    if (strstr(dev->path, "/dev/ramzswap") != NULL ||
        strstr(dev->path, "/dev/zram") != NULL)
        return -1;
    return dev->length * dev->sector_size;
}

int
check_big_enough(long long required_space)
{
    PedDevice *dev = NULL;
    ped_exception_fetch_all();
    ped_device_probe_all();

    bool big_enough = false;
    for (dev = NULL; NULL != (dev = ped_device_get_next(dev));)
    {
        long long dev_size = process_device(dev);
        if (dev_size > required_space)
        {
            big_enough = true;
            break;
        }
    }

    // We would free the devices to release allocated memory,
    // but other modules might be using partman use well,
    // and they can hold pointers to libparted structures in
    // other threads.
    //
    // So prefer to leak memory, instead.
    //
    // ped_device_free_all();

    return big_enough;
}

/*
Local variables:
indent-tabs-mode: nil
c-file-style: "linux"
c-font-lock-extra-types: ("Ped\\sw+")
End:
*/
