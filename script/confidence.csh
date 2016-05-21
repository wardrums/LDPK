#!/bin/csh

# Use this script to test the pre-compiled libraries and modules.
# Run this and redirect standard output to some file,
# then compare your file to ours (out.confidence.<arch>.sdv).
# In the ideal case, they are identical, but there may be slight(!) differences
# in the numbers due to rounding errors or representation mismatch between the platforms.

if `uname` == "Linux" then
	setenv OS_SUFFIX "linux"
else if `uname` == "Darwin" then
	setenv OS_SUFFIX "osx"
endif

set basedir=`dirname $PWD/$0`
setenv LDPK $basedir/..

# Test 1
# - check if tde4_plugin_info is running
# - presence of the five precompiled lens distortion models
# - parameter names, types, default values and ranges
foreach name (`ls $LDPK/compiled/ldpk/$OS_SUFFIX/lib/tde4*.so`)
	$LDPK/bin/$OS_SUFFIX/tde4_plugin_info $name
end

# Test 2
# - check if precompiled python_bindings work
setenv PYTHONPATH $LDPK/python/$OS_SUFFIX
python $LDPK/python/test_lens_distortion_plugins.py
