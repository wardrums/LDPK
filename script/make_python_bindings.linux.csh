#!/bin/csh -x

set basedir=`dirname $PWD/$0`
setenv CC "g++"
setenv SHARED "-shared"
setenv OPT "-O2 -fPIC"
setenv INCPATH "-I $basedir/../include"

# Insert your python header directory here or let me find the latest 2.x
if -e /usr/include/python2.7 then
	setenv INCPYTHON "-I /usr/include/python2.7"
else if -e /usr/include/python2.6 then
	setenv INCPYTHON "-I /usr/include/python2.6"
else if -e /usr/include/python2.5 then
	setenv INCPYTHON "-I /usr/include/python2.5"
else
	unset echo
	echo "No python headers found. Is python installed?"
	exit
endif

# internal/sdv:
if `hostname` == "devil" then
	setenv INCPYTHON "-I /server/devel/extern/linux64/python_sdv/install_dir/include/python2.6"
endif

cd $basedir/../source/ldpk

# Compile the python module. Import this e.g. with:
# >>> import lens_distortion_plugins as ldp
$CC $OPT $SHARED tde4_lens_distortion_plugins.module.C $INCPYTHON $INCPATH -o ../../python/linux/lens_distortion_plugins.so
