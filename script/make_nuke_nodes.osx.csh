#!/bin/csh -x

# internal/sdv: execute on bigmuff.

unset echo
if (`hostname` != "bigmuff.fritz.box" && `hostname` != "bigmuff") then
	unset echo
	echo "***************************************************"
	echo "Please edit this script, enter your path(s) to Nuke "
	echo "and remove this error condition."
	echo "***************************************************"
	exit
endif
set echo

set basedir=`dirname $PWD/$0`
set CC="g++"
setenv OPT "-O2 -fPIC"
setenv SHARED "-dynamiclib"
setenv INC_LDPK "-I $basedir/../include"

if `hostname` == "bigmuff.fritz.box" then
# our compiled stuff goes here:
	setenv TARGET_DIR "compiled"
else if `hostname` == "bigmuff" then
# our compiled stuff goes here:
	setenv TARGET_DIR "compiled"
else
# your results here please:
	setenv TARGET_DIR "lib"
endif

cd $basedir/../source/ldpk

########################### Nuke 6.2 ###########################
unset echo
setenv NUKE_VERSION "6.2"
setenv INC_NUKE "-I /Applications/Nuke6.2v5/Nuke6.2v5.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/Applications/Nuke6.2v5/Nuke6.2v5.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

########################### Nuke 6.3 ###########################
unset echo
setenv NUKE_VERSION "6.3"
setenv INC_NUKE "-I /Applications/Nuke6.3v9/Nuke6.3v9.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/Applications/Nuke6.3v9/Nuke6.3v9.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

########################### Nuke 7.0 ###########################
unset echo
setenv NUKE_VERSION "7.0"
setenv INC_NUKE "-I /Applications/Nuke7.0v8/Nuke7.0v8.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/Applications/Nuke7.0v8/Nuke7.0v8.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

########################### Nuke 8.0 ###########################
unset echo
setenv NUKE_VERSION "8.0"
setenv INC_NUKE "-I /Applications/Nuke8.0v7/Nuke8.0v7.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/Applications/Nuke8.0v7/Nuke8.0v7.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

########################### Nuke 9.0 ###########################
unset echo
setenv NUKE_VERSION "9.0"
setenv INC_NUKE "-I /server/software/osx64/nuke/Nuke9.0v1/Nuke9.0v1.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/server/software/osx64/nuke/Nuke9.0v1/Nuke9.0v1.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

########################### Nuke 10.0 ###########################
unset echo
setenv NUKE_VERSION "10.0"
setenv INC_NUKE "-I /server/software/osx64/nuke/Nuke10.0v1/Nuke10.0v1.app/Contents/MacOS/include/"
setenv LIB_NUKE "-L/server/software/osx64/nuke/Nuke10.0v1/Nuke10.0v1.app/Contents/MacOS/ -lDDImage"
mkdir -p $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.dylib
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.dylib
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.dylib
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.dylib
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/osx/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.dylib

unset echo
echo "**********************************************************"
echo "Plugins should now be in LDPK/$TARGET_DIR/nuke/osx/NukeX.Y/"
echo "Please copy them to your Nuke plugins directory."
echo "All plugin names start with 'LD_3DE...'."
echo "**********************************************************"
