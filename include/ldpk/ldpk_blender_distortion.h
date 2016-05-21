// This file is part of the Lens Distortion Plugin Kit
// Software is provided "as is" - no warranties implied.
// (C) 2011,2012,2013,2014,2015,2016 - Science-D-Visions. Current version: 1.9.1


#ifndef ldpk_blender_distortion_sdv
#define ldpk_blender_distortion_sdv

//! @file ldpk_blender_distortion.h
//! @brief Degree-2 anamorphic and degree-4 radial mixed model.

#include <ldpk/ldpk_generic_distortion_base.h>

namespace ldpk
	{
//! @brief Degree-2 anamorphic and degree-4 radial mixed model.
	template <class VEC2,class MAT2>
	class blender_distortion:public ldpk::generic_distortion_base<VEC2,MAT2,5>
		{
	private:
		typedef VEC2 vec2_type;
		typedef MAT2 mat2_type;

		union
			{
			struct
				{
				double k1,k2,k3,p1,p2;
				};
			double _c[5];
			};
		mutable double _cxx,_cxy,_cyx,_cyy,_cxxx,_cxxy,_cxyy,_cyxx,_cyyx,_cyyy;
		mutable bool _uptodate;

		void update() const
			{
			
			_uptodate = true;
			}
	public:
		blender_distortion():k1(0),k2(0),k3(0),p1(0),p2(0),_uptodate(false)
			{ }
//! Get coefficient as demanded by base class
		double get_coeff(int i) const
			{ return _c[i]; }
//! Set coefficient as demanded by base class
		void set_coeff(int i,double q)
			{ _c[i] = q;_uptodate = false; }

//! Remove distortion. p is a point in diagonally normalized coordinates.
		vec2_type operator()(const vec2_type& p) const
			{
			if(!_uptodate) update();
			
            double x = p[0];
            double y = p[1];

  // Apply distortion to the normalized points to get (xd, yd).
            double r2 = x*x + y*y;
            double r4 = r2 * r2;
            double r6 = r4 * r2;
            double r_coeff = (1 + k1*r2 + k2*r4 + k3*r6);
            double xd = x * r_coeff + 2*p1*x*y + p2*(r2 + 2*x*x);
            double yd = y * r_coeff + 2*p2*x*y + p1*(r2 + 2*y*y);

			vec2_type q;
			q[0] = xd;
			q[1] = yd;
			return q;
			}
// @brief Analytic version of the Jacobi-matrix
		mat2_type jacobi(const vec2_type& p_dn) const
			{
			if(!_uptodate) update();
			double x = p_dn[0],x2 = x * x,x3 = x2 * x,x4 = x2 * x2;
			double y = p_dn[1],y2 = y * y,y3 = y2 * y,y4 = y2 * y2;
			mat2_type m;
			m[0][0] = 1.0 + x2 * 3.0 * _cxx + y2 * _cxy
				+ x4 * 5.0 * _cxxx + x2 * y2 * 3.0 * _cxxy + y4 * _cxyy;
			m[1][1] = 1.0 + x2 * _cyx + y2 * 3.0 * _cyy
				+ x4 * _cyxx + x2 * y2 * 3.0 * _cyyx + y4 * 5.0 * _cyyy;
			m[0][1] = x * y * 2.0 * _cxy + x3 * y * 2.0 * _cxxy + x * y3 * 4.0 * _cxyy;
			m[1][0] = x * y * 2.0 * _cyx + x3 * y * 4.0 * _cyxx + x * y3 * 2.0 * _cyyx;
			return m;
			}
		std::ostream& out(std::ostream& cout) const
			{
			int p = int(cout.precision());
			cout.precision(5);
			cout << "       Poly1: " << std::right << std::fixed << k1 << "\n";
			cout << "       Poly2: " << std::right << std::fixed << k2 << "\n";
			cout << "       Poly3: " << std::right << std::fixed << k3 << "\n";
			cout << "       part1: " << std::right << std::fixed << p1 << "\n";
			cout << "       part2: " << std::right << std::fixed << p2 << "\n";			
			cout.precision(p);
			return cout;
			}
		};
	}

#endif
