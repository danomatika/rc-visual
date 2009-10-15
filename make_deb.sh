#! /bin/bash

# make a Debian package

NAME="rc-visual"

# library/build depenencies
DEPENDS="libsdl1.2debian, libsdl-gfx1.2-4, liblo0ldbl"

# exit if checkinstall is not installed
if [ ! -e "/usr/bin/checkinstall" ] ; then
	echo "cannot build deb package, checkinstall is not installed"
	sleep 2
	exit 0
fi

# build the package
checkinstall -D -y --install=no --pkgname="$NAME" --pkgversion="0.4.0" \
--requires="$DEPENDS" --maintainer="danomatika@gmail.com" --deldoc=yes \
--strip=no --stripso=no --deldesc=yes --delspec=yes

