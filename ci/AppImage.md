# AppImage building for Calamares

> It is possible to build Calamares as an AppImage (perhaps other
> containerized formats as well). This might make sense for
> OEM phase-1 deployments in environments where Calamares is
> not using the native toolkit.

## AppImage tools

You will need
 - [`linuxdeploy-x86_64.AppImage`](https://github.com/linuxdeploy/linuxdeploy/releases)
 - [`linuxdeploy-plugin-qt-x86_64.AppImage`](https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases)
 - [`linuxdeploy-plugin-conda.sh`](https://github.com/linuxdeploy/linuxdeploy-plugin-conda)

These tools should run -- they are bundled as AppImages after all -- on
any modern Linux system. The [AppImage packaging documentation](https://docs.appimage.org/packaging-guide/)
explains how the whole tooling works.

If the tools are not present, the build script (see below) will download them,
but you should save them for later.

## AppImage build

From the **source** directory, run `ci/AppImage.sh`:
 - Use `--tools-dir` to copy the tools from a local cache rather than
   downloading them again.
 - Run it with `--cmake-args` for special CMake handling.
 - Use `--skip-build` to avoid rebuilding Calamares all the time.
 - Use `--config-dir` to copy in Calamares configuration files (e.g.
   *settings.conf* and the module configuration files) from a given
   directory.

The build process will:
 - copy (or download) the AppImage tools into a fresh build directory
 - configure and build Calamares with suitable settings
 - modifies the standard `.desktop` file to be AppImage-compatible
 - builds the image with the AppImage tools

## AppImage caveats

The resulting AppImage, `Calamares-x86_64.AppImage`, can be run as if it is
a regular Calamares executable. For internal reasons it always passes the
`-X` flag; any other command-line flags are passed in unchanged. Internally,
`XDG_*_DIRS` are used to get Calamares to find the resources inside the AppImage
rather than in the host system.
