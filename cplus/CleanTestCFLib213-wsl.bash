#!/bin/bash
#
rm -f libtestcflib*.gz *.deb *.build *.dsc *.log *.changes ex.cmd
pushd testcflib
	if [ -f Makefile ]; then
		make distclean
	fi
popd
