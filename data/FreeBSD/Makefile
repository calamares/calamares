# $FreeBSD$
# 
# SPDX-FileCopyrightText: 2020 Adriaan de Groot <adridg@FreeBSD.org>
# SPDX-License-Identifier: BSD-2-Clause

PORTNAME=	calamares
DISTVERSION=	3.2.25
CATEGORIES=	sysutils
MASTER_SITES=	https://github.com/${PORTNAME}/${PORTNAME}/releases/download/v${DISTVERSION}/

MAINTAINER=	adridg@FreeBSD.org
COMMENT=	GUI System installer and OEM configurator

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libyaml-cpp.so:devel/yaml-cpp \
		libpwquality.so:security/libpwquality \
		libboost_python${PYTHON_SUFFIX}.so:devel/boost-python-libs

USES=		cmake compiler:c++17-lang gettext kde:5 pkgconfig \
		python:3.3+ qt:5
USE_QT=		concurrent core dbus declarative gui \
		network quickcontrols2 svg widgets xml \
		buildtools_build linguist_build qmake_build
USE_KDE=	coreaddons dbusaddons parts service \
		ecm_build
USE_LDCONFIG=	yes

CMAKE_OFF=	WITH_KF5Crash \
		INSTALL_CONFIG \
		INSTALL_COMPLETION \
		INSTALL_POLKIT
CMAKE_ON=	CMAKE_DISABLE_FIND_PACKAGE_KPMcore
CMAKE_ARGS=	-DSKIP_MODULES="webview"

.include <bsd.port.mk>
