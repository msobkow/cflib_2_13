#!/bin/bash
Revision=$1
Build=`echo $Revision | cut --delimiter='-' -f 1`
if [ "$Revision" == "" ]; then
	echo "ERROR: Revision (argument 1) not specified" 1>&2
else
	cd $MSSCFHOME/cflib_2_13/java
	if [ ! -d ../installer ]; then
		mkdir ../installer
	fi
	export Revision
	archiveFileName="../installer/cflib_2_13_${Revision}-DualLGPLv3-java-installer.zip"
	export archiveFileName
	rm -f ${archiveFileName}
	rm -f bin/*.jar
	cp ~/.m2/repository/org/msscf/msscf/v2_13/org.msscf.msscf.v2_13.cflib*/2.13.${Build}/*-2.13.${Build}.jar bin
	if [ -d bin/testdata ]; then
		zip -q9r ${archiveFileName} bin/testdata
	fi
	if [ -d bin/initdata ]; then
		zip -q9r ${archiveFileName} bin/initdata
	fi
	echo "Packaging ${archiveFileName} ..."
	tomcatlibopt=""
	if [ -d ./bin/tomcatlib ]; then
		tomcatlibs=`find ./bin/tomcatlib -name '*.jar'`
		tomcatlibopt=" ${tomcatlibs}"
	fi
	ls -1 ChangeLog ./bin/*.jar ${tomcatlibopt} *txt LICENSE `find bin -name '*.txt' -o -name 'LICENSE' -o -name '*.war' -o -name '*.xsd' -o -name '*.xml' -o -name '*.bash' -o -name '*.bat' -o -name '*.cmd' ` | zip '-q9@' ${archiveFileName}
	echo "Packaged ${archiveFileName}"
	ls -l ${archiveFileName}
	if [ -d bin/testdata ]; then
		zip -q9r ${archiveFileName} bin/testdata
	fi
	if [ -d bin/initdata ]; then
		zip -q9r ${archiveFileName} bin/initdata
	fi
fi
