#!/usr/bin/env bash

# Made by fernandomaroto for EndeavourOS and Portergos
# Adapted from AIS. An excellent bit of code!
# ISO-NEXT specific cleanup removals and additions (08-2021) @killajoe and @manuel
# 01-2022 passing in root path and username as params - @dalto
# 04-2022 re-organized code - @manuel

# Anything to be executed outside chroot need to be here.

_cleaner_msg() {            # use this function to provide all user messages (info, warning, error, ...)
    local type="$1"
    local msg="$2"
    echo "==> $type: $msg"
}

arch_chroot() {   # This function is no more needed?
    # Use chroot not arch-chroot because of the way calamares mounts partitions
    chroot /tmp/$chroot_path /bin/bash -c "${1}"
}  

_CopyFileToTarget() {
    # Copy a file to target

    local file="$1"
    local targetdir="$2"

    if [ ! -r "$file" ] ; then
        _cleaner_msg warning "file '$file' does not exist."
        return
    fi
    if [ ! -d "$targetdir" ] ; then
        _cleaner_msg warning "folder '$targetdir' does not exist."
        return
    fi
    _cleaner_msg info "copying $(basename "$file") to target"
    cp "$file" "$targetdir"
}

_manage_broadcom_wifi_driver() {
    local pkgname=broadcom-wl-dkms
    local targetfile=/tmp/$chroot_path/tmp/$pkgname.txt
    local wifi_pci="$(lspci -k | sed -n '/ Network controller: /,/^[^ \t]/p' | sed '$d')"

    if [ -n "$(echo "$wifi_pci" | grep -w Broadcom)" ] ; then
        echo "yes" > $targetfile
    elif [ -n "$(lsusb | grep -w Broadcom)" ] ; then
        echo "yes" > $targetfile
    else
        echo "no" > $targetfile
    fi
}

_copy_files(){
    local config_file
    local target=/tmp/$chroot_path            # $target refers to the / folder of the installed system

    if [ -r /home/liveuser/setup.url ] ; then
        # Is this needed anymore?
        # /home/liveuser/setup.url contains the URL to personal setup.sh
        local URL="$(cat /home/liveuser/setup.url)"
        if (wget -q -O /home/liveuser/setup.sh "$URL") ; then
            _cleaner_msg info "copying setup.sh to target"
            cp /home/liveuser/setup.sh $target/tmp/   # into /tmp/setup.sh of chrooted
        fi
    fi

    # Communicate to chrooted system if
    # - nvidia card is detected
    # - livesession is running nvidia driver

    local nvidia_file=$target/tmp/nvidia-info.bash
    local card=no
    local driver=no
    local lspci="$(lspci -k)"
    local latest_nvidia_series=495     # TODO: this number must be changed when Arch changes the Nvidia driver series number !!!

    if [ -n "$(echo "$lspci" | grep -P 'VGA|3D|Display' | grep -w NVIDIA)" ] ; then
        card=yes
        [ -n "$(lsmod | grep -w nvidia)" ]                                                   && driver=yes
        [ -n "$(echo "$lspci" | grep -wA2 NVIDIA | grep "Kernel driver in use: nvidia")" ]   && driver=yes
        if [ "$driver" = "yes" ] ; then
            _cleaner_msg info "using nvidia driver"
        else
            _cleaner_msg info "using nouveau driver"
        fi
    fi
    echo "nvidia_card=$card"     >> $nvidia_file
    echo "nvidia_driver=$driver" >> $nvidia_file

    # copy user_commands.bash
    _CopyFileToTarget /home/liveuser/user_commands.bash $target/tmp

    # copy 30-touchpad.conf Xorg config file
    _cleaner_msg info "copying 30-touchpad.conf to target"
    mkdir -p $target/usr/share/X11/xorg.conf.d
    cp /usr/share/X11/xorg.conf.d/30-touchpad.conf  $target/usr/share/X11/xorg.conf.d/

    # copy extra drivers from /opt/extra-drivers to target's /opt/extra-drivers
    if [ -n "$(/usr/bin/ls /opt/extra-drivers/*.zst 2>/dev/null)" ] ; then
        _cleaner_msg info "copying extra drivers to target"
        mkdir -p $target/opt/extra-drivers || _cleaner_msg warning "creating folder /opt/extra-drivers on target failed."
        cp /opt/extra-drivers/*.zst $target/opt/extra-drivers/ || _cleaner_msg warning "copying drivers to /opt/extra-drivers on target failed."
    fi
    if [ -n "$(lsmod | grep r8168)" ] ; then
        _cleaner_msg info "detected usage of r8168 driver"
        touch $target/tmp/r8168_in_use
    fi

    _manage_broadcom_wifi_driver

    # copy endeavouros-release file
    local file=/usr/lib/endeavouros-release
    if [ -r $file ] ; then
        if [ ! -r $target$file ] ; then
            _cleaner_msg info "copying $file to target"
            rsync -vaRI $file $target
        fi
    else
        _cleaner_msg warning "$FUNCNAME: file $file does not exist in the ISO, copy to target failed!"
    fi
}

Main() {
    _cleaner_msg info "cleaner_script.sh started."

    local ROOT_PATH="" NEW_USER=""
    local i

    # parse the options
    for i in "$@"; do
        case $i in
            --root=*)
                ROOT_PATH="${i#*=}"
                shift
                ;;
            --user=*)
                NEW_USER="${i#*=}"
                shift
                ;;
        esac
    done

    if [ -n "$ROOT_PATH" ] ; then
        chroot_path="${ROOT_PATH#/tmp/}"
    else
        # "else" needed no more?
        if [ -f /tmp/chrootpath.txt ]
        then
            chroot_path=$(echo ${ROOT_PATH} |sed 's/\/tmp\///')
        else
            chroot_path=$(lsblk |grep "calamares-root" |awk '{ print $NF }' |sed -e 's/\/tmp\///' -e 's/\/.*$//' |tail -n1)
        fi
    fi

    if [ -z "$chroot_path" ] ; then
        _cleaner_msg "FATAL ERROR" "cleaner_script.sh: chroot_path is empty!"
        return  # no point in continuing here
    fi
    if [ -z "$NEW_USER" ] ; then
        _cleaner_msg "error" "cleaner_script.sh: new username is unknown!"
    fi

    # Copy any file from live environment to new system

    if [ -n "$NEW_USER" ] ; then
        cp -f /etc/skel/.bashrc /tmp/$chroot_path/home/$NEW_USER/.bashrc
    fi
    cp -f /etc/calamares/files/environment /tmp/$chroot_path/etc/environment
    cp -n /usr/bin/device-info /tmp/$chroot_path/usr/bin/.
    cp -n /usr/bin/eos-connection-checker /tmp/$chroot_path/usr/bin/.

    #cp -rf /home/liveuser/.gnupg/gpg.conf /tmp/$chroot_path/etc/pacman.d/gnupg/gpg.conf

    _copy_files

    _cleaner_msg info "cleaner_script.sh done."
}


Main "$@"
