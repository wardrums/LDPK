// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk.h>

using namespace std;
using namespace ldpk;

// A test program for radial decentered distortion.

int main()
	{
	ldpk::radial_decentered_distortion<vec2d,mat2d> model;

// Specify distortion coefficients
	model.set_coeff(0,0.2);
	model.set_coeff(3,-0.1);

// We simulate a camera: Filmback in cm.
	double w_fb_cm = 3.2,h_fb_cm = 2.4;
// Diagonal radius in cm. Our model expects diagonally normalized coordinates.
	double r_fb_cm = sqrt(w_fb_cm * w_fb_cm + h_fb_cm * h_fb_cm) / 2.0;

// Sample points
	int nx = 10,ny = 10;
	for(int iy = -ny;iy <= +ny;++iy)
		{
		for(int ix = -nx;ix <= +nx;++ix)
			{
// x and y in [-1,+1]
			double x_unit = double(ix) / nx;
			double y_unit = double(iy) / ny;

// Coordinates with diagonal radius = 1.0
			vec2d p;
			p[0] = x_unit * w_fb_cm / (2.0 * r_fb_cm);
			p[1] = y_unit * h_fb_cm / (2.0 * r_fb_cm);

// Unwarp
			vec2d q = model(p);

// Print vector data for gnuplot (command "plot ... with vector").
			cout << p[0] << " " << p[1] << " " << (q - p) << endl;
			}
		}
	}

