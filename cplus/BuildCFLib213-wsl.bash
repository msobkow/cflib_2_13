#!/bin/bash
#
let Revision=$1
if [ "$Revision" == "" ]; then
	echo "BuildCFLib211-wsl.bash ERROR: Revision (argument 1) must be specified"
else
	rm -f libcflib*.gz *.deb *.build *.dsc *.log *.changes ex.cmd
	pushd libcflib
		if [ -f Makefile ]; then
			make distclean
		fi
	popd
	if [ ! -d /usr/bin/msobkow ]; then
		sudo mkdir /usr/bin/msobkow
	fi
	sudo chmod 755 /usr/bin/msobkow
	if [ ! -d /usr/bin/msobkow/2.0.13 ]; then
		sudo mkdir /usr/bin/msobkow/2.0.13
	fi
	sudo chmod 755 /usr/bin/msobkow/2.0.13
	if [ ! -d /usr/share ]; then
		sudo mkdir /usr/share
	fi
	sudo chmod 755 /usr/share
	if [ ! -d /usr/share/msobkow ]; then
		sudo mkdir /usr/share/msobkow
	fi
	sudo chmod 755 /usr/share/msobkow
	if [ ! -d /usr/share/msobkow/2.0.13 ]; then
		sudo mkdir /usr/share/msobkow/2.0.13
	fi
	sudo chmod 755 /usr/share/msobkow/2.0.13
	if [ ! -d /usr/share/msobkow/2.0.13/xsd ]; then
		sudo mkdir /usr/share/msobkow/2.0.13/xsd
	fi
	sudo chmod 755 /usr/share/msobkow/2.0.13/xsd
	if [ ! -d /usr/include/msobkow ]; then
		sudo mkdir /usr/include/msobkow
	fi
	sudo chmod 755 /usr/include/msobkow
	if [ ! -d /usr/include/msobkow/2.0.13 ]; then
		sudo mkdir /usr/include/msobkow/2.0.13
	fi
	sudo chmod 755 /usr/include/msobkow/2.0.13
	if [ ! -d /usr/include/msobkow/2.0.13/cflib ]; then
		sudo mkdir /usr/include/msobkow/2.0.13/cflib
	fi
	sudo chmod 755 /usr/include/msobkow/2.0.13/cflib
	echo ":1,\$s:[0-9][0-9][0-9][0-9][0-9]:${Revision}:g" >ex.cmd
	echo ":1,\$s:[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]:0133456789:g" >>ex.cmd
	echo ":wq" >> ex.cmd
	ex libcflib/CFLib.cpp < ex.cmd
	ex libcflib/configure.ac < ex.cmd
	ex libcflib/Makefile.am < ex.cmd
	ex libcflib/cflib/Makefile.am < ex.cmd
	rm ex.cmd
	pushd libcflib
		autoreconf -fi
		aclocal
		autoconf
		automake
		./configure --prefix=/usr --disable-static CFLAGS='-g3 -Og -D_DEBUG' CXXFLAGS='-g3 -Og -std=c++2a -D_DEBUG -I. -I/usr/include/msobkow/2.0.13 -I/usr/include/msobkow/2.0.13'
		#./configure --prefix=/usr --disable-static CFLAGS='-O2 -DNDEBUG' CXXFLAGS='-O2 -std=c++2a -DNDEBUG -I. -I/usr/include/msobkow/2.0.13 -I/usr/include/msobkow/2.0.13'
		make clean
		make
		sudo make install
		sudo rm -Rf /usr/include/cflib
		sudo chmod 755 /usr/bin
		sudo chmod 755 /usr/bin/msobkow
		sudo chmod 755 /usr/bin/msobkow/2.0.13
		#sudo chmod 755 /usr/bin/msobkow/2.0.13/*cflib*
		sudo chmod 755 /usr/include/msobkow
		sudo chmod 755 /usr/include/msobkow/2.0.13
		sudo chmod 755 /usr/include/msobkow/2.0.13/cflib
		sudo sh -c "cd /usr/include/msobkow/2.0.13/cflib && chmod 644 *.hpp"
		sudo chmod 755 /usr/share/msobkow
		sudo chmod 755 /usr/share/msobkow/2.0.13
		sudo chmod 755 /usr/share/msobkow/2.0.13/xsd
		sudo chmod 644 /usr/share/msobkow/2.0.13/xsd/cftip*.xsd
		sudo ldconfig
	popd
fi
