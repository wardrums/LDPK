// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_plugin_loader.h>
#include <ldpk/ldpk_model_parser.h>
#include <ldpk/ldpk_table_generator.h>
#include <fstream>
#include <stdlib.h>

using namespace std;
using namespace ldpk;

int main(int argc,const char** argv)
	{
	plugin_loader pl;
	model_parser mp;
	table_generator tg;
// Number of grid points per dimension.
	int nx = 21,ny = 15;

	if(argc != 4)
		{
		cerr << "usage: ... </path/to/plugin.so> <input_parameter_file> <output_gnuplot_file>" << endl;
		cerr << "input_parameter_file: a list of name-value pairs. Example:" << endl;
		cerr << "\ttde4_filmback_width_cm 2.4" << endl;
		cerr << "\ttde4_filmback_height_cm 1.8" << endl;
		cerr << "\t..." << endl;
		cerr << "\t'Degree 2' 0.1" << endl;
		cerr << "output_gnuplot_file: name of file to be created for gnuplot data" << endl;
		exit(-1);
		}
	ifstream fin_parameter(argv[2]);
	ofstream fout(argv[3]);
	if(!fin_parameter.good())
		{
		cerr << "could not open parameter file '" << argv[2] << "'." << endl;
		exit(-1);
		}
	if(!fout.good())
		{
		cerr << "could not open output file '" << argv[3] << "'." << endl;
		}

	try
		{
// Load plugin
		pl.open_plugin(argv[1]);
// Parse parameters
		mp.set_model(pl.get_model());
		mp.parse(fin_parameter);
// Generate gnuplot data
		tg.set_model(pl.get_model());
		tg.set_grid_size(nx,ny);
		tg.out_gnuplot(fout);
		}
	catch(const ldpk::error_base& e)
		{
		cerr << e.what() << endl;
		e.out(cerr) << endl;
		}
	}
