// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/nuke_ld_3de4_base.h>
#include <ldpk/tde4_ldp_classic_3de_mixed.h>

#define CLASS_LDP_SDV         tde4_ldp_classic_3de_mixed
#define CLASS_IOP_SDV     iop_tde4_ldp_classic_3de_mixed
#define CREATE_SDV create_iop_tde4_ldp_classic_3de_mixed


//! @file nuke_ld_3de_classic_ld_model.C

// This is the name that NUKE will use to store this operator in the
// scripts. So that NUKE can locate the plugin, this must also be the
// name of the compiled plugin (with .so/.dll/.dylib added to the end):
static const char* const CLASS = "LD_3DE_Classic_LD_Model";

// This text will be displayed in a popup help box on the node's panel:
static const char* const HELP = "3DE classic lens distortion model, mixed degree 2 with 4. Works, but we recommend to use LD_3DE_Radial_Standard_Degree_4 or LD_3DE4_Anamorphic_Standard_Degree_4 instead.\n";

//! Nuke plugin based on tde4_ldp_classic_3de_mixed
class iop_tde4_ldp_classic_3de_mixed:public nuke_ld_3de4_base
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

// g++ -g -O2 -shared -fPIC ld_3de_classic_ld_model.C nuke_ld_3de4_base.C -I $server/software/linux64/nuke/Nuke7.0v9/include -I ../../include -L $server/software/linux64/nuke/Nuke7.0v9/lib -o ../../compiled/nuke/Nuke7.0/LD_3DE_Classic_LD_Model.so
