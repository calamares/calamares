#! /bin/bash
: '
Builds and executes a debug version of Calamares.

For running, in the application "Terminal" type:
"/pathToThisFolder/test.sh"

Configure by editing afterwards:
_BUILD/settings.conf
'

here="$(realpath "$(dirname "${0}")")"
build="${here}/_BUILD"


mainFunction () {
	"${here}/build.sh" "Debug"
	cp --no-clobber "${here}/settings.conf" "${build}/settings.conf"
	cd "${build}"
	sudo XDG_RUNTIME_DIR="/tmp/runtime-root" ./calamares -d >/dev/null
}


configurePermissions () {
	sudo -v
	refreshPermissions "$$" &
}


prepareEnvironment () {
	set -e
	configurePermissions
}


refreshPermissions () {
	local pid="${1}"

	while kill -0 "${pid}" 2> /dev/null; do
		sudo -v
		sleep 10
	done
}


prepareEnvironment
mainFunction "${@}"
