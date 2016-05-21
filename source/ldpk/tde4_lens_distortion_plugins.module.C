// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.1


#include <Python.h>
#include "structmember.h"
#include <iostream>
#include <ldpk/tde4_ldp_anamorphic_deg_4_rotate_squeeze_xy.h>
#include <ldpk/tde4_ldp_anamorphic_deg_6.h>
#include <ldpk/tde4_ldp_radial_deg_8.h>
#include <ldpk/tde4_ldp_radial_decentered_deg_4_cylindric.h>
#include <ldpk/tde4_ldp_classic_3de_mixed.h>
#include <ldpk/tde4_ldp_all_par_types.h>
#include <ldpk/tde4_ldp_blender.h>

// Python produces these warnings.
#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

// Praefix tde4_ldp_py_wrapper

struct tde4_ldp_py_wrapper
	{
	PyObject_HEAD
	ldpk::ldp_builtin<ldpk::vec2d,ldpk::mat2d> *_ldm;
	tde4_ldp_py_wrapper():_ldm(0)
		{ }
	bool is_initialized() const
		{ return _ldm != 0; }
	PyObject* not_initialized() const
		{
		PyErr_SetString(PyExc_RuntimeError,"baseclass not initialized, did you call __init__(self)?");
		return NULL;
		}
	};

