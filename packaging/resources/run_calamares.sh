#! /usr/bin/env sh

SCRIPT_DIRECTORY="$(dirname -- "$(readlink -f -- "$0")")"

MODE="$(echo "$1" | tr "[:upper:]" "[:lower:]")"
if [ "$MODE" != "offline" ] && [ "$MODE" != "online" ]; then
    echo ""
    echo "ERROR: Please specify \"online\" or \"offline\" as the first argument to this script, to indicate the mode to run Calamares in."
    exit 1
fi
shift 1

UNMOUNT_FILESYSTEMS_COMMAND="umount -rf /run/media/rebornos/*"

UPDATE_INSTALL_MODE_COMMAND="cp -f \
    "$SCRIPT_DIRECTORY"/settings_"$MODE".conf \
    "$SCRIPT_DIRECTORY"/settings.conf"

LAUNCH_INSTALLER_COMMAND="env \
    DISPLAY="$DISPLAY" \
    XAUTHORITY="$XAUTHORITY" \
    XDG_RUNTIME_DIR="/tmp/runtime-root" \
    KDE_SESSION_VERSION=5 \
    KDE_FULL_SESSION=true \
    QT_QUICK_CONTROLS_STYLE="org.kde.desktop" \
    dbus-launch calamares "$@""

{
    pkexec \
    bash -c \
        "$UNMOUNT_FILESYSTEMS_COMMAND; $UPDATE_INSTALL_MODE_COMMAND && $LAUNCH_INSTALLER_COMMAND" 
} > ~/install.log      