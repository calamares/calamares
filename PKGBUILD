pkgname=calamares
pkgver=3.2.0
_pkgver=3.2.0
pkgrel=6
pkgdesc='Distribution-independent installer framework'
arch=('i686' 'x86_64')
license=(GPL)
url="https://github.com/casualx85/calamares"
license=('LGPL')
depends=('kconfig' 'kcoreaddons' 'kiconthemes' 'ki18n' 'kio' 'solid' 'yaml-cpp' 'kpmcore>=3.3.0' 'mkinitcpio-openswap'
         'boost-libs' 'ckbcomp' 'hwinfo' 'qt5-svg' 'polkit-qt5' 'gtk-update-icon-cache' 'pythonqt>=3.2')
makedepends=('extra-cmake-modules' 'qt5-tools' 'qt5-translations' 'git' 'boost')
backup=('usr/share/calamares/modules/bootloader.conf'
        'usr/share/calamares/modules/displaymanager.conf'
        'usr/share/calamares/modules/initcpio.conf'
        'usr/share/calamares/modules/unpackfs.conf')

#source+=(#"$pkgname-$pkgver.tar.gz::https://github.com/casualx85/calamares/archive/v${_pkgver}.tar.gz"
#         "$pkgname-$pkgver-$pkgrel.tar.gz::$url/-/archive/3.2.x-stable/calamares-3.2.x-stable.tar.gz")
source+=()
#sha256sums=('06cf6c4f7b9ff3b5a74eda44d25c3ea7fe697ca5af1dc1c691543b138c69fc5a')

prepare() {
	mv ${srcdir}/calamares-3.2.x-stable ${srcdir}/calamares-${_pkgver}
	cd ${srcdir}/calamares-${_pkgver}

	# patches here

	# add revision
	_patchver="$(cat CMakeLists.txt | grep -m3 -e CALAMARES_VERSION_PATCH | grep -o "[[:digit:]]*" | xargs)"
	sed -i -e "s|CALAMARES_VERSION_PATCH $_patchver|CALAMARES_VERSION_PATCH $_patchver-$pkgrel|g" CMakeLists.txt
}

build() {
	cd ${srcdir}/calamares-${_pkgver}

	mkdir -p build
	cd build
        cmake .. \
              -DCMAKE_BUILD_TYPE=Release \
              -DCMAKE_INSTALL_PREFIX=/usr \
              -DCMAKE_INSTALL_LIBDIR=/usr/lib64 \
              -DWITH_PYTHONQT:BOOL=ON \
              #-DSKIP_MODULES="webview interactiveterminal initramfs \
              #                initramfscfg dracut dracutlukscfg \
              #                dummyprocess dummypython dummycpp \
              #                dummypythonqt plasmalnf"
        make
}

package() {
	cd ${srcdir}/calamares-${_pkgver}/build
	make DESTDIR="$pkgdir" install
	install -Dm644 "../data/anthuresta-icon.svg" "$pkgdir/usr/share/icons/hicolor/scalable/apps/calamares.svg"
	install -Dm644 "../data/calamares.desktop" "$pkgdir/usr/share/applications/calamares.desktop"
	install -Dm755 "../data/calamares_polkit" "$pkgdir/usr/bin/calamares_polkit"
	install -Dm644 "../data/49-nopasswd-calamares.rules" "$pkgdir/etc/polkit-1/rules.d/49-nopasswd-calamares.rules"
	chmod 750      "$pkgdir"/etc/polkit-1/rules.d
}