/**** Lens Distortion Models *****/
static int anamorphic_deg_4_rotate_squeeze_xy(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_anamorphic_deg_4_rotate_squeeze_xy<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int anamorphic_deg_6(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_anamorphic_deg_6<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int radial_deg_8(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_radial_deg_8<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int radial_decentered_deg_4_cylindric(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_radial_decentered_deg_4_cylindric<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int classic_3de_mixed(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_classic_3de_mixed<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int all_par_types(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_all_par_types<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}
static int blender(tde4_ldp_py_wrapper *self, PyObject *args, PyObject *kwds)
	{
	self->_ldm = new tde4_ldp_blender<ldpk::vec2d,ldpk::mat2d>();
	return 0;
	}

/*********************************/

static void ldm_dealloc(tde4_ldp_py_wrapper* self)
	{
	if(self->_ldm) delete self->_ldm;
	self->ob_type->tp_free((PyObject*)self);
	}

static PyObject* ldm_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
	{
	tde4_ldp_py_wrapper *self;
	self = (tde4_ldp_py_wrapper*)type->tp_alloc(type, 0);
	if (self != NULL)
		{
		self->_ldm = 0;
		}
	return (PyObject *)self;
	}

static PyObject* ldm_getModelName(tde4_ldp_py_wrapper* self)
	{
	char modelname[256];
	self->_ldm->getModelName(modelname);
	PyObject *name = Py_BuildValue("s",modelname);
	return name;
	}
static PyObject* ldm_getNumParameters(tde4_ldp_py_wrapper* self)
	{
	int num_parameters;
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->getNumParameters(num_parameters);
	PyObject *num = Py_BuildValue("i",num_parameters);
	return num;
	}
static PyObject* ldm_getParameterName(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	int i_par;
	if(!PyArg_ParseTuple(args,"i",&i_par))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	char name_par[256];
	self->_ldm->getParameterName(i_par,name_par);
	PyObject *name = Py_BuildValue("s",name_par);
	return name;
	}
static PyObject* ldm_getParameterType(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	if(!PyArg_ParseTuple(args,"s",&name_par))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	self->_ldm->getParameterType(name_par,type_par);
	PyObject *t = Py_BuildValue("i",type_par);
	return t;
	}
static PyObject* ldm_getParameterDefaultValue(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	if(!PyArg_ParseTuple(args,"s",&name_par))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	self->_ldm->getParameterType(name_par,type_par);
	switch(type_par)
		{
		case TDE4_LDP_STRING:
		case TDE4_LDP_FILE:
			{
			char value[1000];
			self->_ldm->getParameterDefaultValue(name_par,value);
			PyObject *t = Py_BuildValue("s",value);
			return t;
			}
		case TDE4_LDP_DOUBLE:
		case TDE4_LDP_ADJUSTABLE_DOUBLE:
			{
			double value;
			self->_ldm->getParameterDefaultValue(name_par,value);
			PyObject *t = Py_BuildValue("d",value);
			return t;
			}
		case TDE4_LDP_INT:
			{
			int value;
			self->_ldm->getParameterDefaultValue(name_par,value);
			PyObject *t = Py_BuildValue("i",value);
			return t;
			}
		case TDE4_LDP_TOGGLE:
			{
			bool value;
			self->_ldm->getParameterDefaultValue(name_par,value);
			PyObject *t = Py_BuildValue("O",value ? Py_True : Py_False);
			return t;
			}
		}
	cerr << "ldm_getParameterDefaultValue: unreachable code" << endl;
	return NULL;
	}
static PyObject* ldm_getParameterRange(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	if(!PyArg_ParseTuple(args,"s",&name_par))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	self->_ldm->getParameterType(name_par,type_par);
	if(type_par == TDE4_LDP_ADJUSTABLE_DOUBLE)
		{
		double a,b;
		self->_ldm->getParameterRange(name_par,a,b);
		PyObject *t = Py_BuildValue("(ff)",a,b);
		return t;
		}
	PyErr_SetString(PyExc_RuntimeError,"getParameterRange is only defined for parameter type ADJUSTABLE_DOUBLE.");
	return NULL;
	}
static PyObject* ldm_setParameterValueDouble(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	double val;
	if(!PyArg_ParseTuple(args,"sd",&name_par,&val))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	if(!self->_ldm->getParameterType(name_par,type_par))
		{
		PyErr_SetString(PyExc_RuntimeError,"setParameterValueDouble: unknown parameter.");
		return NULL;
		}
	if((type_par == TDE4_LDP_DOUBLE) || (type_par == TDE4_LDP_ADJUSTABLE_DOUBLE))
		{
		self->_ldm->setParameterValue(name_par,val);
		Py_INCREF(Py_None);
		return Py_None;
		}
	PyErr_SetString(PyExc_RuntimeError,"setParameterValueDouble: parameter does not have type DOUBLE or ADJUSTABLE_DOUBLE.");
	return NULL;
	}
static PyObject* ldm_setParameterValueInt(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	int val;
	if(!PyArg_ParseTuple(args,"si",&name_par,&val))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	if(!self->_ldm->getParameterType(name_par,type_par))
		{
		PyErr_SetString(PyExc_RuntimeError,"setParameterValueDouble: unknown parameter.");
		return NULL;
		}
	if(type_par == TDE4_LDP_INT)
		{
		self->_ldm->setParameterValue(name_par,val);
		Py_INCREF(Py_None);
		return Py_None;
		}
	PyErr_SetString(PyExc_RuntimeError,"setParameterValueInt: parameter does not have type INT.");
	return NULL;
	}
static PyObject* ldm_setParameterValueString(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	const char* val;
	if(!PyArg_ParseTuple(args,"ss",&name_par,&val))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	if(!self->_ldm->getParameterType(name_par,type_par))
		{
		PyErr_SetString(PyExc_RuntimeError,"setParameterValueDouble: unknown parameter.");
		return NULL;
		}
	if((type_par == TDE4_LDP_STRING) || (type_par == TDE4_LDP_FILE))
		{
		self->_ldm->setParameterValue(name_par,val);
		Py_INCREF(Py_None);
		return Py_None;
		}
	PyErr_SetString(PyExc_RuntimeError,"setParameterValueInt: parameter does not have type STRING or FILE.");
	return NULL;
	}
static PyObject* ldm_setParameterValueBool(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	const char* name_par;
	PyObject* val;
	if(!PyArg_ParseTuple(args,"sO",&name_par,&val))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	tde4_ldp_ptype type_par;
	if(!self->_ldm->getParameterType(name_par,type_par))
		{
		PyErr_SetString(PyExc_RuntimeError,"setParameterValueDouble: unknown parameter.");
		return NULL;
		}
	if(type_par == TDE4_LDP_TOGGLE)
		{
		self->_ldm->setParameterValue(name_par,val == Py_True);
		Py_INCREF(Py_None);
		return Py_None;
		}
	PyErr_SetString(PyExc_RuntimeError,"setParameterValueBool: parameter does not have type TOGGLE.");
	return NULL;
	}
static PyObject* ldm_initializeParameters(tde4_ldp_py_wrapper* self)
	{
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->initializeParameters();
	Py_INCREF(Py_None);
	return Py_None;
	}
static PyObject* ldm_undistort(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	double x0,y0,x1,y1;
	if(!PyArg_ParseTuple(args,"(dd)",&x0,&y0))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->undistort(x0,y0,x1,y1);
	PyObject *t = Py_BuildValue("dd",x1,y1);
	return t;
	}
static PyObject* ldm_distort(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	double x0,y0,x1,y1;
	if(!PyArg_ParseTuple(args,"(dd)",&x0,&y0))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->distort(x0,y0,x1,y1);
	PyObject *t = Py_BuildValue("dd",x1,y1);
	return t;
	}
static PyObject* ldm_getJacobianMatrix(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	double x0,y0,m00,m01,m10,m11;
	if(!PyArg_ParseTuple(args,"(dd)",&x0,&y0))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->getJacobianMatrix(x0,y0,m00,m01,m10,m11);
	PyObject *t = Py_BuildValue("dddd",m00,m01,m10,m11);
	return t;
	}
static PyObject* ldm_getTwistVector(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	double x0,y0,t0,t1;
	if(!PyArg_ParseTuple(args,"(dd)",&x0,&y0))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->getTwistVector(x0,y0,t0,t1);
	PyObject *t = Py_BuildValue("dd",t0,t1);
	return t;
	}
static PyObject* ldm_getBoundingBoxDistort(tde4_ldp_py_wrapper* self,PyObject* args,PyObject *keywds)
	{
	static char *kwlist[] = {"xa","ya","xb","yb","nx","ny",NULL};
	double xa_in,ya_in,xb_in,yb_in,xa_out,ya_out,xb_out,yb_out;
	int nx = 32,ny = 32;
	if(!PyArg_ParseTupleAndKeywords(args,keywds,"dddd|ii",kwlist,&xa_in,&ya_in,&xb_in,&yb_in,&nx,&ny))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->getBoundingBoxDistort(xa_in,ya_in,xb_in,yb_in,xa_out,ya_out,xb_out,yb_out,nx,ny);
	PyObject *t = Py_BuildValue("dddd",kwlist,xa_out,ya_out,xb_out,yb_out);
	return t;
	}
static PyObject* ldm_getBoundingBoxUndistort(tde4_ldp_py_wrapper* self,PyObject* args,PyObject *keywds)
	{
	static char *kwlist[] = {"xa","ya","xb","yb","nx","ny",NULL};
	double xa_in,ya_in,xb_in,yb_in,xa_out,ya_out,xb_out,yb_out;
	int nx = 32,ny = 32;
	if(!PyArg_ParseTupleAndKeywords(args,keywds,"dddd|ii",kwlist,&xa_in,&ya_in,&xb_in,&yb_in,&nx,&ny))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->getBoundingBoxUndistort(xa_in,ya_in,xb_in,yb_in,xa_out,ya_out,xb_out,yb_out,nx,ny);
	PyObject *t = Py_BuildValue("dddd",xa_out,ya_out,xb_out,yb_out);
	return t;
	}
static PyObject* ldm_setCamera(tde4_ldp_py_wrapper* self,PyObject* args)
	{
	double fl_cm,w_fb_cm,h_fb_cm,x_lco_cm,y_lco_cm,r_pa,fd_cm;
	if(!PyArg_ParseTuple(args,"ddddddd",&fl_cm,&w_fb_cm,&h_fb_cm,&x_lco_cm,&y_lco_cm,&r_pa,&fd_cm))
		{ return NULL; }
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	self->_ldm->setParameterValue("tde4_focal_length_cm",fl_cm);
	self->_ldm->setParameterValue("tde4_filmback_width_cm",w_fb_cm);
	self->_ldm->setParameterValue("tde4_filmback_height_cm",h_fb_cm);
	self->_ldm->setParameterValue("tde4_lens_center_offset_x_cm",x_lco_cm);
	self->_ldm->setParameterValue("tde4_lens_center_offset_y_cm",y_lco_cm);
	self->_ldm->setParameterValue("tde4_pixel_aspect",r_pa);
	self->_ldm->setParameterValue("tde4_custom_focus_distance_cm",fd_cm);
	self->_ldm->initializeParameters();
	Py_INCREF(Py_None);
	return Py_None;
	}
static PyObject* ldm_getCamera(tde4_ldp_py_wrapper* self)
	{
	if(!self->is_initialized())
		{ return self->not_initialized(); }
	double fl_cm = self->_ldm->fl_cm();
	double w_fb_cm = self->_ldm->w_fb_cm();
	double h_fb_cm = self->_ldm->h_fb_cm();
	double x_lco_cm = self->_ldm->x_lco_cm();
	double y_lco_cm = self->_ldm->y_lco_cm();
	double r_pa = self->_ldm->pa();
	double fd_cm = self->_ldm->fd_cm();
	PyObject *t = Py_BuildValue("ddddddd",fl_cm,w_fb_cm,h_fb_cm,x_lco_cm,y_lco_cm,r_pa,fd_cm);
	return t;
	}


static PyMemberDef ldm_members[] = {
	{NULL}
	};

static PyMethodDef ldm_methods[] = {
	{"getModelName", (PyCFunction)ldm_getModelName, METH_NOARGS,
		"Signature: getModelName() -> string.\n"\
		"Name of distortion model as in 3DE4's GUI."
		},
	{"getNumParameters", (PyCFunction)ldm_getNumParameters, METH_NOARGS,
		"Signature: getNumParameters() -> int.\n"\
		"Number of model-specific parameters. "\
		"There are seven built-in paramters (like tde4_filmback_width_cm...tde4_focus_distance_cm) "\
		"and a number of model-specific parameters, which describe the lens distortion model."
		},
	{"getParameterName", (PyCFunction)ldm_getParameterName, METH_VARARGS,
		"Signature: getParameterName(i) -> string.\n"\
		"Name of i-th model-specific parameter"
		},
	{"getParameterType", (PyCFunction)ldm_getParameterType, METH_VARARGS,
		"Signature: getParameterType(name) -> int.\n"\
		"Type of parameter"
		},
	{"getParameterDefaultValue", (PyCFunction)ldm_getParameterDefaultValue, METH_VARARGS,
		"Signature: getParameterDefaultValue(name) -> one of double,int,string,bool.\n"\
		"Default value of parameter"
		},
	{"getParameterRange", (PyCFunction)ldm_getParameterRange, METH_VARARGS,
		"Signature: getParameterRange(name) -> (double,double).\n"\
		"Typical/Strict range of parameter"
		},
	{"setParameterValueDouble", (PyCFunction)ldm_setParameterValueDouble, METH_VARARGS,
		"Signature: setParameterValueDouble(name,value) -> None.\n"\
		"Set value of parameter. The parameter is addressed by its name. This can be one of the seven built-in parameters "\
		"or one of the model-specific ones. Please note, that all length-unit parameters are given in centimeter."
		},
	{"setParameterValueInt", (PyCFunction)ldm_setParameterValueInt, METH_VARARGS,
		"Signature: setParameterValueInt(name,value) -> None.\n"\
		"Set value of parameter."
		},
	{"setParameterValueString", (PyCFunction)ldm_setParameterValueString, METH_VARARGS,
		"Signature: setParameterValueString(name,value) -> None.\n"\
		"Set value of parameter."
		},
	{"setParameterValueBool", (PyCFunction)ldm_setParameterValueBool, METH_VARARGS,
		"Signature: setParameterValueBool(name,value) -> None.\n"\
		"Set value of parameter."
		},
	{"initializeParameters", (PyCFunction)ldm_initializeParameters, METH_NOARGS,
		"Signature: initializeParameters() -> None.\n"\
		"Initialize what -er- needs to be initialized (after modifying parameters, important)"
		},
	{"undistort", (PyCFunction)ldm_undistort, METH_VARARGS,
		"Signature: undistort((x,y)) -> (double,double).\n"\
		"remove distortion for point (x,y). "\
		"The point (x,y) is specified in unit coordinates [0,1]x[0,1], which correspond to the filmback. "\
		"Please consult the ldpk-documentation for details."
		},
	{"distort", (PyCFunction)ldm_distort, METH_VARARGS,
		"Signature: distort((x,y)) -> (double,double).\n"\
		"apply distortion for point (x,y). "\
		"Inverse function of undistort(). Usually, this function is iterative, while undistort() is not (i.e. it's slower)."
		},
	{"getJacobianMatrix", (PyCFunction)ldm_getJacobianMatrix, METH_VARARGS,
		"Signature: getJacobianMatrix((x,y)) -> (double,double,double,double).\n"\
		"Jacobian for point (x,y). Result is (m00,m01,m10,m11) <- this order. "\
		"This is the Jacobian for the undistort-method, in unit coordinates [0,1]x[0,1]."
		},
	{"getTwistVector", (PyCFunction)ldm_getTwistVector, METH_VARARGS,
		"Signature: getTwistVector((x,y)) -> (double,double).\n"\
		"Mixed Derivatives for point (x,y). Result is (t0,t1). "\
		"These are the mixed derivatives for the undistort-method, in unit coordinates [0,1]x[0,1]."
		},
	{"getBoundingBoxDistort", (PyCFunction)ldm_getBoundingBoxDistort, METH_VARARGS | METH_KEYWORDS,
		"Signature: getBoundingBoxDistort(double xa,double ya,double xb,double yb,int nx=32,int ny=32) -> (double xa_out,double ya_out,double xb_out,double yb_out).\n"\
		"Bounding box resulting from distorting the rectangle [xa,ya]x[xb,yb]. "\
		"The return value is the bounding box (xa_out,ya_out),(xb_out,yb_out). "\
		"By default, the edges of the rectangle are scanned at nx+1 points horizontally and ny+1 points vertically."
		},
	{"getBoundingBoxUndistort", (PyCFunction)ldm_getBoundingBoxUndistort, METH_VARARGS | METH_KEYWORDS,
		"Signature: getBoundingBoxUndistort(double xa,double ya,double xb,double yb,int nx=32,int ny=32) -> (double xa_out,double ya_out,double xb_out,double yb_out).\n"\
		"Bounding box resulting from undistorting the rectangle [xa,ya]x[xb,yb]. "\
		"The return value is the bounding box (xa_out,ya_out),(xb_out,yb_out)."
		"By default, the edges of the rectangle are scanned at nx+1 points horizontally and ny+1 points vertically."
		},
	{"setCamera", (PyCFunction)ldm_setCamera, METH_VARARGS,
		"Signature: setCamera(double,double,double,double,double,double,double) -> None.\n"
		"Convenience function for setting all seven built-in camera parameters at once. "
		"The parameters are (in this order): focal length [cm], filmback width [cm], filmback height [cm], "
		"lens center offset x [cm], lens center offset y [cm], pixel aspect, focus distance [cm]. "
		"If focus distance is not relevant, it should be set to some non-zero value, say 100 (cm). "
		"Currently, no error-checking is done. "
		"initializeParameters() is called implicitly."
		},
	{"getCamera", (PyCFunction)ldm_getCamera, METH_VARARGS,
		"Signature: getCamera() -> (double,double,double,double,double,double,double).\n"
		"This method returns the seven built-in camera parameters at once. "
		"The parameters are (in this order): focal length [cm], filmback width [cm], filmback height [cm], "
		"lens center offset x [cm], lens center offset y [cm], pixel aspect, focus distance [cm]. "
		},
	{NULL}
	};

static PyTypeObject anamorphic_deg_4_rotate_squeeze_xy_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)anamorphic_deg_4_rotate_squeeze_xy,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyTypeObject anamorphic_deg_6_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)anamorphic_deg_6,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyTypeObject radial_deg_8_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)radial_deg_8,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyTypeObject radial_decentered_deg_4_cylindric_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)radial_decentered_deg_4_cylindric,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyTypeObject classic_3de_mixed_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)classic_3de_mixed,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyTypeObject blender_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)blender,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};
	
