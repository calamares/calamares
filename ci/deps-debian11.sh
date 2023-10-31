#! /bin/sh
#
# Install dependencies for the nightly-debian (11) build
#
apt-get update
apt-get -y install git-core jq curl ninja
apt-get -y install \
	build-essential \
	cmake \
	extra-cmake-modules \
	gettext \
	libatasmart-dev \
	libappstreamqt-dev \
	libboost-python-dev \
	libicu-dev \
	libparted-dev \
	libpolkit-qt5-1-dev \
	libqt5svg5-dev \
	libqt5webkit5-dev \
	libyaml-cpp-dev \
	ninja-build \
	os-prober \
	pkg-config \
	python3-dev \
	qtbase5-dev \
	qtdeclarative5-dev \
	qttools5-dev \
	qttools5-dev-tools
# Same name as on KDE neon, different version
apt-get -y install libkpmcore-dev
# Additional dependencies (KF5, +)
apt-get -y install \
	libkf5config-dev \
	libkf5coreaddons-dev \
	libkf5i18n-dev \
	libkf5iconthemes-dev \
	libkf5parts-dev \
	libkf5service-dev \
	libkf5solid-dev \
	libkf5crash-dev \
	libkf5package-dev \
	libkf5plasma-dev \
	libpwquality-dev \
	libqt5webenginewidgets5 \
	qtwebengine5-dev
true
