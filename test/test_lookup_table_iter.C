// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk.h>
#include <sstream>

using namespace std;
using namespace ldpk;

// This program demonstrates how iterating is done in the lookup table.

int main()
	{
	lookup_table<vec2d> lut;
	stringstream sout;
	string s[5 * 7 * 5];

// Initializing
	lut.init(7,5);
	lut.set_lens_center_fov(vec2d(.4,.3));
// Iterating
	lut.reset();
	while(lut.next())
		{
		lut.out_state(sout);
		}

// Only for pretty printing
	for(int i = 0;i < 5 * 7 * 5;++i)
		{
		sout >> s[i];
		}
	for(int j = 0;j < 5;++j)
		{
		for(int i = 0;i < 5;++i)
			{
			for(int k = 0;k < 7;++k)
				{
				cout << s[i + 5 * 7 * j + 5 * k] << "     ";
				}
			cout << endl;
			}
		cout << endl;
		}
	}
