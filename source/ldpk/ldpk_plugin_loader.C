// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_plugin_loader.h>
#include <ldpk/ldpk_error.h>
#include <iostream>

using namespace std;

namespace ldpk
	{
	void plugin_loader::open_plugin(const std::string& path)
		{
		const char* dlmsg;
		void* plugin;

		_model = 0;
// Open plugin
		plugin = dlopen(path.c_str(),_mode);
		dlmsg = dlerror();
		if(!plugin)
			{
			if(_verbose) cerr << "error: could not open plugin '" << path << "'" << endl;
			throw error_dynamic_link(dlmsg);
			}
// Find creator and destroyer symbols
		_create_plugin = (tde4ldp_create_fct_t*)dlsym(plugin,"tde4ldp_create_fct");
		dlmsg = dlerror();
		if(dlmsg)
			{
			if(_verbose) cerr << "error: cannot load symbol 'tde4ldp_create_fct'" << endl;
			throw error_dynamic_link(dlmsg);
			}
		_destroy_plugin = (tde4ldp_destroy_fct_t*)dlsym(plugin,"tde4ldp_destroy_fct");
		dlmsg = dlerror();
		if(dlmsg)
			{
			if(_verbose) cerr << "error: cannot load symbol 'tde4ldp_destroy_fct'" << endl;
			throw error_dynamic_link(dlmsg);
			}
// Create model instance
		_model = (*_create_plugin)();
		if(_model == 0)
			{
			throw error_dynamic_link("error: could not create instance of distortion model class");
			}
		}
	void plugin_loader::close_plugin()
		{
		if(_model)
			{
			(*_destroy_plugin)(_model);
			_model = 0;
			}
		}
	}
