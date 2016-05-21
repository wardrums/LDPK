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

# Convert box from unit to pixel
def unit2px(w_px,h_px,box):
	return w_px * box[0],h_px * box[1],w_px * box[2],h_px * box[3]

def get_bounding_box(direction):

	ldm = ldp.classic_3de_mixed()

# Not a realistic filmback, just proxy data
	ldm.setParameterValueDouble("tde4_filmback_width_cm",1.92)
	ldm.setParameterValueDouble("tde4_filmback_height_cm",1.08)
	ldm.setParameterValueDouble("tde4_focal_length_cm",7.5)
	ldm.setParameterValueDouble("tde4_pixel_aspect",1.0)

	ldm.setParameterValueDouble("Distortion",0.02)
	ldm.setParameterValueDouble("Anamorphic Squeeze",1.0)
	ldm.setParameterValueDouble("Curvature X",0.02)
	ldm.setParameterValueDouble("Curvature Y",0.02)
	ldm.setParameterValueDouble("Quartic Distortion",0.02)

	ldm.initializeParameters()

	if direction == "undistort":
		return ldm.getBoundingBoxUndistort(0,0,1,1,32,32)
	elif direction == "distort":
		return ldm.getBoundingBoxDistort(0,0,1,1,32,32)
	else:
		return [0,0,1,1]

print unit2px(1920,1080,get_bounding_box("undistort"))




