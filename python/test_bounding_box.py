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

ldm = ldp.anamorphic_deg_4_rotate_squeeze_xy()

# This is a setup from a realistic grid shot, which caused trouble
# for a long time. Distortion is clearly visible, not extreme,
# but with considerable lens rotation (-1.5 degree).
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

#ldm.setParameterValueDouble("Cx02 - Degree 2",-0.1693)
#ldm.setParameterValueDouble("Cy02 - Degree 2",-0.1032)
#ldm.setParameterValueDouble("Cx22 - Degree 2",-0.1247)
#ldm.setParameterValueDouble("Cy22 - Degree 2",-0.1005)
#ldm.setParameterValueDouble("Cx04 - Degree 4",-0.1023)
#ldm.setParameterValueDouble("Cy04 - Degree 4",-0.1057)
#ldm.setParameterValueDouble("Cx24 - Degree 4",-0.1289)
#ldm.setParameterValueDouble("Cy24 - Degree 4",+0.0004)
#ldm.setParameterValueDouble("Cx44 - Degree 4",-0.0215)
#ldm.setParameterValueDouble("Cy44 - Degree 4",-0.0327)

ldm.setParameterValueDouble("Lens Rotation",-1.5357)
ldm.setParameterValueDouble("Squeeze-X",0.9799)
ldm.setParameterValueDouble("Squeeze-Y",1.0)
ldm.initializeParameters()

# Convert box from unit to pixel
def unit2px(w_px,h_px,box):
	return w_px * box[0],h_px * box[1],w_px * box[2],h_px * box[3]

# Calculate Bounding Box and reformulate for 4k-images
# The arguments nx,ny indicate, how many points are sampled
# per edge (nx,ny means nx+1,ny+1 samples).
# The 32x32-scan method runs 10000 times/sec on my machine,
# without multithreading. We use simple scanning, no approximation
# by cubic splines.
print "start"
if False:
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,2,2))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,4,4))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,8,8))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,16,16))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,32,32))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,64,64))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,128,128))
	print unit2px(4096,2048,ldm.getBoundingBoxUndistort(0,0,1,1,256,256))
else:
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,2,2))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,4,4))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,8,8))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,16,16))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,32,32))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,64,64))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,128,128))
	print unit2px(4096,2048,ldm.getBoundingBoxDistort(0,0,1,1,256,256))
print "stop"

# result in px for 4k-images, copy-pasted from console.
# The results clearly show that it's not enough to sample four corners
# and four edge-centered points, but from 32x32 samples upwards, changes
# are little.
"""
start
(80.4474396575805, 2.9400338449801167, 4015.5525603424194, 2045.0599661550198)
(80.4474396575805, -3.231828182046616, 4015.5525603424194, 2051.2318281820467)
(80.4474396575805, -3.231828182046616, 4015.5525603424194, 2051.2318281820467)
(80.4474396575805, -3.8582851905026825, 4015.5525603424194, 2051.8582851905026)
(80.4474396575805, -3.8582851905026825, 4015.5525603424194, 2051.8582851905026)
(80.4474396575805, -3.8582851905026825, 4015.5525603424194, 2051.8582851905026)
(80.4474396575805, -3.8582851905026825, 4015.5525603424194, 2051.8582851905026)
(80.4474396575805, -3.8607945871112173, 4015.5525603424194, 2051.8607945871113)
stop
"""
