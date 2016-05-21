// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/nuke_ld_3de4_base.h>

using namespace std;

// We need this for the "direction" knob.
static const char * const directions[] = {"distort","undistort",0};
// Output modes
static const char * const output_modes[] = {"image","STMap",0};

enum OutputModes {
	OUTPUT_IMAGE,
	OUTPUT_STMAP,
	};

nuke_ld_3de4_base::nuke_ld_3de4_base(Node* node,ldm_type* ldm):DD::Image::Iop(node)
	{
// We start with seven built-in parameters.
	_num_par_double = 7;
	_num_par_adjustable_double = 0;
	_num_par_int = 0;
	_num_par_string = 0;
	_num_par_file = 0;
	_num_par_toggle = 0;
// Lens distortion model
	_ldm = ldm;
// Number of model-specific parameters.
	_ldm->getNumParameters(_num_par);
// We determine the number of parameters for each 3DE4 widget type.
	for(int i = 0;i < _num_par;++i)
		{
		tde4_ldp_ptype type_par;
		char name_par[256];
		_ldm->getParameterName(i,name_par);
		_ldm->getParameterType(name_par,type_par);
		switch(type_par)
			{
			case TDE4_LDP_ADJUSTABLE_DOUBLE:
				++_num_par_adjustable_double;break;
			case TDE4_LDP_DOUBLE:
				++_num_par_double;break;
			case TDE4_LDP_INT:
				++_num_par_int;break;
			case TDE4_LDP_STRING:
				++_num_par_string;break;
			case TDE4_LDP_FILE:
				++_num_par_file;break;
			case TDE4_LDP_TOGGLE:
				++_num_par_toggle;break;
			default:
				cerr << "nuke_ld_3de4_base::nuke_ld_3de4_base: undefined type, implementation error." << endl;
			}
		}
// From these numbers we create value arrays for the knobs (one more than needed for debugging reasons).
	_values_adjustable_double = new double[_num_par_adjustable_double + 1];
	_values_double = new double[_num_par_double + 1];
	_values_int = new int[_num_par_int + 1];
	_values_string = new const char*[_num_par_string + 1];
	_values_file = new const char*[_num_par_file + 1];
	_values_toggle = new bool[_num_par_toggle + 1];
// Defaults. We initialize knobs with these pointers.
	_defaults_string = new char*[_num_par_string + 1];
	_defaults_file = new char*[_num_par_file + 1];
	for(int i = 0;i < _num_par_string + 1;++i)
		{ _defaults_string[i] = 0; }
	for(int i = 0;i < _num_par_file + 1;++i)
		{ _defaults_file[i] = 0; }
// Initialize value-arrays.
	set_default_values();
	}
nuke_ld_3de4_base::~nuke_ld_3de4_base()
	{
	if(_ldm) delete _ldm;
	if(_values_adjustable_double) delete[] _values_adjustable_double;
	if(_values_double) delete[] _values_double;
	if(_values_int) delete[] _values_int;
	if(_values_string) delete[] _values_string;
	if(_values_file) delete[] _values_file;
	if(_values_toggle) delete[] _values_toggle;

	if(_defaults_string)
		{
// Strings were created with strdup, so ::free.
		for(int i = 0;i < _num_par_string;++i)
			{ if(_defaults_string[i]) ::free(_defaults_string[i]); }
		delete[] _defaults_string;
		}
	if(_defaults_file)
		{
// Strings were created with strdup, so ::free.
		for(int i = 0;i < _num_par_file;++i)
			{ if(_defaults_file[i]) ::free(_defaults_file[i]); }
		delete[] _defaults_file;
		}
	}