static PyTypeObject all_par_types_Type = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"lens_distortion_plugins.tde4_ldp_py_wrapper",             /*tp_name*/
	sizeof(tde4_ldp_py_wrapper),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)ldm_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"tde4_ldp_py_wrapper objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	ldm_methods,             /* tp_methods */
	ldm_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)all_par_types,      /* tp_init */
	0,                         /* tp_alloc */
	ldm_new,                 /* tp_new */
	};

static PyMethodDef module_methods[] = {
	{NULL}
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC initlens_distortion_plugins(void) 
	{
	PyObject* m;

	if (PyType_Ready(&anamorphic_deg_4_rotate_squeeze_xy_Type) < 0)
		return;
	if (PyType_Ready(&anamorphic_deg_6_Type) < 0)
		return;
	if (PyType_Ready(&radial_deg_8_Type) < 0)
		return;
	if (PyType_Ready(&radial_decentered_deg_4_cylindric_Type) < 0)
		return;
	if (PyType_Ready(&classic_3de_mixed_Type) < 0)
		return;
	if (PyType_Ready(&blender_Type) < 0)
		return;

	if (PyType_Ready(&all_par_types_Type) < 0)
		return;

	m = Py_InitModule3("lens_distortion_plugins", module_methods,"modul which provides.");

	if (m == NULL)
		return;

	PyModule_AddObject(m,"TDE4_LDP_STRING",PyInt_FromLong(0));
	PyModule_AddObject(m,"TDE4_LDP_DOUBLE",PyInt_FromLong(1));
	PyModule_AddObject(m,"TDE4_LDP_INT",PyInt_FromLong(2));
	PyModule_AddObject(m,"TDE4_LDP_FILE",PyInt_FromLong(3));
	PyModule_AddObject(m,"TDE4_LDP_TOGGLE",PyInt_FromLong(4));
	PyModule_AddObject(m,"TDE4_LDP_ADJUSTABLE_DOUBLE",PyInt_FromLong(5));

	Py_INCREF(&anamorphic_deg_4_rotate_squeeze_xy_Type);
	PyModule_AddObject(m,"anamorphic_deg_4_rotate_squeeze_xy",	(PyObject *)&anamorphic_deg_4_rotate_squeeze_xy_Type);

	Py_INCREF(&anamorphic_deg_6_Type);
	PyModule_AddObject(m,"anamorphic_deg_6",			(PyObject *)&anamorphic_deg_6_Type);

	Py_INCREF(&radial_deg_8_Type);
	PyModule_AddObject(m,"radial_deg_8",				(PyObject *)&radial_deg_8_Type);

	Py_INCREF(&radial_decentered_deg_4_cylindric_Type);
	PyModule_AddObject(m,"radial_decentered_deg_4_cylindric",	(PyObject *)&radial_decentered_deg_4_cylindric_Type);

	Py_INCREF(&classic_3de_mixed_Type);
	PyModule_AddObject(m,"classic_3de_mixed",			(PyObject *)&classic_3de_mixed_Type);

	Py_INCREF(&blender_Type);
	PyModule_AddObject(m,"blender",			(PyObject *)&blender_Type);

	Py_INCREF(&all_par_types_Type);
	PyModule_AddObject(m,"any_ldm",					(PyObject *)&all_par_types_Type);
	}

// g++ -g -O2 -shared -fPIC tde4_lens_distortion_plugins.module.C -I /usr/include/python2.7 -I ../../include -o lens_distortion_plugins.so
// devil: g++ -g -O2 -shared -fPIC tde4_ldp.module.C -I /server/devel/extern/linux64/python_sdv/install_dir/include/python2.6 -I ../../include -o lens_distortion_plugins.so
// das ist dann python 2.6, kompatibel zu Nuke.


