#! /bin/sh
#
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#   1. Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#   2. Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
### END LICENSES

### USAGE
#
# Shell script to help build an AppImage for Calamares.
#
# Usage:
#   AppImage.sh [-T|--tools-dir <dir>]
#               [-C|--cmake-args <args>]
#               [-c|--config-dir <dir>]
#               [-s|--skip-build]
#               [-p|--with-python]
#
# Multiple --cmake-args arguments will be collected together and passed to
# CMake before building the application.
#
# Use --tools-dir to indicate where the linuxdeploy tools are located.
#
# Use --config to copy a config-directory (with settings.conf and others)
# into the resulting image,
#
# Option --skip-build assumes that there is an already-built Calamares
# available in the AppImage build directory; use this when you are, e.g.
# re-packaging the image with different configuration. Option --with-python
# adds the Conda Python packaging ecosystem to the AppImage, which will make
# it **more** portable by disconnecting from the system Python libraries.
#
# The build process for AppImage proceeds in a directory build-AppImage
# that is created in the current directory.
#
# The resulting AppImage has XDG_* enabled, and appends the in-image
# directories to the current environment. You can set XDG_* in the
# current environment to use other configurations and data, e.g. the
# data in the current live environment. Or leave it unset, to try
# Calamares with only the configuration contained in the AppImage.
#
### END USAGE

TOOLS_DIR="."
CMAKE_ARGS=""
DO_REBUILD="true"
DO_CONDA="false"
CONFIG_DIR=""
while test "$#" -gt 0
do
    case "x$1" in
    x--help|x-h)
        sed -e '1,/USAGE/d' -e '/END.USAGE/,$d' < "$0"
        return 0
        ;;
    x--tools-dir|x-T)
        TOOLS_DIR="$2"
        shift
        ;;
    x--cmake-args|x-C)
        CMAKE_ARGS="$CMAKE_ARGS $2"
        shift
        ;;
    x--config-dir|x-c)
        CONFIG_DIR="$2"
        shift
        ;;
    x--skip-build|x-s)
        DO_REBUILD="false"
        ;;
    x--with-python|x-p)
        DO_CONDA="true"
        ;;
    *)
        echo "! Unknown argument '$1'."
        exit 1
        ;;
    esac
    test "$#" -gt 0 || { echo "! Missing arguments."; exit 1; }
    shift
done

### Check where we're running
#
BIN_DIR=$( cd $( dirname "$0" ) && pwd -P )
test -d "$BIN_DIR" || { echo "! Could not find BIN_DIR"; exit 1; }
test -f "$BIN_DIR/AppImage.sh" || { echo "! $BIN_DIR does not have AppImage.sh"; exit 1; }

SRC_DIR=$( cd "$BIN_DIR/.." && pwd -P )
test -d "$SRC_DIR" || { echo "! Could not find SRC_DIR"; exit 1; }
test -d "$SRC_DIR/ci" || { echo "! $SRC_DIR isn't a top-level Calamares checkout"; exit 1; }
test -f "$SRC_DIR/CMakeLists.txt" || { echo "! SRC_DIR is missing CMakeLists.txt"; exit 1; }

### Check pre-requisites
#
BUILD_DIR=build-AppImage
test -d "$BUILD_DIR" || mkdir -p "$BUILD_DIR"
test -d "$BUILD_DIR" || { echo "! Could not create $BUILD_DIR"; exit 1; }

TOOLS_LIST="linuxdeploy-x86_64.AppImage linuxdeploy-plugin-qt-x86_64.AppImage"
$DO_CONDA && TOOLS_LIST="$TOOLS_LIST linuxdeploy-plugin-conda.sh"

for tool in $TOOLS_LIST
do
    if test -x "$BUILD_DIR/$tool" ; then
        # This tool is ok
        :
    else
        if test -f "$TOOLS_DIR/$tool" ; then
            cp "$TOOLS_DIR/$tool" "$BUILD_DIR/$tool" || exit 1
        else
            fetch=$( grep "^# URL .*$tool\$" "$0" | sed 's/# URL *//' )
            curl -L -o "$BUILD_DIR/$tool" "$fetch"
        fi
        chmod +x "$BUILD_DIR/$tool"
        test -x "$BUILD_DIR/$tool" || { echo "! Missing tool $tool in tools-dir $TOOLS_DIR"; exit 1; }
    fi
done

if test -n "$CONFIG_DIR" ; then
    test -f "$CONFIG_DIR/settings.conf" || { echo "! No settings.conf in $CONFIG_DIR"; exit 1; }
fi

### Clean up build-directory
#
rm -rf "$BUILD_DIR/AppDir"
if $DO_REBUILD ; then
    rm -rf "$BUILD_DIR/build"
    mkdir "$BUILD_DIR/build" || { echo "! Could not create $BUILD_DIR/build for the cmake-build."; exit 1; }
else
    test -d "$BUILD_DIR/build" || { echo "! No build found in $BUILD_DIR, but --skip-build is given."; exit 1; }
    test -x "$BUILD_DIR/build/calamares" || { echo "! No complete build found in $BUILD_DIR/build ."; exit 1; }
fi
mkdir "$BUILD_DIR/AppDir" || { echo "! Could not create $BUILD_DIR/AppDir for the AppImage install."; exit 1; }
LOG_FILE="$BUILD_DIR/AppImage.log"
rm -f "$LOG_FILE"
{ echo "# Calamares build started" `date` ; echo "# .. build directory $BUILD_DIR"; echo "# .. log file $LOG_FILE"; } > "$LOG_FILE"
cat "$LOG_FILE"

