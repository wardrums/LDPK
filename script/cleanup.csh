#!/bin/csh -v

set basedir=`dirname $PWD/$0`

rm -rf $basedir/../source/ldpk/*.o
rm -rf $basedir/../test/*.o
rm -rf $basedir/../test/*.dSYM
rm -rf $basedir/../lib/*.o
rm -rf $basedir/../lib/*.dSYM
rm -rf $basedir/../bin/*.dSYM

cd $basedir/../bin
rm -f test_lookup_table_iter
rm -f test_radial_decentered_distortion
rm -f test_generic_radial_distortion
rm -f test_plugin_loader
rm -f test_model_visualizer

cd $basedir/../lib
rm -f libldpk.a
rm -f tde4_ldp_*.so

cd $basedir/../doc
rm -rf doxy/html/*

cd $basedir/../
rm -rf tmp/*
