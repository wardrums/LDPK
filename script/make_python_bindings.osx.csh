#!/bin/csh -x

set basedir=`dirname $PWD/$0`
setenv CC "g++"
setenv SHARED "-dynamiclib"
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

# Check if you need 64-bit or 32-bit on OSX 10.5
#setenv OPT "-O2 -arch x86_64 -fPIC"
setenv OPT "-O2 -fPIC"

cd $basedir/../source/ldpk

# Compile the python module. Import this e.g. with:
# >>> import lens_distortion_plugins as ldp
$CC $OPT $SHARED tde4_lens_distortion_plugins.module.C $INCPYTHON $INCPATH -lpython -o ../../python/osx/lens_distortion_plugins.so
