// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_plugin_loader.h>
#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>

using namespace std;
using namespace ldpk;

int main(int argc,char** argv)
	{
	if(argc != 2)
		{
		cerr << "usage: test_plugin_loader </preferably/absolute/path/to/plugin.so>" << endl;
		exit(-1);
		}
	plugin_loader l;
	l.open_plugin(argv[1]);
	if(l.get_model())
		{
// Write plugin info to stdout, close and exit.
		int num_parameters;
		l.get_model()->getNumParameters(num_parameters);

		char model_name[100];
		l.get_model()->getModelName(model_name);

		cout << "number of parameters: " << num_parameters << endl;
		cout << "model name: '" << model_name << "'" << endl;

		for(int i = 0;i < num_parameters;++i)
			{
			char parameter_name[100];
			tde4_ldp_ptype parameter_type;
			double a,b;
			
			l.get_model()->getParameterName(i,parameter_name);
			l.get_model()->getParameterType(parameter_name,parameter_type);

			cout << "parameter: '" << parameter_name << "'" << endl;
			}

		l.close_plugin();
		}
	}

