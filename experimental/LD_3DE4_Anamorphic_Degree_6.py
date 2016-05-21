import lens_distortion_plugins as ldp
import string
import re

# Here we use the python bindings in order to create a lens distortion node
# base on Nuke's GridWarp. User knobs for each ld- and camera-parameter are added to GridWarp.
# The grid controls (positions and tangents) are equipped with expressions which evaluate
# the ld- and camera-parameters.

# I'm stuck here: don't know how to set python expressions for each vertex and tangent individually.

def nukify_name(s):
	return string.join(re.sub("[+,:; _-]+","_",s.strip()).split())

ldm = ldp.anamorphic_deg_6()
g = nuke.nodes.GridWarp()
k = nuke.Double_Knob("fov_xa_unit","fov left [unit coord]")
k.setDefaultValue([0.0])
k.setRange(0.0,1.0)
g.addKnob(k)
k = nuke.Double_Knob("fov_ya_unit","fov bottom [unit coord]")
k.setDefaultValue([0.0])
k.setRange(0.0,1.0)
g.addKnob(k)
k = nuke.Double_Knob("fov_xb_unit","fov right [unit coord]")
k.setDefaultValue([1.0])
k.setRange(0.0,1.0)
g.addKnob(k)
k = nuke.Double_Knob("fov_yb_unit","fov top [unit coord]")
k.setDefaultValue([1.0])
k.setRange(0.0,1.0)
g.addKnob(k)
k = nuke.Double_Knob("tde4_filmback_width_cm","tde4 filmback width [cm]")
k.setDefaultValue([0.8])
k.setRange(0.1,10.0)
g.addKnob(k)
k = nuke.Double_Knob("tde4_filmback_height_cm","tde4 filmback height [cm]")
k.setDefaultValue([0.6])
k.setRange(0.1,10.0)
g.addKnob(k)
k = nuke.Double_Knob("tde4_focal_length_cm","tde4 focal length [cm]")
g.addKnob(k)
k = nuke.Double_Knob("tde4_focus_distance_cm","tde4 focus distance [cm]")
g.addKnob(k)
k = nuke.Double_Knob("tde4_lens_center_offset_x_cm","tde4 lens center offset x [cm]")
g.addKnob(k)
k = nuke.Double_Knob("tde4_lens_center_offset_y_cm","tde4 lens center offset y [cm]")
g.addKnob(k)
k = nuke.Double_Knob("tde4_pixel_aspect","tde4 pixel aspect")
g.addKnob(k)
for i in range(ldm.getNumParameters()):
	name = ldm.getParameterName(i)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_ADJUSTABLE_DOUBLE:
		k = nuke.Double_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		k.setRange(*ldm.getParameterRange(name))
		g.addKnob(k)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_DOUBLE:
		k = nuke.Double_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		g.addKnob(k)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_INT:
		k = nuke.Int_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		g.addKnob(k)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_STRING:
		k = nuke.String_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		g.addKnob(k)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_FILE:
		k = nuke.File_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		g.addKnob(k)
	if ldm.getParameterType(name) == ldp.TDE4_LDP_TOGGLE:
		k = nuke.Bool_Knob(nukify_name(name),name)
		k.setDefaultValue([ldm.getParameterDefaultValue(name)])
		g.addKnob(k)

