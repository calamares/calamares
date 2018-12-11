# Build configuration on Travis.
#
# Defines a CMAKE_ARGS variable for use with cmake
#
# This file is sourced by travis.sh, and exports the variables
# to the environment.
CMAKE_ARGS="\
  -DCMAKE_BUILD_TYPE=Release \
  -DWEBVIEW_FORCE_WEBKIT=1 \
  -DKDE_INSTALL_USE_QT_SYS_PATHS=ON \
  -DWITH_PYTHONQT=OFF"

export CMAKE_ARGS
