.. Python bindings for LDPK documentation master file, created by
   sphinx-quickstart on Sun Oct 20 21:45:43 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Python bindings for LDPK
========================

.. toctree::
   :maxdepth: 2

.. module:: lens_distortion_plugins

Indices and tables
==================

* :ref:`genindex`
* :ref:`search`

.. testsetup::

	import lens_distortion_plugins as ldp

Introduction
============

The Lens Distortion Plugin Kit (LDPK) provides a python module which allows to use the five
built-in lens distortion models in python. When we use this module, we import it this way:

.. doctest::

	>>> import lens_distortion_plugins as ldp

Classes
=======

There is a class for each of the five built-in lens distortion models.
The python classes are:

.. autoclass:: anamorphic_deg_6
.. autoclass:: anamorphic_deg_4_rotate_squeeze_xy
.. autoclass:: radial_deg_8
.. autoclass:: radial_decentered_deg_4_cylindric
.. autoclass:: classic_3de_mixed

The human-readable name as it appears in 3DE4 is given by the method

.. automethod:: any_ldm.getModelName

.. doctest::

	>>> print ldp.anamorphic_deg_6().getModelName()
	3DE4 Anamorphic, Degree 6

.. doctest::

	>>> print ldp.anamorphic_deg_4_rotate_squeeze_xy().getModelName()
	3DE4 Anamorphic - Standard, Degree 4

.. doctest::

	>>> print ldp.radial_deg_8().getModelName()
	3DE4 Radial - Fisheye, Degree 8

.. doctest::

	>>> print ldp.radial_decentered_deg_4_cylindric().getModelName()
	3DE4 Radial - Standard, Degree 4

.. doctest::

	>>> print ldp.classic_3de_mixed().getModelName()
	3DE Classic LD Model

Parameter name
==============

Parameters are addressed by their (human-readable) names. The following method maps the index
into the parameter name:

.. automethod:: any_ldm.getParameterName

Parameter types
===============

In 3DE4 each parameter of a lens distortion model (built-in or plugin) is represented
by a widget in Attribute Editor -> Lenses -> Lens Distortion. There are six different
widget types, and they are represented by the following symbolic (and numeric) values:

.. doctest::

	>>> print ldp.TDE4_LDP_STRING
	0
	>>> print ldp.TDE4_LDP_DOUBLE
	1
	>>> print ldp.TDE4_LDP_INT
	2
	>>> print ldp.TDE4_LDP_FILE
	3
	>>> print ldp.TDE4_LDP_TOGGLE
	4
	>>> print ldp.TDE4_LDP_ADJUSTABLE_DOUBLE
	5

Instead of strings we prefer to have the same numeric values here as we have in C++.
The type of a parameter is determined by

.. automethod:: any_ldm.getParameterType

.. doctest::

	>>> ldm = ldp.anamorphic_deg_6()
	>>> print ldm.getParameterType("Cx02 - Degree 2")
	5

The return value is one of the constants mentioned above.

Default value
=============

Each parameter has a default value. The default value is retrieved using the method

.. automethod:: any_ldm.getParameterDefaultValue

.. doctest::

	>>> ldm = ldp.anamorphic_deg_4_rotate_squeeze_xy()
	>>> print ldm.getParameterDefaultValue("Squeeze-X")
	1.0

Range
=====

Parameters of type ADJUSTABLE_DOUBLE have range values which describe the possible values
of the parameter. The range values are not strict mathematical limits, they are more some kind of
hints for 3DE4's optimization algorithms.

.. automethod:: any_ldm.getParameterRange

.. doctest::

	>>> ldm = ldp.radial_decentered_deg_4_cylindric()
	>>> print ldm.getParameterRange("Phi - Cylindric Direction")
	(-90.0, 90.0)

Setting parameter values
========================

There are four methods for setting parameter values individually.

.. automethod:: any_ldm.setParameterValueDouble

Parameters of types TDE4_LDP_DOUBLE and TDE4_LDP_ADJUSTABLE_DOUBLE must be set
with this method. The seven built-in parameters are of type TDE4_LDP_DOUBLE:

- tde4_focal_length_cm
- tde4_filmback_width_cm
- tde4_filmback_height_cm
- tde4_lens_center_offset_x_cm
- tde4_lens_center_offset_y_cm
- tde4_pixel_aspect
- tde4_focus_distance_cm

.. automethod:: any_ldm.setParameterValueBool
.. automethod:: any_ldm.setParameterValueInt
.. automethod:: any_ldm.setParameterValueString

The following methods allow to set and get the seven built-in camera parameters:

.. automethod:: any_ldm.setCamera
.. automethod:: any_ldm.getCamera

.. doctest::

	>>> import lens_distortion_plugins as ldp                                                                                                                                                                                                                                
	>>> ldm = ldp.radial_decentered_deg_4_cylindric()
	>>> ldm.setCamera(1.0,0.8,0.6,0.1,0.1,1.0,100.0)
	>>> print ldm.getCamera()
	(1.0, 0.8, 0.6, 0.1, 0.1, 1.0, 100.0)


Initializing for usage
======================

When all parameters are set, the instance needs to be initialized for usage. This is done by:

.. automethod:: any_ldm.initializeParameters

Remove and apply lens distortion
================================

.. automethod:: any_ldm.undistort
.. automethod:: any_ldm.distort

Bounding box
============

There are methods for getting the bounding box for the undistort- and the distort-function.
These methods are quite simple, they surround the domain of the function with some predefined
sample density and accumulate minimum and maximum function values. So, please do not expect
them to deliver values at precision 1e-15...

.. automethod:: any_ldm.getBoundingBoxUndistort
.. automethod:: any_ldm.getBoundingBoxDistort

.. doctest::

	>>> ldm = ldp.radial_decentered_deg_4_cylindric()
	>>> ldm.setParameterValueDouble("tde4_focal_length_cm",1.0)
	>>> ldm.setParameterValueDouble("tde4_filmback_width_cm",0.8)
	>>> ldm.setParameterValueDouble("tde4_filmback_height_cm",0.6)
	>>> ldm.setParameterValueDouble("tde4_pixel_aspect",1.0)
	>>> ldm.setParameterValueDouble("Distortion - Degree 2",0.1)
	>>> ldm.initializeParameters()
	>>> print ldm.getBoundingBoxUndistort(0,0,1,1)
	(-0.050000000000000044, -0.050000000000000044, 1.05, 1.05)
	>>> print ldm.getBoundingBoxDistort(0,0,1,1)
	(0.027077570819212873, 0.016296699052012663, 0.9729224291807872, 0.9837033009479873)

Derivatives
===========

The LDPK provides methods for accessing the Jacobian Matrix (first derivatives) and the so-called "Twist Vector" (mixed derivatives). 
The methods are:

.. automethod:: any_ldm.getJacobianMatrix
.. automethod:: any_ldm.getTwistVector

The derivatives are used in practice to build distortion nodes for compositing based on bicubic Hermite splices, like Nuke's GridWarp.

