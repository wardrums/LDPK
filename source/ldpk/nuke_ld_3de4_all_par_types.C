// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/nuke_ld_3de4_base.h>
#include <ldpk/tde4_ldp_all_par_types.h>

#define CLASS_LDP_SDV         tde4_ldp_all_par_types
#define CLASS_IOP_SDV     iop_tde4_ldp_all_par_types
#define CREATE_SDV create_iop_tde4_ldp_all_par_types

//! @file nuke_ld_3de4_anamorphic_standard_degree_4.C

// This is the name that NUKE will use to store this operator in the
// scripts. So that NUKE can locate the plugin, this must also be the
// name of the compiled plugin (with .so/.dll/.dylib added to the end):
static const char* const CLASS = "LD_3DE4_All_Parameter_Types";

// This text will be displayed in a popup help box on the node's panel:
static const char* const HELP = "3DE4 sample model which contains all types of parameters...\n";

//! Nuke plugin based on tde4_ldp_all_par_types
class iop_tde4_ldp_all_par_types:public nuke_ld_3de4_base
	{
public:
	CLASS_IOP_SDV(Node* node):nuke_ld_3de4_base(node,new CLASS_LDP_SDV<ldpk::vec2d,ldpk::mat2d>())
		{ }
	const char* Class() const
		{ return CLASS; }
	const char* node_help() const
		{ return HELP; }
	};

// So wird das woanders auch gemacht. Bauen wir einfach nach.
static DD::Image::Iop* CREATE_SDV(Node* node)
	{
	return (new DD::Image::NukeWrapper (new CLASS_IOP_SDV(node)))->noMix()->noMask();
	}
const DD::Image::Iop::Description nuke_ld_3de4_base::description(CLASS,0,CREATE_SDV);

