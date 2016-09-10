#!/bin/sh
kernel_cmdline ()
{
    for param in $(/bin/cat /proc/cmdline); do
        case "${param}" in
            $1=*) echo "${param##*=}"; return 0 ;;
            $1) return 0 ;;
            *) continue ;;
        esac
    done
    [ -n "${2}" ] && echo "${2}"
    return 1
}

USENONFREE="$(kernel_cmdline nonfree no)"
VIDEO="$(kernel_cmdline xdriver no)"
DESTDIR="$1"

REPO_PATH=/opt/live
[ -d /opt/livecd ] && REPO_PATH=/opt/livecd
PAC_CONF=${REPO_PATH}/pacman-gfx.conf

echo "MHWD-Driver: ${USENONFREE}"
echo "MHWD-Video: ${VIDEO}"

mkdir -p ${DESTDIR}${REPO_PATH}
mount -o bind ${REPO_PATH} ${DESTDIR}${REPO_PATH} > /tmp/mount.pkgs.log
ls ${DESTDIR}${REPO_PATH} >> /tmp/mount.pkgs.log

# Video driver
if  [ "${USENONFREE}" == "yes" ] || [ "${USENONFREE}" == "true" ]; then
	if  [ "${VIDEO}" == "vesa" ]; then
		chroot ${DESTDIR} mhwd --install pci video-vesa --pmconfig "${PAC_CONF}"
	else
		chroot ${DESTDIR} mhwd --auto pci nonfree 0300 --pmconfig "${PAC_CONF}"
	fi
else
	if  [ "${VIDEO}" == "vesa" ]; then
		chroot ${DESTDIR} mhwd --install pci video-vesa --pmconfig "${PAC_CONF}"
	else
		chroot ${DESTDIR} mhwd --auto pci free 0300 --pmconfig "${PAC_CONF}"
	fi
fi

# Network driver
chroot ${DESTDIR} mhwd --auto pci free 0200 --pmconfig "${PAC_CONF}"
chroot ${DESTDIR} mhwd --auto pci free 0280 --pmconfig "${PAC_CONF}"

umount ${DESTDIR}${REPO_PATH}
rmdir ${DESTDIR}${REPO_PATH}
