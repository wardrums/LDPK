#!/usr/bin/python

import sys
import math

try:
	import lens_distortion_plugins as ldp
except:
	print "Couldn't import module 'lens_distortion_plugins'."
	print "Most likely, python doesn't know where it is located."
	print "Please move the module file 'lens_distortion_plugins.so'"
	print "to some place where python modules are located on your system "
	print "or add the path to 'lens_distortion_plugins.so' to your python paths, "
	print "e.g. by modifying the environment variable PYTHONPATH appropriately."
	sys.exit()


def test1():
	ldm = ldp.radial_decentered_deg_4_cylindric()
	ldm.setParameterValueDouble("tde4_filmback_width_cm",1.6)
	ldm.setParameterValueDouble("tde4_filmback_height_cm",1.2)
	ldm.setParameterValueDouble("tde4_focal_length_cm",2.0)
	ldm.setParameterValueDouble("tde4_pixel_aspect",1.0)
	ldm.setParameterValueDouble("Distortion - Degree 2",0.1)
	ldm.setParameterValueDouble("Quartic Distortion - Degree 4",0.1)
	ldm.initializeParameters()

	for iy in range(11):
		for ix in range(11):
			xp = ix / 10.0
			yp = iy / 10.0
			xq,yq = ldm.undistort((xp,yp))
			xr,yr = ldm.distort((xq,yq))
# output as table, with numeric error
			print "(%f,%f) -> (%f,%f) -> (%f,%f), mismatch: %e" % (xp,yp,xq,yq,xr,yr,math.sqrt((xr-xp)**2+(yr-yp)**2))
# output for gnuplot: plot ... with vectors
#			print "%f %f %f %f" % (xp,yp,xq - xp,yq - yp)
		

# An anamorphic example with realistic numbers (lens rotation!)
def test2():
	ldm = ldp.anamorphic_deg_4_rotate_squeeze_xy()
	ldm.setParameterValueDouble("tde4_filmback_width_cm",4.9152)
	ldm.setParameterValueDouble("tde4_filmback_height_cm",1.8672)
	ldm.setParameterValueDouble("tde4_focal_length_cm",7.5)
	ldm.setParameterValueDouble("tde4_pixel_aspect",2.0)
	ldm.setParameterValueDouble("Cx02 - Degree 2",0.1693)
	ldm.setParameterValueDouble("Cy02 - Degree 2",0.1032)
	ldm.setParameterValueDouble("Cx22 - Degree 2",0.1247)
	ldm.setParameterValueDouble("Cy22 - Degree 2",0.1005)
	ldm.setParameterValueDouble("Cx04 - Degree 4",0.1023)
	ldm.setParameterValueDouble("Cy04 - Degree 4",0.1057)
	ldm.setParameterValueDouble("Cx24 - Degree 4",0.1289)
	ldm.setParameterValueDouble("Cy24 - Degree 4",-0.0004)
	ldm.setParameterValueDouble("Cx44 - Degree 4",0.0215)
	ldm.setParameterValueDouble("Cy44 - Degree 4",0.0327)
	ldm.setParameterValueDouble("Lens Rotation",-1.5357)
	ldm.setParameterValueDouble("Squeeze-X",0.9799)
	ldm.setParameterValueDouble("Squeeze-Y",1.0)
	ldm.initializeParameters()

	max_mismatch = 0
	for iy in range(11):
		for ix in range(11):
			xp = ix / 10.0
			yp = iy / 10.0
			xq,yq = ldm.undistort((xp,yp))
			xr,yr = ldm.distort((xq,yq))
			mismatch = math.sqrt((xr-xp)**2+(yr-yp)**2)
			if mismatch > max_mismatch:
				max_mismatch = mismatch
# output as table, with numeric error
			print "(%f,%f) -> (%f,%f) -> (%f,%f), mismatch: %e" % (xp,yp,xq,yq,xr,yr,mismatch)
# output for gnuplot: plot ... with vectors
#			print "%f %f %f %f" % (xp,yp,xq - xp,yq - yp)
	print "max_mismatch: %e" % max_mismatch

	print ldm.getJacobianMatrix((0.5,0.5))
	print ldm.getTwistVector((0.5,0.5))

test1()
test2()



