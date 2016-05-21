#!/bin/csh -x

set basedir=`dirname $PWD/$0`
cd $basedir

pushd ../doc/sphinx
setenv PYTHONPATH ../../python/linux
make clean
make doctest
make html
popd