void nuke_ld_3de4_base::check_indices(int i_par_adjustable_double,int i_par_double,int i_par_int,int i_par_string,int i_par_file,int i_par_toggle,int i_debug) const
	{
	if(i_par_adjustable_double != _num_par_adjustable_double)
		{ cerr << "inconsistent indexing, implementation error (adjustable_double)! [" << i_debug << "]" << endl; }
	if(i_par_double != _num_par_double)
		{ cerr << "inconsistent indexing, implementation error (double)! [" << i_debug << "]" << endl; }
	if(i_par_int != _num_par_int)
		{ cerr << "inconsistent indexing, implementation error (int)! [" << i_debug << "]" << endl; }
	if(i_par_string != _num_par_string)
		{ cerr << "inconsistent indexing, implementation error (string)! [" << i_debug << "]" << endl; }
	if(i_par_file != _num_par_file)
		{ cerr << "inconsistent indexing, implementation error (file)! [" << i_debug << "]" << endl; }
	if(i_par_toggle != _num_par_toggle)
		{ cerr << "inconsistent indexing, implementation error (toggle)! [" << i_debug << "]" << endl; }
	}

string nuke_ld_3de4_base::nukify_name(const string& name)
	{
	string s;
	bool space = true;
// Empty string maps to underscore (we want to get a valid identifier).
	if(name == "")
		{ return "_"; }
// Identifiers don't start with a numeric char, so underscore.
	if(isdigit(name[0]))
		{ s += '_'; }
	for(int i = 0;i < name.size();++i)
		{
		char c = name[i];
		if(isalnum(c))
			{
// Transfer alphanums unmodified.
			space = false;
			s += c;
			}
		else
			{
// Everything else is baked into one underscore.
			if(!space)
				{
				space = true;
				s += '_';
				}
			}
		}
	return s;
	}

void nuke_ld_3de4_base::set_default_values()
	{
	int i_par_adjustable_double = 0;
	int i_par_double = 0;
	int i_par_int = 0;
	int i_par_string = 0;
	int i_par_file = 0;
	int i_par_toggle = 0;
// Direction, default is "undistort".
	_knob_direction = 1;
// Output mode, default must be 'image' to preserve original behaviour
	_knob_output_mode = 0;
// 3DE4-Field-of-View
	_xa_fov_unit = 0.0;
	_ya_fov_unit = 0.0;
	_xb_fov_unit = 1.0;
	_yb_fov_unit = 1.0;
// First the seven built-in parameters. Order is important, we won't change.
	_values_double[i_par_double++] = 1.0;
	_values_double[i_par_double++] = 100.0;
	_values_double[i_par_double++] = 0.8;
	_values_double[i_par_double++] = 0.6;
	_values_double[i_par_double++] = 0.0;
	_values_double[i_par_double++] = 0.0;
	_values_double[i_par_double++] = 1.0;
// Now the model-specific parameters.
	for(int i = 0;i < _num_par;++i)
		{
		tde4_ldp_ptype type_par;
		char name_par[256];
		_ldm->getParameterName(i,name_par);
		_ldm->getParameterType(name_par,type_par);
		switch(type_par)
			{
			case TDE4_LDP_ADJUSTABLE_DOUBLE:
				{
				double d;
				_ldm->getParameterDefaultValue(name_par,d);
				_values_adjustable_double[i_par_adjustable_double++] = d;
				break;
				}
			case TDE4_LDP_DOUBLE:
				{
				double d;
				_ldm->getParameterDefaultValue(name_par,d);
				_values_double[i_par_double++] = d;
				break;
				}
			case TDE4_LDP_INT:
				{
				int d;
				_ldm->getParameterDefaultValue(name_par,d);
				_values_int[i_par_int++] = d;
				break;
				}
			case TDE4_LDP_STRING:
				{
				char v[1024];
				_ldm->getParameterDefaultValue(name_par,v);
// See destructor, free with ::free.
				_defaults_string[i_par_string] = strdup(v);
				_values_string[i_par_string] = _defaults_string[i_par_string];
				++i_par_string;
				break;
				}
			case TDE4_LDP_FILE:
				{
				char v[1024];
				_ldm->getParameterDefaultValue(name_par,v);
// See destructor, free with ::free.
				_defaults_file[i_par_file] = strdup(v);
				_values_file[i_par_file] = _defaults_file[i_par_file];
				++i_par_file;
				break;
				}
			case TDE4_LDP_TOGGLE:
				{
				bool d;
				_ldm->getParameterDefaultValue(name_par,d);
				_values_toggle[i_par_toggle++] = d;
				break;
				}
			default:
				{
				cerr << "nuke_ld_3de4_base::set_default_values: undefined type, implementation error." << endl;
				break;
				}
			}
		}
	check_indices(i_par_adjustable_double,i_par_double,i_par_int,i_par_string,i_par_file,i_par_toggle,1);
	}

