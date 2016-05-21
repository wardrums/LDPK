// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.2


#include <ldpk/ldpk_vec2d.h>

using namespace std;
using namespace ldpk;

void extend_bbox_by_spline(const vec2d& qa,const vec2d& qb,const vec2d& dqa,const vec2d& dqb,box2d& box)
	{
	vec2d a = qa;
	vec2d b = dqa;
	vec2d c = -3.0 * qa + 3.0 * qb - 2.0 * dqa - dqb;
	vec2d d =  2.0 * qa - 2.0 * qb +       dqa + dqb;
	vec2d disc;

	for(int i = 0;i <= 10;++i)
		{
		double t = double(i) / 10;
		cout << i << ": " << (a + b * t + c * t * t + d * t * t * t) << endl;
		}
	for(int i = 0;i < 2;++i)
		{
		if(d[i] != 0.0)
			{
			disc[i] = (c[i] * c[i]) / (9.0 * d[i] * d[i]) - b[i] / (3.0 * d[i]);
// equal 0 means saddle point, i.e. not an extreme value,
// less than 0 means no extremum at all.
			if(disc[i] > 0.0)
				{
				double t,r = sqrt(disc[i]);
				t = -c[i] / (3.0 * d[i]) + r;
				if((t > 0.0) && (t < 1.0))
					{ box.extend(i,a[i] + t * (b[i] + t * (c[i] + t * d[i]))); }
				t = -c[i] / (3.0 * d[i]) - r;
				if((t > 0.0) && (t < 1.0))
					{ box.extend(i,a[i] + t * (b[i] + t * (c[i] + t * d[i]))); }
				}
			}
		else
			{
			if(c[i] != 0.0)
				{
				double t = b[i] / (-2.0 * c[i]);
				if((t > 0.0) && (t < 1.0))
					{ box.extend(i,a[i] + t * (b[i] + t * (c[i] + t * d[i]))); }
				}
			}
		}
	}

int main()
	{
	vec2d qa(0,0),qb(10,0);
	vec2d dqa(1,-2),dqb(1,-1);
	box2d box;
	box.extend(qa);
	box.extend(qb);
	extend_bbox_by_spline(qa,qb,dqa,dqb,box);
	cout << box.a() << endl;
	cout << box.b() << endl;
	}