### Python Support
#
#
if $DO_CONDA ; then
    export CONDA_CHANNELS="conda-forge;anaconda"
    export CONDA_PACKAGES="gettext;py-boost"

    (
        cd "$BUILD_DIR" &&
        ./linuxdeploy-x86_64.AppImage --appdir=AppDir/ --plugin=conda
    )

    . "$BUILD_DIR/AppDir/usr/conda/bin/activate"
fi

### Build Calamares
#
if $DO_REBUILD ; then
    echo "# Running cmake ..."
    (
        cd "$BUILD_DIR/build" &&
        cmake "$SRC_DIR" -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib $CMAKE_ARGS
    ) >> "$LOG_FILE" 2>&1 || { tail -10 "$LOG_FILE" ; echo "! Could not run CMake"; exit 1; }
    echo "# Running make ..."
    (
        cd "$BUILD_DIR/build" &&
        make -j4
    ) >> "$LOG_FILE" 2>&1 || { tail -10 "$LOG_FILE" ; echo "! Could not run make"; exit 1; }
fi
echo "# Running make install ..."
(
    cd "$BUILD_DIR/build" &&
    make install DESTDIR=../AppDir
) >> "$LOG_FILE" 2>&1 || { tail -10 "$LOG_FILE" ; echo "! Could not run make install"; exit 1; }

### Modify installation
#
IMAGE_DIR="$BUILD_DIR/AppDir"

# Munge the desktop file to not use absolute paths or pkexec
sed -i \
    -e 's+^Exec=.*+Exec=calamares+' \
    -e 's+^Name=.*+Name=Calamares+' \
    "$IMAGE_DIR"/usr/share/applications/calamares.desktop

# Replace the executable with a shell-proxy
test -x "$IMAGE_DIR/usr/bin/calamares" || { echo "! Does not seem to have installed calamares"; exit 1; }
mv "$IMAGE_DIR/usr/bin/calamares" "$IMAGE_DIR/usr/bin/calamares.bin"
cat > "$IMAGE_DIR/usr/bin/calamares" <<"EOF"
#! /bin/sh
#
# Calamares proxy-script. Runs Calamares with XDG support enabled,
# and in-image XDG dirs set up so that compiled-in configuration can be used.
test -n "${XDG_DATA_DIRS}" && XDG_DATA_DIRS="${XDG_DATA_DIRS}:"
test -n "${XDG_CONFIG_DIRS}" $$ XDG_CONFIG_DIRS="${XDG_CONFIG_DIRS}:"
export XDG_DATA_DIRS="${XDG_DATA_DIRS}${APPDIR}/usr/share/"
export XDG_CONFIG_DIRS="${XDG_CONFIG_DIRS}${APPDIR}/etc/:${APPDIR}/usr/share/"
export PYTHONPATH="${APPDIR}/usr/lib:"
cd "$APPDIR"
exec "$APPDIR"/usr/bin/calamares.bin -X "$@"
EOF
chmod 755 "$IMAGE_DIR/usr/bin/calamares"
test -x "$IMAGE_DIR/usr/bin/calamares" || { echo "! Does not seem to have proxy for calamares"; exit 1; }

### Install additional files
#
PLUGIN_DIR=$( qmake  -query QT_INSTALL_PLUGINS )
for plugin in \
    libpmsfdiskbackendplugin.so \
    libpmdummybackendplugin.so \
    libpmlibpartedbackendplugin.so
do
    # Warning, but not fatal: generally you only have two out of three available
    # depending on the KPMCore version.
    cp "$PLUGIN_DIR/$plugin" "$IMAGE_DIR/usr/lib" 2> /dev/null || { echo "! Could not copy KPMCore plugin $plugin"; }
done

# Install configuration files
ETC_DIR="$IMAGE_DIR"/etc/calamares
mkdir -p "$ETC_DIR"
test -d "$ETC_DIR" || { echo "! Could not create /etc/calamares in image."; exit 1; }

if test -z "$CONFIG_DIR" ; then
    echo "# Using basic settings.conf"
    cp "$SRC_DIR/settings.conf" "$ETC_DIR"
else
    test -f "$CONFIG_DIR/settings.conf" || { echo "! No settings.conf in $CONFIG_DIR"; exit 1; }
    mkdir -p "$ETC_DIR/modules"
    cp "$CONFIG_DIR/settings.conf" "$ETC_DIR"
    test -d "$CONFIG_DIR/modules" && cp -r "$CONFIG_DIR/modules" "$ETC_DIR"
    test -d "$CONFIG_DIR/branding" && cp -r "$CONFIG_DIR/branding" "$IMAGE_DIR/usr/share/calamares"
fi

### Build the AppImage
#
#
echo "# Building AppImage"
(
    export QT_SELECT=qt5  # Otherwise might pick Qt4 in image
    export LD_LIBRARY_PATH=AppDir/usr/lib  # RPATH isn't set in the executable
    cd "$BUILD_DIR" &&
    ./linuxdeploy-x86_64.AppImage --appdir=AppDir/ --plugin=qt --output=appimage
) >> "$LOG_FILE" 2>&1 || { tail -10 "$LOG_FILE" ; echo "! Could not create image"; exit 1; }

echo "# Created in $BUILD_DIR/Calamares-x86_64.AppImage"
echo "# .. log file at $LOG_FILE"

exit 0
### Database for installation
#
# URL https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
# URL https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
# URL https://raw.githubusercontent.com/TheAssassin/linuxdeploy-plugin-conda/master/linuxdeploy-plugin-conda.sh
