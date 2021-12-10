#! /usr/bin/env sh

# Global settings
BUILD_DIRECTORY="/tmp/makepkg"
PACKAGE_NAME="rebornos-calamares-core" # Must be the same as the one set in the PKGBUILDS

# Parse arguments
LONG=source:,target:,branch:,clean,install,help
SHORT=s:,t:,b:,c,i,h
OPTS=$(getopt --alternative --name build-package --options $SHORT --longoptions $LONG -- "$@") 
eval set -- "$OPTS"

# Set default options
TARGET="arch"
SOURCE="local"
BRANCH=""
CLEAN="n"
INSTALL="n"

display_help()
{
    echo "Usage:                                                                        "
    echo "    build-package -h|--help                                                   "
    echo "    build-package [-s|--source <SOURCE>] [-t|--target <TARGET>]               "
    echo "                            [-b|--branch <BRANCH>] [-c|--clean] [-i|--install]"
    echo "Arguments:                                                                    "
    echo "    <SOURCE>:                                                                 "
    echo "        local     Use the local source code                                   "
    echo "        git       Pull sources from the git repository                        "
    echo "    <TARGET>:                                                                 "
    echo "        arch      Build for Arch Linux                                        "
    echo "    <BRANCH>:     Name of the git branch to use                               "
}

build_package()
{
    TARGET="$1"
    SOURCE="$2"
    BRANCH="$3"
    CLEAN="$4"
    INSTALL="$5"

    if [ "$TARGET" == "arch" ]; then
        build_package_arch "$SOURCE" "$BRANCH" "$CLEAN" "$INSTALL"
    else
        echo "Target $1 is not supported yet. Please contact the developer." 1>&2
        exit 3
    fi
}

build_package_arch()
{
    echo "Building for Arch Linux..."
    SOURCE="$1"
    BRANCH="$2"
    CLEAN="$3"
    INSTALL="$4"
    PROJECT_DIRECTORY=$(dirname -- $(dirname -- $(readlink -f -- "$0"))) # Resolve any symlinks and then go to the parent directory

    SOURCE_PATH="$PROJECT_DIRECTORY"    
    DESTINATION_PATH="$BUILD_DIRECTORY/$PACKAGE_NAME/src"
    echo "Detected project directory: $PROJECT_DIRECTORY"
    echo "The makepkg build files will be copied to: $BUILD_DIRECTORY/$PACKAGE_NAME"
    echo ""

    if [ "$SOURCE" == "local" ]; then
        echo "Local build selected..."
        PKGBUILD_POSTFIX="local"
        mkdir -p "$DESTINATION_PATH" # Create the directory used by `makepkg` for sources

        pacman -Qq rsync > /dev/null || sudo pacman -S --needed rsync # Install rsync if not already installed
        rsync --archive --human-readable --progress --update "$SOURCE_PATH/." "$DESTINATION_PATH" # Copy the sources from local directory
        rsync --archive --human-readable --progress --update "$PROJECT_DIRECTORY/packaging/archlinux/$PACKAGE_NAME.desktop" "$DESTINATION_PATH" # Copy the desktop file from local directory

        CURRENT_BRANCH=$(cd "$PROJECT_DIRECTORY" && git branch --show-current)
        if [ -n "$BRANCH" ]; then
          echo "Checking out the branch: $BRANCH..."
          (cd "$DESTINATION_PATH" && git checkout "$BRANCH")
        else
          echo "No specific git branch specified. Not checking out..."
        fi 
    else
        PKGBUILD_POSTFIX="git"
    fi

    if [ "$CLEAN" == "y" ]; then
        CLEAN_ARGUMENT="--cleanbuild"
    else
        CLEAN_ARGUMENT=""
    fi 

    if [ "$INSTALL" == "y" ]; then
        INSTALL_ARGUMENT="--install"
    else
        INSTALL_ARGUMENT=""
    fi 

    ( # Create a subshell to prevent directory changes outside
      cd "$PROJECT_DIRECTORY/packaging/archlinux" && \
      BUILDDIR="$BUILD_DIRECTORY" \
      MAKEFLAGS="-j$(nproc)" \
      makepkg -p "PKGBUILD-$PKGBUILD_POSTFIX" \
          "$CLEAN_ARGUMENT" \
          --noextract \
          --force \
          "$INSTALL_ARGUMENT" \
          --syncdeps \
          --sign
    )
}

while :
do
  case "$1" in
    -s | --source )
      SOURCE="$2"
      SOURCE="$SOURCE" | awk '{print tolower($0)}'
      shift 2
      ;;
    -t | --target )
      TARGET="$2"
      TARGET="$TARGET" | awk '{print tolower($0)}'
      shift 2
      ;;
    -b | --branch )
      BRANCH="$2"
      BRANCH="$BRANCH" | awk '{print tolower($0)}'
      shift 2
      ;;
    -c | --clean )
      CLEAN="y"
      shift
      ;;
    -i | --install )
      INSTALL="y"
      shift
      ;;
    -h | --help)
      display_help
      exit 0
      ;;
    --)
      shift;
      break
      ;;
    *)
      echo "Unexpected option: $1" 1>&2
      display_help
      exit 2
      ;;
  esac
done

echo ""
echo "Package build script for $PACKAGE_NAME"
echo ""
echo "The makepkg build directory is set to: $BUILD_DIRECTORY"
build_package "$TARGET" "$SOURCE" "$BRANCH" "$CLEAN" "$INSTALL" 
echo ""



