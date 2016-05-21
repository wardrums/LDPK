# 3DE4.script.name:	Export Nuke LD_3DE4 Lens Distortion Node
# 3DE4.script.version:	v1.5
# 3DE4.script.gui:	Main Window::3DE4::File::Export
# 3DE4.script.comment:	Creates an LD_3DE4 Lens Distortion Node for each selected camera (exports .nk script)
# 3DE4.script.comment:	The five LD_3DE4 Nodes were introduced in Lens Distortion Plugin Kit version 1.7 (2013-12-11).
# 3DE4.script.comment:  With the release of Nuke8.0 we will update and promote these plugins on linux, osx and windows,
# 3DE4.script.comment:	also for Nuke6.2 (osx and linux), Nuke6.3 and Nuke7.0.
# 3DE4.script.comment:	This script should not be mistaken for "Export Weta Nuke Distortion"
#
# Author: Uwe Sassenberg (SDV)
# For 3DE4 releases r1 or higher
# Versions:
# 1.5 - Widgets for initial frames in 3DE4 and Nuke.
# 1.4 - Bugfixes
# 1.3 - Changes to due modified Python API
# 1.2 - Minor Changes for first official release
# 1.1 - Make sure it runs on R1
# 1.0 - Start, original script: Wolgang Niedermeier (Weta)


import tde4
import string
import re

# Debugging
fout = open("/dev/tty","w")

# We translate our API model and parameter names into Nuke identifiers.
# The rules are:
# - The empty string maps to an underscore
# - When the names starts with 0-9 it gets an underscore
# - All non-alphanumeric characters are mapped to underscores, but sequences
#   of underscores shrink to a single underscore, looks better.
def nukify_name(s):
	if s == "":
		return "_"
	if s[0] in "0123456789":
		t = "_"
	else:
		t = ""
	t += string.join(re.sub("[+,:; _-]+","_",s.strip()).split())
	return t

# Nuke interprets entities like "<" and ">", so we shall expand them.
def decode_entities(s):
	return s.replace("&","&amp;").replace("<","&lt;").replace(">","&gt;")

# By this function we determine the dynamic mode of lens distortion.
def get_dynamic_distortion_mode(id_lens):
	try:
		dyndistmode	= tde4.getLensDynamicDistortionMode(id_lens)
	except:
# For 3DE4 Release 1:
		if tde4.getLensDynamicDistortionFlag(id_lens) == 1:
			dyndistmode = "DISTORTION_DYNAMIC_FOCAL_LENGTH"
		else:
			dyndistmode = "DISTORTION_STATIC"
	return dyndistmode

# Similar but we're only interested in lens dynamic or not.
#def is_distortion_dynamic(id_lens):
#	return get_dynamic_distortion_mode(id_lens) != "DISTORTION_STATIC"

def is_focal_length_dynamic(id_cam):
	try:
# New API: we check for dynamic focal length.
		if tde4.getCameraFocalLengthMode(id_cam) == "FOCAL_DYNAMIC":
			return True
		else:
			return False
	except:
# Old API, e.g. Release 1: we check for dynamic focal length.
		if tde4.getCameraZoomingFlag(id_cam) == 1:
			return True
		else:
			return False

def is_focus_distance_dynamic(id_cam):
	try:
# New API: we check for dynamic focus distance.
		if tde4.getCameraFocusMode(id_cam) == "FOCUS_DYNAMIC":
			return True
		else:
			return False
	except:
# Release 1.
			return False

# Are there any frame dependent properties in the camera?
def is_camera_dynamic(id_cam):
	return is_focal_length_dynamic(id_cam) or is_focus_distance_dynamic(id_cam)

class CancelException(Exception):	
	pass

def getLDmodelParameterList(model):
	l = []
	for p in range(tde4.getLDModelNoParameters(model)):
		l.append(tde4.getLDModelParameterName(model, p))
	return l

def exportNukeDewarpNode(id_cam,offset,nuke_path):
	id_lens 	= tde4.getCameraLens(id_cam)
	model 	= tde4.getLensLDModel(id_lens)
	num_frames 	= tde4.getCameraNoFrames(id_cam)
	w_fb_cm = tde4.getLensFBackWidth(id_lens)
	h_fb_cm = tde4.getLensFBackHeight(id_lens)
	lco_x_cm = tde4.getLensLensCenterX(id_lens)
	lco_y_cm = tde4.getLensLensCenterY(id_lens)
	pxa = tde4.getLensPixelAspect(id_lens)
# xa,xb,ya,yb in unit coordinates, in this order.
	xa_unit,xb_unit,ya_unit,yb_unit = tde4.getCameraFOV(id_cam)
		
	f = open(nuke_path,"w")
	try:
		f.write('# Created by 3DEqualizer4 using Export Nuke Distortion Nodes export script\n')
		f.write("LD" + nukify_name(model) + ' {\n')
		f.write(' direction undistort\n')
