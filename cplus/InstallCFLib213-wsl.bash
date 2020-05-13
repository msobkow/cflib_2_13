#!/bin/bash
#
MAJOR_VERSION=2
MINOR_VERSION=13
pushd libcflib
	sudo make install
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
