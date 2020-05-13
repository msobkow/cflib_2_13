#!/bin/bash
#
rm -f libcflib*.gz *.deb *.build *.dsc *.log *.changes ex.cmd
pushd libcflib
	if [ -f Makefile ]; then
		make distclean
	fi
popd
