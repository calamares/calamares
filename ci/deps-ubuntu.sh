#! /bin/sh
#
# Install dependencies for the nightly-ubuntu (devel) build
# These build dependencies are grabbed directly from the Debian package
#
apt-get update
apt-get -y install git-core jq curl ninja
apt-get -y install \
        build-essential \
        cmake \
        extra-cmake-modules \
        gettext \
        libappstreamqt5-dev \
        libkf5config-dev \
        libkf5coreaddons-dev \
        libkf5crash-dev \
        libkf5i18n-dev \
        libkf5iconthemes-dev \
        libkf5kio-dev \
        libkf5parts-dev \
        libkf5plasma-dev \
        libkf5service-dev \
        libkf5solid-dev \
        libkpmcore-dev \
        libparted-dev \
        libpolkit-qt5-1-dev \
        libpwquality-dev \
        libqt5svg5-dev \
        libqt5webkit5-dev \
        libyaml-cpp-dev \
        os-prober \
        pkg-config \
        pkg-kde-tools \
        polkitd \
        python3-dev \
        python3-jsonschema \
        python3-yaml \
        qml-module-qtquick-layouts \
        qml-module-qtquick-privatewidgets \
        qml-module-qtquick-window2 \
        qml-module-qtquick2 \
        qtbase5-dev \
        qtdeclarative5-dev \
        qtlocation5-dev \
        qttools5-dev \
        qttools5-dev-tools
true