################################
# focal length                 #
################################
		if is_focal_length_dynamic(id_cam):
# write focal length curve if dynamic
#			print 'dynamic focal length'
			f.write(' tde4_focal_length_cm {{curve ')	
			for frame in range(num_frames):
# Internally, frames start at 1.
				focal = tde4.getCameraFocalLength(id_cam,frame + 1)
				f.write ('x%i %.7f ' % (frame + offset,focal))
			f.write('}}\n')
		else:
# write static focal length otherwise
#			print 'static focal length'
			f.write(' tde4_focal_length_cm %.7f \n' % tde4.getCameraFocalLength(id_cam,1))
################################
# focus distance               #
################################
# For Release 1 this function return False, so no problem with getCameraFocus.
		if is_focus_distance_dynamic(id_cam):
# write focus distance curve if dynamic
#			print 'dynamic focus distance'
			f.write(' tde4_custom_focus_distance_cm {{curve ')	
			for frame in range(num_frames):
# Internally, frames start at 1.
				focus = tde4.getCameraFocus(id_cam,frame + 1)
				f.write ('x%i %.7f ' % (frame + offset,focus))
			f.write('}}\n')
		else:
			try:
# write static focus distance otherwise
				f.write(' tde4_custom_focus_distance_cm %.7f \n' % tde4.getCameraFocus(id_cam,1))
			except:
# For Release 1 we simply write out the default value to Nuke.
				f.write(' tde4_custom_focus_distance_cm 100.0 \n')
################################
# built-in parameters          #
################################
# the remaining five built-in parameters
		f.write(' tde4_filmback_width_cm %.7f \n' % w_fb_cm)
		f.write(' tde4_filmback_height_cm %.7f \n' % h_fb_cm)
		f.write(' tde4_lens_center_offset_x_cm %.7f \n' % lco_x_cm)
		f.write(' tde4_lens_center_offset_y_cm %.7f \n' % lco_y_cm)
		f.write(' tde4_pixel_aspect %.7f \n' % pxa)
################################
# field-of-view                #
################################
		f.write(' field_of_view_xa_unit %.7f \n' % xa_unit)
		f.write(' field_of_view_xb_unit %.7f \n' % xb_unit)
		f.write(' field_of_view_ya_unit %.7f \n' % ya_unit)
		f.write(' field_of_view_yb_unit %.7f \n' % yb_unit)
		
# write distortion parameters
#
# dynamic distortion
		dyndistmode = get_dynamic_distortion_mode(id_lens)

		old_api = True
		try:
			for para in getLDmodelParameterList(model):
				tde4.getLensLDAdjustableParameter(id_lens, para, 1)
				break
		except:
			old_api = False

		if old_api:
# dynamic focal length (zoom)
			if dyndistmode=="DISTORTION_DYNAMIC_FOCAL_LENGTH":
#				print 'dynamic lens distortion, focal length'
				for para in getLDmodelParameterList(model):
					f.write(' ' + nukify_name(para) + ' {{curve ')	
					for frame in range(num_frames):
# Internally, frames start at 1.
						focal = tde4.getCameraFocalLength(id_cam,frame + 1)
						f.write ('x%i %.7f ' % (frame + offset,tde4.getLensLDAdjustableParameter(id_lens,para,focal)))
					f.write('}}\n')
# dynamic focus distance
			if dyndistmode=="DISTORTION_DYNAMIC_FOCUS_DISTANCE":
#				print 'dynamic lens distortion, focus distance'
				for para in getLDmodelParameterList(model):
					f.write(' ' + nukify_name(para) + ' {{curve ')	
					for frame in range(num_frames):
# Older Releases do not have Focus-methods.
						try:
# Internally, frames start at 1.
							focus = tde4.getCameraFocus(id_cam,frame + 1)
						except:
							focus = 100.0
						f.write('x%i %.7f ' % (frame + offset,tde4.getLensLDAdjustableParameter(id_lens,para,focus)))
					f.write('}}\n')
# static distortion
			if dyndistmode=="DISTORTION_STATIC":
#				print 'static lens distortion'
				for para in getLDmodelParameterList(model):
					f.write(' ' + nukify_name(para) + ' %.7f \n'%tde4.getLensLDAdjustableParameter(id_lens,para,1))
		else:
# new API
			if dyndistmode=="DISTORTION_STATIC":
#				print 'static lens distortion'
				for para in getLDmodelParameterList(model):
					f.write(' ' + nukify_name(para) + ' %.7f \n'%tde4.getLensLDAdjustableParameter(id_lens,para,1,1))
			else:
#				print 'dynamic lens distortion,'
# dynamic
				for para in getLDmodelParameterList(model):
					f.write(' ' + nukify_name(para) + ' {{curve ')	
					for frame in range(num_frames):
