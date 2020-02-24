#!/usr/bin/env bash

function remove () {
    local list
    local file
    local exit_code
    list=($(echo "$@"))
    for file in "${list[@]}"; do
        if [[ -f ${file} ]]; then
            rm -f "${file}"
        elif [[ -d ${file} ]]; then
            rm -rf "${file}"
        fi
    done
}

while getopts 'u:' arg; do
    case "${arg}" in
        u) user="${OPTARG}";;
    esac
done

remove /etc/skel/Desktop
remove /etc/systemd/system/getty@tty1.service.d/autologin.conf
remove /root/.automated_script.sh
remove /etc/mkinitcpio-archiso.conf
remove /etc/initcpio
remove /home/${user}/Desktop/calamares.desktop