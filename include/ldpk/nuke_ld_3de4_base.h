// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <DDImage/Iop.h>
#include <DDImage/Box.h>
#include <DDImage/Filter.h>
#include <DDImage/Knobs.h>
#include <DDImage/Pixel.h>
#include <DDImage/Row.h>
#include <DDImage/Tile.h>
#include <DDImage/NukeWrapper.h>
#include <ldpk/ldpk_ldp_builtin.h>

using namespace std;

//! @brief The baseclass for Nuke plugins around LDPK-based lens distortion models.
//! In order to implement a Nuke plugin, derive from this class.
class nuke_ld_3de4_base:public DD::Image::Iop
	{
private:
	DD::Image::Filter _filter;
// Anzahl der modellabhaengigen Parameter, wird im Konstruktor ermittelt.
	int _num_par;
// Der Wert des Richtungsknobs
	int _knob_direction;
// Current output mode (extension by RSP, see .C-file)
	int _knob_output_mode;
// Neu: Field-of-View
	double _xa_fov_unit,_ya_fov_unit;
	double _xb_fov_unit,_yb_fov_unit;
	double _xd_fov_unit,_yd_fov_unit;
	double _inv_xd_fov_unit,_inv_yd_fov_unit;
// Find out number of parameters per type and store here:
	int _num_par_adjustable_double;
	int _num_par_double;
	int _num_par_int;
	int _num_par_string;
	int _num_par_file;
	int _num_par_toggle;
// Wir verwenden hier absichtlich nicht std::vector, weil wir uns darauf verlassen
// muessen, dass die Werte nicht im Speicher verschoben werden. Es gibt einen Beispiel-Node,
// bei Nuke, der lustigerweise KnobParade heisst, da sehen wir, wie das geht.
	double* _values_adjustable_double;
	double* _values_double;
	int* _values_int;
	const char** _values_string;
	const char** _values_file;
	bool* _values_toggle;
// Default values for string- and file-knobs.
	char** _defaults_string;
	char** _defaults_file;
// The ld model instance. We derive from ldp_builtin instead of tde4_ld_plugin,
// since this class provides some extra functionality we need.
//	typedef ldpk::ldp_builtin<ldpk::vec2d,ldpk::mat2d> ldm_type;
	typedef tde4_ld_plugin ldm_type;
	ldm_type* _ldm;
// Map x-coordinate from unit cordinates to fov coordinates.
	double map_in_fov_x(double x_unit) const
		{ return  (x_unit - _xa_fov_unit) * _inv_xd_fov_unit; }
// Map y-coordinate from unit cordinates to fov coordinates.
	double map_in_fov_y(double y_unit) const
		{ return  (y_unit - _ya_fov_unit) * _inv_yd_fov_unit; }
// Map x-coordinate from fov cordinates to unit coordinates.
	double map_out_fov_x(double x_fov) const
		{ return x_fov * _xd_fov_unit + _xa_fov_unit; }
// Map y-coordinate from fov cordinates to unit coordinates.
	double map_out_fov_y(double y_fov) const
		{ return y_fov * _yd_fov_unit + _ya_fov_unit; }

// Model and parameter names in 3DE4 are human-readable, with characters
// like ",", "-" and space in it. This method eliminates maximum substrings containing
// other than [a-zA-Z0-9] and replaces them by a single underscore. The empty string is
// mapped to "_". A leading [0-9] is supplemented by a leading underscore.
// The result has the form of an identifier in C and Python.
	std::string nukify_name(const std::string& name);
// Anscheinend von keiner Basisklasse gefordert.
	enum direction_enum { distort = 0,undistort = 1 };
	DD::Image::Box bounds(direction_enum,int x,int y,int r,int t);
// LDM-Parameter auf default
	void set_default_values();
// Check for implementation errors
	void check_indices(int i_par_adjustable_double,int i_par_double,int i_par_int,int i_par_string,int i_par_file,int i_par_toggle,int i_debug) const;
public:
	nuke_ld_3de4_base(Node* node,ldm_type* ldm);
	virtual ~nuke_ld_3de4_base();

	void knobs(DD::Image::Knob_Callback f);
	void _validate(bool);
	void _request(int x,int y,int r,int t,DD::Image::ChannelMask channels,int count);
	void engine(int y,int x,int r,DD::Image::ChannelMask channels,DD::Image::Row& out);

	static const DD::Image::Iop::Description description;
	};
