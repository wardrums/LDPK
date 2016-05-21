// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <iostream>

using namespace std;

struct X
	{
	virtual void foo(const char* ident,const char* a)
		{
		cout << "foo(" << ident << ",const char*): " << a << endl;
		}
	virtual void foo(const char* ident,int a)
		{
		cout << "foo(" << ident << ",int): " << a << endl;
		}
	virtual void foo(const char* ident,bool a)
		{
		cout << "foo(" << ident << ",bool): " << a << endl;
		}
	};
struct Y:public X
	{
	
	};

int main()
	{
	X x;
	const void* s = "text";
	x.foo("name",s);
	}
