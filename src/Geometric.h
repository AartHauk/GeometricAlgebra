#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <iostream>
#include <initializer_list>

namespace Geometric
{
	extern unsigned APPROXIMATION_PERCISION;

	void setPercision (unsigned percision);

	struct G2
	{
		double coefficients[4];
	
		G2(double a = 0, double b = 0, double c = 0, double d = 0): coefficients{a, b, c, d} {}
		G2(const G2 &);
		G2(const std::initializer_list<double> &);
		
		G2& operator=(const G2&);
		double operator[] (unsigned n) const;
	};
	
	std::ostream& operator<< (std::ostream&, G2);

	G2 operator+ (G2 A, G2 B);
	G2& operator+= (G2& A, G2 B);
	G2 operator* (G2 A, G2 B);
	G2 operator* (double c, G2 A);
	G2 operator* (G2 A, double c);
	G2& operator*= (G2& A, G2 B);
	G2 operator/ (G2 A, G2 B);
	G2 operator/ (double c, G2 A);
	G2 operator/ (G2 A, double c);

	G2 dot (G2 A, G2 B);
	G2 inner (G2 A, G2 B);
	G2 outer (G2 A, G2 B);
	G2 norm (G2 A);
	G2 conjugate (G2 A);
	G2 inverse (G2 B);
	
	G2 pow (G2 A, unsigned b);
	G2 exp (G2 X);
	G2 sin (G2 X);
	G2 cos (G2 X);
}

#endif /* GEOMETRIC_H */
