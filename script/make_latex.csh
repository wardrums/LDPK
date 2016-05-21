#!/bin/csh -x

set basedir=`dirname $PWD/$0`
cd $basedir

pushd ../latex
latex ldpk.tex
latex ldpk.tex
dvipdf ldpk.dvi ../doc/tex/ldpk.pdf
popd

