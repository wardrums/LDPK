#!/usr/bin/python
# Print parameters of all built-in models
# default values and ranges.

import sys

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

def print_plugin_info(ldm):
	print ldm.getModelName()
	for i in range(ldm.getNumParameters()):
		name = ldm.getParameterName(i)
		val = ldm.getParameterDefaultValue(name)
		print "%d: %s, default: %s" % (i,name,str(val)),
		if ldm.getParameterType(name) == ldp.TDE4_LDP_ADJUSTABLE_DOUBLE:
			print ", range: ",ldm.getParameterRange(name)
		else:
			print
	print "----------------------------------------"


ldm = ldp.anamorphic_deg_4_rotate_squeeze_xy()
print_plugin_info(ldm)
ldm = ldp.anamorphic_deg_6()
print_plugin_info(ldm)
ldm = ldp.radial_deg_8()
print_plugin_info(ldm)
ldm = ldp.radial_decentered_deg_4_cylindric()
print_plugin_info(ldm)
ldm = ldp.classic_3de_mixed()
print_plugin_info(ldm)
ldm = ldp.any_ldm()
print_plugin_info(ldm)


