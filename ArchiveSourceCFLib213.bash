#!/bin/bash
#
export build_tag=$*
if [ "$build_tag" == "" ]; then
	echo "ArchiveSourceCFLib213.bash ERROR A single argument build tag must be specified"
else
	if [ "${MSSCFHOME}" == "" ]; then
		echo "ArchiveSourceCFLib213.bash ERROR MSSCFHOME environment variable not found or is empty"
	else
		if [ ! -d ${MSSCFHOME} ]; then
			echo "ArchiveSourceCFLib213.bash ERROR MSSCFHOME directory ${MSSCFHOME} does not exist"
		else
			pushd ${MSSCFHOME}
				aproj=cflib
				if [ -d ${aproj}_2_13 ]; then
					pushd ${aproj}_2_13
						if [ ! -d installer ]; then
							mkdir installer
							chmod 755 installer
						fi
						archiveFileName="installer/${aproj}_2_13_${build_tag}-LGPLv3-src.zip"
						if [ -f ${archiveFileName} ]; then
							rm -f ${archiveFileName}
						fi
						echo "Archiving ${archiveFileName} ..."
						find . -name 'ChangeLog' -o -name 'README.md' -o -name 'lgpl-3.0.txt' -o -name 'LICENSE' -o -name '.gitattributes' -o -name '.gitignore' -o -name '*.bash' -o -name '*.bat' -o -name '*.cmd' -o -name '*.gif' -o -name '*.png' -o -name '*.wav' -o -name '*.xsd' -o -name '*.xml' -o -name '*.java' -o -name '*.cpp' -o -name '*.hpp' -o -name 'Makefile.am' -o -name 'configure.ac' -o -name '*.csproj' -o -name '*.cs' -o -name '*.sql' -o -name '*.tsql' -o -name '*.isql' -o -name '*.pgsql' -o -name '*.plsql' -o -name '*.mysql' | grep -v build | zip '-q9@' ${archiveFileName}
						ls -l ${archiveFileName}
					popd
				fi
			popd
		fi
	fi
fi
