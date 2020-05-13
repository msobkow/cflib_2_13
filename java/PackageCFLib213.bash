#!/bin/bash
Revision=$1
if [ "$Revision" == "" ]; then
	echo "ERROR: Revision (argument 1) not specified" 1>&2
else
	cd $MSSCFHOME/cflib_2_13/java
	if [ ! -d ../installer ]; then
		mkdir ../installer
	fi
	export Revision
	archiveFileName="../installer/cflib_2_13_${Revision}-LGPLv3-java-installer.zip"
	export archiveFileName
	rm -f ${archiveFileName}
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
	ls -1 ChangeLog ./bin/*.jar ./bin/lib/*.jar ${tomcatlibopt} lgpl-3.0.txt LICENSE `find bin -name 'lgpl-3.0.txt' -o -name 'LICENSE' -o -name '*.war' -o -name '*.xsd' -o -name '*.xml' -o -name '*.bash' -o -name '*.bat' -o -name '*.cmd' ` | zip '-q9@' ${archiveFileName}
	echo "Packaged ${archiveFileName}"
	ls -l ${archiveFileName}
	if [ -d bin/testdata ]; then
		zip -q9r ${archiveFileName} bin/testdata
	fi
	if [ -d bin/initdata ]; then
		zip -q9r ${archiveFileName} bin/initdata
	fi
fi
