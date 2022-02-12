#! /bin/bash
: '
For building Calamares using this program, in the application "Terminal" type:
"/pathToThisFolder/build.sh" "[arguments]"

Where "[arguments]" can either be:

- The build type: "Release" or "Debug"
- The building flags, for example: -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr
'

here="$(realpath "$(dirname "${0}")")"
build="${here}/_BUILD"


mainFunction () {
	enterBuildDir
	configureBuild
	compile
}


checkDependencies () {
	local name=""
	local location=""
	local dependency=""
	local missing=()

	local dependencies=(
		boost@/usr/bin/b2
		cmake@/usr/bin/cmake
		extra-cmake-modules@/usr/share/ECM/cmake/ECMConfig.cmake
		gcc@/usr/bin/gcc
		kcoreaddons@/usr/bin/desktoptojson
		kpmcore@/usr/include/kpmcore/backend/corebackend.h
		python3@/usr/bin/python3
		qt@/usr/bin/qmake
		yaml-cpp@/usr/include/yaml-cpp/binary.h
	)

	for dependency in "${dependencies[@]}"; do
		name="$(echo "${dependency}" | cut --delimiter='@' --fields=1)"
		location="$(echo "${dependency}" | cut --delimiter='@' --fields=2)"

		if [[ ! -f "${location}" ]]; then
			missing+=("${name}")
		fi
	done

	if [[ "${#missing[@]}" -ne 0 ]]; then
		echo "missing dependencies: ${missing[*]}" >&2
		exit 1
	fi
}


compile () {
	local cores; cores="$(grep -c ^processor /proc/cpuinfo)"
	local jobs; jobs="$(("${cores}" + "${cores}" / 2))"
	local load; load="$(optimalLoad "${cores}")"

	so make --jobs="${jobs}" --load="${load}"
}


configureBuild () {
	# shellcheck disable=SC2068
	so cmake .. ${arguments[@]}
}


enterBuildDir () {
	makeBuildDir
	cd "${build}"
}


makeBuildDir () {
	if [[ ! -d "${build}" ]]; then
		mkdir --parents "${build}"
	fi
}


optimalLoad () {
	local cores="${1}"

	if [[ "${cores}" -eq 1 ]]; then
		echo 1
	else
		echo "$(("${cores}" * 75 / 100))"
	fi
}


prepareEnvironment () {
	set -e
	renice --priority 10 "${$}" >/dev/null
	checkDependencies
	setArguments "${@}"
}


setArguments () {
	arguments=("${@}")

	if [[ "${#arguments}" -eq 0 ]]; then
		echo "no build type specified as argument: Release Debug" >&2
		exit 1
	elif [[ "${arguments[*]}" == "Release" ]] || [[ "${arguments[*]}" == "Debug" ]]; then
		arguments=("-DCMAKE_BUILD_TYPE=${arguments[*]}")
	fi
}


so () {
	local tag="-${FUNCNAME[2]}"
	local commands="${@:1}"
	local maxLines=20
	local error=""

	if ! error="$(eval "${commands[@]}" 2>&1 >"/dev/null")"; then
		if [[ -z "${error}" ]] ; then
			error="Command failed: ${commands[*]}"
		else
			if [[ "$(echo "${error}" | wc --lines)" -gt "${maxLines}" ]]; then
				error="$(echo "${error}" | tail -n "${maxLines}")"
				error="$(printf "...\n%s", "${error}")"
			fi

			echo "${tag}${error}" >&2
		fi

		exit 1
	fi
}


prepareEnvironment "${@}"
mainFunction "${@}"