DD::Image::Box nuke_ld_3de4_base::bounds(direction_enum dir,int x,int y,int r,int t)
	{
// From pixel coordinates to unit coordinates
	double xa_in_unit = double(x) / format().width();
	double ya_in_unit = double(y) / format().height();
	double xb_in_unit = double(r) / format().width();
	double yb_in_unit = double(t) / format().height();
// From unit coordinates to fov coordinates
	double xa_in_fov = (xa_in_unit - _xa_fov_unit) / (_xb_fov_unit - _xa_fov_unit);
	double xb_in_fov = (xb_in_unit - _xa_fov_unit) / (_xb_fov_unit - _xa_fov_unit);
	double ya_in_fov = (ya_in_unit - _ya_fov_unit) / (_yb_fov_unit - _ya_fov_unit);
	double yb_in_fov = (yb_in_unit - _ya_fov_unit) / (_yb_fov_unit - _ya_fov_unit);
// Get bounding box
	double xa_out_fov,ya_out_fov,xb_out_fov,yb_out_fov;
	if(dir == distort)
		{ _ldm->getBoundingBoxDistort(xa_in_fov,ya_in_fov,xb_in_fov,yb_in_fov,xa_out_fov,ya_out_fov,xb_out_fov,yb_out_fov,8,8); }
	else
		{ _ldm->getBoundingBoxUndistort(xa_in_fov,ya_in_fov,xb_in_fov,yb_in_fov,xa_out_fov,ya_out_fov,xb_out_fov,yb_out_fov,8,8); }
// From fov coordinates to unit coordinates
	double xa_out_unit = xa_out_fov * (_xb_fov_unit - _xa_fov_unit) + _xa_fov_unit;
	double xb_out_unit = xb_out_fov * (_xb_fov_unit - _xa_fov_unit) + _xa_fov_unit;
	double ya_out_unit = ya_out_fov * (_yb_fov_unit - _ya_fov_unit) + _ya_fov_unit;
	double yb_out_unit = yb_out_fov * (_yb_fov_unit - _ya_fov_unit) + _ya_fov_unit;
// From unit coordinates to pixel
	double xa_px = format().width() * xa_out_unit;
	double ya_px = format().height() * ya_out_unit;
	double xb_px = format().width() * xb_out_unit;
	double yb_px = format().height() * yb_out_unit;
// Slight extra margin, just in case our getBoundingBox-Methods miss something.
	return DD::Image::Box(int(floor(xa_px)) - 2,int(floor(ya_px)) - 2,int(ceil(xb_px)) + 2,int(ceil(yb_px)) + 2);
	}

