#!/bin/bash
Revision=$1
if [ "$Revision" == "" ]; then
	echo "ERROR: Revision (argument 1) not specified" 1>&2
else
	export Revision
	cd $MSSCFHOME/cflib_2_13/cplus
	if [ ! -d ../installer ]; then
		mkdir ../installer
	fi
	chmod 755 ../installer
	ZipFile="../installer/cflib_2_13_${Revision}-LGPLv3-wsl-debug-installer.zip"
	export ZipFile
	rm -f ${ZipFile}
	rm -Rf cflib-2.13.${Revision}-wsl
	mkdir cflib-2.13.${Revision}-wsl
	chmod 755 cflib-2.13.${Revision}-wsl
	echo "Preparing cflib-2.13.${Revision}-wsl ..."
	pushd cflib-2.13.${Revision}-wsl
		cp ../lgpl-3.0.txt ../LICENSE .
		git log 2>&1 >ChangeLog
		mkdir bin
		chmod 755 bin
		mkdir bin/msobkow
		chmod 755 bin/msobkow
		mkdir bin/msobkow/2.0.13
		chmod 755 bin/msobkow/2.0.13
		cp ../lgpl-3.0.txt ../LICENSE bin/msobkow/2.0.13
		chmod 644 bin/msobkow/2.0.13/*
		cp /usr/bin/msobkow/2.0.13/testcflib bin/msobkow/2.0.13
		chmod 755 bin/msobkow/2.0.13/testcflib
		mkdir lib
		chmod 755 lib
		cp /usr/lib/libcflib.la /usr/lib/libcflib.so.2.0.13 lib
		chmod 755 lib/*.so.*
		chmod 644 lib/*.la
		strip bin/msobkow/2.0.13/*cf* lib/*.so.*
		mkdir include
		chmod 755 include
		mkdir include/msobkow
		chmod 755 include/msobkow
		mkdir include/msobkow/2.0.13
		chmod 755 include/msobkow/2.0.13
		cp ../lgpl-3.0.txt ../LICENSE include/msobkow/2.0.13
		chmod 644 include/msobkow/2.0.13/*
		mkdir include/msobkow/2.0.13/cflib
		chmod 755 include/msobkow/2.0.13/cflib
		cp /usr/include/msobkow/2.0.13/cflib/*.hpp include/msobkow/2.0.13/cflib
		chmod 644 include/msobkow/2.0.13/cflib*/*.hpp
		mkdir share
		chmod 755 share
		mkdir share/msobkow
		chmod 755 share/msobkow
		mkdir share/msobkow/2.0.13
		chmod 755 share/msobkow/2.0.13
		cp ../lgpl-3.0.txt ../LICENSE share/msobkow/2.0.13
		chmod 644 share/msobkow/2.0.13/*
		mkdir share/msobkow/2.0.13/xsd
		chmod 755 share/msobkow/2.0.13/xsd
		cp /usr/share/msobkow/2.0.13/xsd/cftip*.xsd share/msobkow/2.0.13/xsd
		chmod 644 share/msobkow/2.0.13/xsd/*.xsd
	popd
	echo "Packaging cflib-2.13.${Revision}-wsl ..."
	zip -q9r ${ZipFile} cflib-2.13.${Revision}-wsl
	rm -Rf cflib-2.13.${Revision}-wsl
	echo "Packaged ${ZipFile}"
	ls -l ${ZipFile}
fi
