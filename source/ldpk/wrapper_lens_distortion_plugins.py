import lens_distortion_plugins as ldp

class anamorphic_deg_4_rotate_squeeze_xy(ldp.anamorphic_deg_4_rotate_squeeze_xy):
	def __init__(self):
		ldp.anamorphic_deg_4_rotate_squeeze_xy.__init__(self)
		self.parameters = [self.getParameterName(i) for i in range(self.getNumParameters())]
	def __iter__(self):
		return self.parameters.__iter__()

class anamorphic_deg_6(ldp.anamorphic_deg_6):
	def __init__(self):
		ldp.anamorphic_deg_6.__init__(self)
		self.parameters = [self.getParameterName(i) for i in range(self.getNumParameters())]
	def __iter__(self):
		return self.parameters.__iter__()

class radial_deg_8(ldp.radial_deg_8):
	def __init__(self):
		ldp.radial_deg_8.__init__(self)
		self.parameters = [self.getParameterName(i) for i in range(self.getNumParameters())]
	def __iter__(self):
		return self.parameters.__iter__()

class radial_decentered_deg_4_cylindric(ldp.radial_decentered_deg_4_cylindric):
	def __init__(self):
		ldp.radial_decentered_deg_4_cylindric.__init__(self)
		self.parameters = [self.getParameterName(i) for i in range(self.getNumParameters())]
	def __iter__(self):
		return self.parameters.__iter__()

class classic_3de_mixed(ldp.classic_3de_mixed):
	def __init__(self):
		ldp.classic_3de_mixed.__init__(self)
		self.parameters = [self.getParameterName(i) for i in range(self.getNumParameters())]
	def __iter__(self):
		return self.parameters.__iter__()