void nuke_ld_3de4_base::knobs(DD::Image::Knob_Callback callback)
	{
// Knob fo direction: undistort <-> distort
	DD::Image::Enumeration_knob(callback,&_knob_direction,directions,"direction");
// Knob for output mode
	DD::Image::Enumeration_knob(callback,&_knob_output_mode,output_modes,"mode","output mode");
// Filterknob.
	_filter.knobs(callback);
// Indices for our value arrays.
	int i_par_adjustable_double = 0;
	int i_par_double = 0;
	int i_par_int = 0;
	int i_par_string = 0;
	int i_par_file = 0;
	int i_par_toggle = 0;

// Field-of-View
	Double_knob(callback,&_xa_fov_unit,DD::Image::IRange(0.0,1.0),"field_of_view_xa_unit","fov left [unit coord]");
	Double_knob(callback,&_ya_fov_unit,DD::Image::IRange(0.0,1.0),"field_of_view_ya_unit","fov bottom [unit coord]");
	Double_knob(callback,&_xb_fov_unit,DD::Image::IRange(0.0,1.0),"field_of_view_xb_unit","fov right [unit coord]");
	Double_knob(callback,&_yb_fov_unit,DD::Image::IRange(0.0,1.0),"field_of_view_yb_unit","fov top [unit coord]");
// First the seven built-in parameters, in this order.
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(0.5,50.0),"tde4_focal_length_cm","tde4 focal length [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(10.0,1000.0),"tde4_custom_focus_distance_cm","tde4 focus distance [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(.1,10.0),"tde4_filmback_width_cm","tde4 filmback width [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(.1,10.0),"tde4_filmback_height_cm","tde4 filmback height [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(-5.0,5.0),"tde4_lens_center_offset_x_cm","tde4 lens center offset x [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(-5.0,5.0),"tde4_lens_center_offset_y_cm","tde4 lens center offset y [cm]");
	Double_knob(callback,&_values_double[i_par_double++],DD::Image::IRange(0.25,4.0),"tde4_pixel_aspect","tde4 pixel aspect");
// Now the model-specific parameters.
	for(int i = 0;i < _num_par;++i)
		{
		tde4_ldp_ptype type_par;
		char name_par[256];
		_ldm->getParameterName(i,name_par);
		_ldm->getParameterType(name_par,type_par);
		switch(type_par)
			{
			case TDE4_LDP_ADJUSTABLE_DOUBLE:
				{
				double a,b;
				_ldm->getParameterRange(name_par,a,b);
				Double_knob(callback,&_values_adjustable_double[i_par_adjustable_double],DD::Image::IRange(a,b),nukify_name(name_par).c_str(),name_par);
				++i_par_adjustable_double;
				break;
				}
			case TDE4_LDP_DOUBLE:
				{
				Double_knob(callback,&_values_double[i_par_double],DD::Image::IRange(-1,+1),nukify_name(name_par).c_str(),name_par);
				++i_par_double;
				break;
				}
			case TDE4_LDP_INT:
				{
				Int_knob(callback,&_values_int[i_par_int],nukify_name(name_par).c_str(),name_par);
				++i_par_int;
				break;
				}
			case TDE4_LDP_STRING:
				{
				String_knob(callback,&_values_string[i_par_string],nukify_name(name_par).c_str(),name_par);
				SetFlags(callback,DD::Image::Knob::STARTLINE);
				 ++i_par_string;
				break;
				}
			case TDE4_LDP_FILE:
				{
				File_knob(callback,&_values_file[i_par_file],nukify_name(name_par).c_str(),name_par);
				SetFlags(callback,DD::Image::Knob::STARTLINE);
				++i_par_file;
				break;
				}
			case TDE4_LDP_TOGGLE:
				{
				Bool_knob(callback,&_values_toggle[i_par_toggle],nukify_name(name_par).c_str(),name_par);
				SetFlags(callback,DD::Image::Knob::STARTLINE);
				++i_par_toggle;
				break;
				}
			default:
				{
				cerr << "nuke_ld_3de4_base::knobs: undefined type, implementation error." << endl;
				break;
				}
			}
		}
	check_indices(i_par_adjustable_double,i_par_double,i_par_int,i_par_string,i_par_file,i_par_toggle,2);
	}

void nuke_ld_3de4_base::_validate(bool)
	{
	if(!input(0))
		{ return; }
// Calculate quantities derived from Field-of-View.
	_xd_fov_unit = _xb_fov_unit - _xa_fov_unit;
	_yd_fov_unit = _yb_fov_unit - _ya_fov_unit;
	_inv_xd_fov_unit = 1.0 / _xd_fov_unit;
	_inv_yd_fov_unit = 1.0 / _yd_fov_unit;
// Indices for iterating over value arrays.
	int i_par_adjustable_double = 0;
	int i_par_double = 0;
	int i_par_int = 0;
	int i_par_string = 0;
	int i_par_file = 0;
	int i_par_toggle = 0;
// Transfer parameters into our lens distortion model.
// First the seven built-in parameters. Never change the order.
	_ldm->setParameterValue("tde4_focal_length_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_custom_focus_distance_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_filmback_width_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_filmback_height_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_lens_center_offset_x_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_lens_center_offset_y_cm",_values_double[i_par_double++]);
	_ldm->setParameterValue("tde4_pixel_aspect",_values_double[i_par_double++]);
// Model-specific parameters
	for(int i = 0;i < _num_par;++i)
		{
		tde4_ldp_ptype type_par;
		char name_par[256];
		_ldm->getParameterName(i,name_par);
		_ldm->getParameterType(name_par,type_par);
		switch(type_par)
			{
			case TDE4_LDP_ADJUSTABLE_DOUBLE:
				{
				_ldm->setParameterValue(name_par,_values_adjustable_double[i_par_adjustable_double]);
				++i_par_adjustable_double;
				break;
				}
			case TDE4_LDP_DOUBLE:
				{
				_ldm->setParameterValue(name_par,_values_double[i_par_double]);
				++i_par_double;
				break;
				}
			case TDE4_LDP_INT:
				{
				_ldm->setParameterValue(name_par,_values_int[i_par_int]);
				++i_par_int;
				break;
				}
			case TDE4_LDP_STRING:
				{
				_ldm->setParameterValue(name_par,_values_string[i_par_string]);
				++i_par_string;
				break;
				}
			case TDE4_LDP_FILE:
				{
				_ldm->setParameterValue(name_par,_values_file[i_par_file]);
				++i_par_file;
				break;
				}
			case TDE4_LDP_TOGGLE:
				{
				_ldm->setParameterValue(name_par,_values_toggle[i_par_toggle]);
				++i_par_toggle;
				break;
				}
			default:
				{
				cerr << "nuke_ld_3de4_base::_validate: undefined type, implementation error." << endl;
				break;
				}
			}
		}
	check_indices(i_par_adjustable_double,i_par_double,i_par_int,i_par_string,i_par_file,i_par_toggle,3);
// Important, required bei 3DE4 plugin baseclass.
	_ldm->initializeParameters();
// Filter
	_filter.initialize();
// Not clear, I should read the Nuke documentation...
// I guess it copies the image area data from the input.
	copy_info();
// We compute the bounding box. The box cannot be smaller than the image area,
// but maybe larger, therefore we merge our info with the bounding box from the lens model.
	info_.merge(bounds(_knob_direction == distort ? distort : undistort,format().x(),format().y(),format().r(),format().t()));
	}

void nuke_ld_3de4_base::_request(int x,int y,int r,int t,DD::Image::ChannelMask channels,int count)
	{
// Since for image processing we *fetch* at pixel positions,
// the inverse mapping is used (as often mentioned).
	DD::Image::Box box = bounds(_knob_direction == distort ? undistort : distort,x,y,r,t);
// The original Weta-Node forms an intersection with input0's box,
// makes sense, we do the same here. I guess, we shouldn't demand,
// what input0 does not supply, that's why.
	box.intersect(input0().info());
	input0().request(box.x(),box.y(),box.r(),box.t(),channels,count);
	}

void nuke_ld_3de4_base::engine(int y,int x,int r,DD::Image::ChannelMask channels,DD::Image::Row& outrow)
	{
	if(!input(0))
		{ return; }
	int w = format().w();
	int h = format().h();
	if((w <= 0) | (h <= 0))
		{ return; }
	double inv_w = 1.0 / w;
	double inv_h = 1.0 / h;
// We construct (x_s,y_s) in a way, so that the image area is mapped to the unit interval [0,1]^2,
// which is required by our 3DE4 lens distortion plugin class. Nuke's coordinates are pixel based,
// (0,0) is the left lower corner of the left lower pixel, while (1,1) is the right upper corner
// of that pixel. The center of any pixel (ix,iy) is (ix+0.5,iy+0.5), so we add 0.5 here.
	double y_s = (0.5 + y) * inv_h;
// Determine bounding box and write down results.
	vector<ldpk::vec2d> pos;
// Reserve, so that push_back is performant.
	pos.reserve(r - x);
// Box for "lock the tile".
	DD::Image::Box box;
	for(int i = x;i < r;++i)
		{
// We don't forget shifting by (half,half)!
		double x_s = (0.5 + i) * inv_w;
		double x_d,y_d;
// Image processing, reversed mapping. Weave in 3DE4's field of view.
		if(_knob_direction == undistort)
			{ _ldm->distort(map_in_fov_x(x_s),map_in_fov_y(y_s),x_d,y_d); }
		else
			{ _ldm->undistort(map_in_fov_x(x_s),map_in_fov_y(y_s),x_d,y_d); }
// The result already contains the (half,half) shift. Reformulate in Nuke's coordinates. Weave "out" 3DE4's field of view.
		double px = map_out_fov_x(x_d) * w;
		double py = map_out_fov_y(y_d) * h;
// Build the box for "lock the tile..."
		if(i == x)
			{ box = DD::Image::Box(int(floor(px)),int(floor(py)),int(ceil(px)),int(ceil(py))); }
		else
			{ box.merge(int(floor(px)),int(floor(py)),int(ceil(px)),int(ceil(py))); }
// We store the results.
		pos.push_back(ldpk::vec2d(px,py));
		}
// Add margin for reconstruction filter. Cubic will need two pixels more, others maybe three.
	box.pad(3);

// Transfer the stored result. We set pixels x to r in outrow.
// Begin extension by David Cattermole and Ben Dickson, RSP. Thank you!
// Minor changes added by SDV for version 1.9.1.
	if(_knob_output_mode == OUTPUT_STMAP)
		{
// Output source pixel coordinates in format compatible with STMap
		double inv_w0 = 1.0 / input0().format().width();
		double inv_h0 = 1.0 / input0().format().height();
		for(int i = 0;i < pos.size();++i)
			{
			foreach(z,channels)
				{
				if(z == DD::Image::Chan_Red)
					{ outrow.writable(z)[i + x] = float(pos[i][0] * inv_w0); }
				else if(z == DD::Image::Chan_Green)
					{ outrow.writable(z)[i + x] = float(pos[i][1] * inv_h0); }
				else
					{ outrow.writable(z)[i + x] = 0.0; }
				}
			}
		}
// End extension.
	else if(_knob_output_mode == OUTPUT_IMAGE)
		{
// Added in 1.9.1. This should accelerate the output in the viewer,
// but I wouldn't expect any effect for rendering to disk.
		DD::Image::InterestRatchet interest_ratchet;
		DD::Image::Pixel out(channels);
		out.setInterestRatchet(&interest_ratchet);
// Output warped image
// "lock the tile into the cache"
		DD::Image::Tile t(input0(),box.x(),box.y(),box.r(),box.t(),channels);
// Compute resulting row.
		for(int i = 0;i < pos.size();++i)
			{
// Transfer the stored result. We set pixels x to r in outrow.
			input0().sample(float(pos[i][0]),float(pos[i][1]),1.0,1.0,&_filter,out);
			foreach(z,channels)
				{ outrow.writable(z)[i + x] = out[z]; }
			}
		}
	else
		{
		std::cerr << "ERROR: nuke_ld_3de4_base: Unhandled output mode " << _knob_output_mode << "\n";
		for(int i = 0;i < pos.size();++i)
			{
			foreach(z,channels)
				{ outrow.writable(z)[i + x] = -1; }
			}
		}
	}


