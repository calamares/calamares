#! /usr/bin/env sh

SCRIPT_DIRECTORY="$(dirname -- "$(readlink -f -- "$0")")"

MODE="$(echo "$1" | tr "[:upper:]" "[:lower:]")"
if [ "$MODE" != "offline" ] && [ "$MODE" != "online" ]; then
    echo ""
    echo "ERROR: Please specify \"online\" or \"offline\" as the first argument to this script, to indicate the mode to run Calamares in."
    exit 1
fi
shift 1

(
    cd "$SCRIPT_DIRECTORY" && \
    sudo cp -f settings_"$MODE".conf settings.conf
)
sudo calamares "$@"