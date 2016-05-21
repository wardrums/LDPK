// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_model_parser.h>
#include <cmath>

using namespace std;

namespace ldpk
	{
	bool model_parser::parse_string_optional(std::istream& cin,std::string& s)
		{
		cin >> ws;
		if(cin.eof()) return false;
// If end of stream was not reached, we can parse a string.
		try
			{
			parse_string(cin,"<none>",s);
			}
		catch(...)
			{
			error_could_not_read_parameter_name();
			}
		return true;
		}
	void model_parser::parse_string(std::istream& cin,const string& par,string& s)
		{
		char c_open,c;

		s = "";
		cin >> ws;
// Check for quotation character
		c_open = cin.get();
		if(cin.fail()) throw error_could_not_read_value(par);
		if((c_open != '\'') && (c_open != '"'))
			{
			cin.putback(c_open);
// Not a quotation character, then simply read string.
			cin >> s;
			if(cin.fail()) throw error_could_not_read_value(par);
			}
		else
			{
// Read characters until same quotation character occurs
			while(true)
				{
				c = cin.get();
				if(cin.fail()) throw error_could_not_read_value(par);
				if(c == c_open)
					{
// Closing quotation character found.
					break;
					}
				s += c;
				}
			}
		}
	void model_parser::parse_double(std::istream& cin,const string& par,double& v)
		{
		cin >> ws >> v;
		if(cin.fail()) throw error_could_not_read_value(par);
		}
	void model_parser::parse_int(std::istream& cin,const string& par,int& v)
		{
		cin >> ws >> v;
		if(cin.fail()) throw error_could_not_read_value(par);
		}
	void model_parser::parse_bool(std::istream& cin,const string& par,bool& v)
		{
		cin >> ws >> v;
		if(cin.fail()) throw error_could_not_read_value(par);
		}
	void model_parser::parse(std::istream& cin)
		{
		string name;

// Remember format flags
		ios_base::fmtflags fmt = cin.flags();
		cin.flags(ios::boolalpha);
		try
			{
// Read name-value pairs until end of stream
			while(parse_string_optional(cin,name))
				{
				if(!name.empty() && (name[0] == '#'))
					{
// That's a comment. Read the entire line and restart parsing.
					string skipped;
					getline(cin,skipped);
					continue;
					}
				
				if(_verbose) cout << "parameter: " << name << endl;
// Find out type of parameter
				tde4_ldp_ptype ptype;
// Check parameter name and get type
				if(!_model->getParameterType(name.c_str(),ptype))
					{
					throw error_undefined_parameter(name);
					}
// Read value of given type
				switch(ptype)
					{
					case TDE4_LDP_STRING:
					case TDE4_LDP_FILE:
						{
						string v;
						parse_string(cin,name,v);
						if(_verbose) cout << "value: " << v << endl;
						_model->setParameterValue(name.c_str(),v.c_str());
						break;
						}
					case TDE4_LDP_DOUBLE:
					case TDE4_LDP_ADJUSTABLE_DOUBLE:
						{
						double v;
						parse_double(cin,name,v);
						if(_verbose) cout << "value: " << v << endl;
						_model->setParameterValue(name.c_str(),v);
						break;
						}
					case TDE4_LDP_INT:
						{
						int v;
						parse_int(cin,name,v);
						if(_verbose) cout << "value: " << v << endl;
						_model->setParameterValue(name.c_str(),v);
						break;
						}
					case TDE4_LDP_TOGGLE:
						{
						bool v;
						parse_bool(cin,name,v);
						if(_verbose) cout << "value: " << v << endl;
						_model->setParameterValue(name.c_str(),v);
						break;
						}
					}
				}
// All parameters set
			_model->initializeParameters();
			}
		catch(...)
			{
// Reset format flags
			cin.flags(fmt);
			throw;
			}
		}
	}
