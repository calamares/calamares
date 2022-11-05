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
		ack@/usr/bin/vendor_perl/ack
		autoconf@/usr/bin/autoconf
		automake@/usr/bin/automake
		binutils@/usr/bin/addr2line
		bison@/usr/bin/bison
		boost-dev@/usr/include/boost/accumulators/accumulators.hpp
		boost-python3-dev@/usr/include/boost/mpi/python.hpp
		cmake@/usr/bin/cmake
		extra-cmake-modules@/usr/share/ECM/cmake/ECMConfig.cmake
		fakeroot@/usr/bin/fakeroot
		flex@/usr/bin/flex
		gcc@/usr/bin/gcc
		gettext@/usr/bin/gettext
		git@/usr/bin/git
		icu@/usr/bin/icuinfo
		kcoreaddons@/usr/bin/desktoptojson
		kcrash@/usr/include/KF5/KCrash/kcrash.h
		kiconthemes@/usr/bin/kiconfinder5
		kio@/usr/bin/kcookiejar5
		kpackage-dev@/usr/include/KF5/KPackage/kpackage/package.h
		kparts-dev@/usr/include/KF5/KParts/kparts/part.h
		kpmcore-dev@/usr/include/kpmcore/backend/corebackend.h
		kservice-dev@/usr/include/KF5/KService/kservice.h
		libatasmart-dev@/usr/include/atasmart.h
		libkf5parts-dev@/usr/include/KF5/KParts/kparts_version.h
		libpwquality-dev@/usr/include/pwquality.h
		libtool@/usr/bin/libtool
		libyaml-dev@/usr/include/yaml.h
		m4@/usr/bin/m4
		make@/usr/bin/make
		parted-dev@/usr/include/parted/device.h
		patch@/usr/bin/patch
		plasma-framework-dev@/usr/include/KF5/plasma/plasma.h
		plasma-workspace-dev@/usr/include/kworkspace5/kworkspace.h
		polkit-qt5-dev@/usr/include/polkit-qt5-1/polkitqt1-agent-export.h
		python3-dev@/usr/bin/python3
		qt5-base-dev@/usr/include/qt/QtConcurrent/qtconcurrentversion.h
		qt5-declarative-dev@/usr/include/qt/QtQml/qtqmlversion.h
		qt5-svg-dev@/usr/include/qt/QtSvg/qtsvgversion.h
		qt5-tools-dev@/usr/include/qt/QtDesigner/qtdesignerversion.h
		qt5-translations@/usr/share/licenses/qt5-translations
		qt5-webengine-dev@/usr/include/qt/QtPdf/qtpdfversion.h
		qt5-xmlpatterns@/usr/share/licenses/qt5-xmlpatterns
		yaml-cpp-dev@/usr/include/yaml-cpp/binary.h
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
	local commands="${*:1}"
	local maxLines=20
	local error=""

	if ! error="$(eval "${commands}" 2>&1 >"/dev/null")"; then
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
