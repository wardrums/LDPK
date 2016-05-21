#!/bin/csh -x

# internal/sdv: execute on devil.

unset echo
if (`hostname` != "devil") then
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
setenv SHARED "-shared"
setenv INC_LDPK "-I $basedir/../include"

if `hostname` == "devil" then
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
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke6.2v4/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke6.2v4"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

########################### Nuke 6.3 ###########################
unset echo
setenv NUKE_VERSION "6.3"
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke6.3v8/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke6.3v8"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

########################### Nuke 7.0 ###########################
unset echo
setenv NUKE_VERSION "7.0"
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke7.0v9/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke7.0v9"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

########################### Nuke 8.0 ###########################
unset echo
setenv NUKE_VERSION "8.0"
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke8.0v1/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke8.0v1"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

########################### Nuke 9.0 ###########################
unset echo
setenv NUKE_VERSION "9.0"
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke9.0v1/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke9.0v1"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C				nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C				nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

########################### Nuke 10.0 ###########################
unset echo
setenv NUKE_VERSION "10.0"
setenv INC_NUKE "-I $server/software/linux64/nuke/Nuke10.0v1/include"
setenv LIB_NUKE "-L $server/software/linux64/nuke/Nuke10.0v1"
mkdir -p $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION
set echo

$CC $OPT $SHARED nuke_ld_3de4_anamorphic_degree_6.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Degree_6.so
$CC $OPT $SHARED nuke_ld_3de4_anamorphic_standard_degree_4.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Anamorphic_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8.C			nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8.so
$CC $OPT $SHARED nuke_ld_3de4_radial_standard_degree_4.C		nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Standard_Degree_4.so
$CC $OPT $SHARED nuke_ld_3de_classic_ld_model.C				nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE_Classic_LD_Model.so
$CC $OPT $SHARED nuke_ld_3de4_all_par_types.C				nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_All_Parameter_Types.so

unset echo
echo "**********************************************************"
echo "Plugins should now be in LDPK/$TARGET_DIR/nuke/linux/NukeX.Y/"
echo "Please copy them to your Nuke plugins directory."
echo "All plugin names start with 'LD_3DE...'."
echo "**********************************************************"

# $CC $OPT $SHARED nuke_ld_3de4_radial_fisheye_degree_8_release_1.C	nuke_ld_3de4_base.C $INC_LDPK $INC_NUKE $LIB_NUKE -o $basedir/../$TARGET_DIR/nuke/linux/Nuke$NUKE_VERSION/LD_3DE4_Radial_Fisheye_Degree_8_Release_1.so
