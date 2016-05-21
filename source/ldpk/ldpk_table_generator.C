// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_table_generator.h>
#include <ldpk/ldpk_error.h>

using namespace std;

namespace ldpk
	{
	void table_generator::out_gnuplot(ostream& cout)
		{
		if(_model == 0) throw error_no_model_specified();
		
		for(int iy = 0;iy < _ny;++iy)
			{
			double y0 = double(iy) / (_ny - 1);
			for(int ix = 0;ix < _nx;++ix)
				{
				double x0 = double(ix) / (_nx - 1);
				double x1,y1;
				_model->undistort(x0,y0,x1,y1);
				cout << x0 << " " << y0 << " " << x1 - x0 << " " << y1 - y0 << endl;
				}
			}
		}
	}
