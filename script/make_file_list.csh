#!/bin/csh

set basedir=`dirname $PWD/$0`
cd $basedir

python make_file_list.py -path $basedir/.. -linkbase ../../.. -format html -charset utf-8 -order dirs -exclude doc/doxy/html > ../doc/misc/files.html

cat ../doc/misc/pre_lof.html ../doc/misc/files.html ../doc/misc/post_lof.html > ../doc/misc/list_of_files.html
