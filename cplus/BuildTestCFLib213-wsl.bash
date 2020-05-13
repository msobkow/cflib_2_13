#!/bin/bash
#
let Revision=$1
if [ "$Revision" == "" ]; then
	echo "BuildCFLib211-wsl.bash ERROR: Revision (argument 1) must be specified"
else
	rm -f libtestcflib*.gz *.deb *.build *.dsc *.log *.changes ex.cmd
	pushd testcflib
		if [ -f Makefile ]; then
			make distclean
		fi
	popd
	echo ":1,\$s:[0-9][0-9][0-9][0-9][0-9]:${Revision}:g" >ex.cmd
	echo ":1,\$s:[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]:0133456789:g" >>ex.cmd
	echo ":wq" >> ex.cmd
	ex testcflib/configure.ac < ex.cmd
	ex testcflib/Makefile.am < ex.cmd
	rm ex.cmd
	pushd testcflib
		autoreconf -fi
		aclocal
		autoconf
		automake
		./configure --prefix=/usr --disable-static CFLAGS='-g3 -Og -D_DEBUG' CXXFLAGS='-g3 -Og -std=c++2a -D_DEBUG -I. -I/usr/include/msobkow/2.0.13 -I/usr/include/msobkow/2.0.13'
		#./configure --prefix=/usr --disable-static CFLAGS='-O2 -DNDEBUG' CXXFLAGS='-O2 -std=c++2a -DNDEBUG -I. -I/usr/include/msobkow/2.0.13 -I/usr/include/msobkow/2.0.13'
		make clean
		make
		sudo make install
		sudo chmod 755 /usr/bin/msobkow
		sudo chmod 755 /usr/bin/msobkow/2.0.13
		sudo chmod 755 /usr/bin/msobkow/2.0.13/testcflib
		#sudo chmod 755 /usr/include/msobkow/2.0.13/testcflib
		#sudo sh -c "cd /usr/include/msobkow/2.0.13/testcflib && chmod 644 *.hpp"
		sudo ldconfig
	popd
fi
