#ifndef CLIFFORD_H
#define CLIFFORD_H

#include <iostream>
#include <cstddef>

namespace Geometric
{
	class G2;
	
	std::ostream& operator<< (std::ostream &ost, G2 &geometric);
	
	class G2
	{
	private:
		double scalar, e1, e2, pseudoScalar;
	public:
		G2 (double s = 0, double x = 0, double y = 0, double ps = 0): scalar(s), e1(x), e2(y), pseudoScalar(ps) {}
		
		G2 (const G2 &geometric);
		~G2 ();
	
		friend std::ostream& operator<< (std::ostream &ost, G2 &geometric);

		G2 operator+ (const G2 &geometric) const;
		G2& operator+= (const G2 &geometric);
		G2 operator* (const G2 &geometric) const;
		G2 operator* (double s) const;
		G2& operator*= (const G2 &geometric);
		G2& operator*= (double s);

		double operator[](std::size_t n) const;
		//G2
	};
};
#endif /* CLIFFORD_H  */