# Internally, frames start at 1.
						focal = tde4.getCameraFocalLength(id_cam,frame + 1)
						focus = tde4.getCameraFocus(id_cam,frame + 1)
						f.write('x%i %.7f ' % (frame + offset,tde4.getLensLDAdjustableParameter(id_lens,para,focal,focus)))
#						print "%i[3DE4] -> %i[Nuke]" % (frame + tde4.getCameraFrameOffset(id_cam),frame + offset)
					f.write('}}\n')


		
		f.write(' name LD_3DE4_' + decode_entities(tde4.getCameraName(id_cam)) + '\n')
		f.write('}\n')

	finally:	
		f.close()	


def set_initial_frame_widget(wdg,a,b):
	val = tde4.getWidgetValue(nuke_node_req,"option_menu_default_initial_frame")
	try:
		initial_frame_3de4 = tde4.getCameraFrameOffset(id_cam)
	except:
		initial_frame_3de4 = 1
# 3 means user-defined. In this case the GUI allows to enter a frame value.
	if val == 3:
		tde4.setWidgetSensitiveFlag(nuke_node_req,"text_initial_frame_nuke",True)
	elif val == 2:
		tde4.setWidgetSensitiveFlag(nuke_node_req,"text_initial_frame_nuke",False)
		tde4.setWidgetValue(nuke_node_req,"text_initial_frame_nuke",str(initial_frame_3de4))
	elif val == 1:
		tde4.setWidgetSensitiveFlag(nuke_node_req,"text_initial_frame_nuke",False)
		tde4.setWidgetValue(nuke_node_req,"text_initial_frame_nuke",str(tde4.getCameraSequenceAttr(id_cam)[0]))


# main
try:
# camera and lens
	id_cam = tde4.getCurrentCamera()
	id_lens = tde4.getCameraLens(id_cam)

# check if variable 'nuke_path' exists already or is of type None
	try: 
		nuke_path
	except:
		nuke_path = ''
	if nuke_path is None:
		nuke_path = ''

# File widget
	nuke_node_req	= tde4.createCustomRequester()
	tde4.addFileWidget(nuke_node_req,'file_nuke_path', 'Filename: ', '*.nk', nuke_path)

# Get smart start value for initial frame option menu.
	try:
		initial_frame_3de4 = tde4.getCameraFrameOffset(id_cam)
	except:
		initial_frame_3de4 = 1
	if initial_frame_3de4 == 1:
# Mimicking Nuke's Read Node default behaviour.
		value_option_menu_default_initial_frame = 1
	else:
# Using 3DE4 initial frame
		value_option_menu_default_initial_frame = 2

	try:
		tde4.setWidgetCallbackFunction
		we_have_set_widget_callback_function = True
	except:
		we_have_set_widget_callback_function = False

# For older releases we cannot do the smart guessing...
	if we_have_set_widget_callback_function:
		widget_default_initial_frame = tde4.addOptionMenuWidget(nuke_node_req,"option_menu_default_initial_frame","Startframe is based on","Nuke Read Node Default","3DE4 Initial Frame","User-defined")
		tde4.setWidgetValue(nuke_node_req,"option_menu_default_initial_frame",str(value_option_menu_default_initial_frame))
		tde4.setWidgetCallbackFunction(nuke_node_req,"option_menu_default_initial_frame","set_initial_frame_widget")
# Without / before smart-guessing we mimick Nuke's Read Node default behaviour.
	tde4.addTextFieldWidget(nuke_node_req,"text_initial_frame_nuke","Startframe in Nuke",str(tde4.getCameraSequenceAttr(id_cam)[0]))

# After creating all widgets we invoke the Callback once explicitly in order to initialize the text widget.
	if we_have_set_widget_callback_function:
		set_initial_frame_widget(widget_default_initial_frame,None,None)

# post requester
	ret	= tde4.postCustomRequester(nuke_node_req,'Export nuke distortion node for camera ' + tde4.getCameraName(id_cam)+' ',700,0,'Ok','Cancel ')
	if ret != 1:
		raise CancelException('Cancelled')
# At this point we know that user has pressed "Ok". Check path and suffix
	nuke_path = tde4.getWidgetValue(nuke_node_req,'file_nuke_path')
	if not nuke_path:
		raise Exception('No path specified')
	if not nuke_path.endswith('.nk'):
		nuke_path += '.nk'
# Update frame values and calculate offset between 3DE4 and Nuke.
	initial_frame_nuke = int(tde4.getWidgetValue(nuke_node_req,"text_initial_frame_nuke"))
# export
	exportNukeDewarpNode(id_cam,initial_frame_nuke,nuke_path)

except CancelException, e:
	pass

except Exception, e:
	tde4.postQuestionRequester('Error ', str(e), '  OK  ')

