#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <math.h>

#include "Geometric.h"

namespace Geometric
{
unsigned factorial (unsigned i);

unsigned APPROXIMATION_PERCISION = 10;

void setPercision (unsigned percision)
{
	APPROXIMATION_PERCISION = percision;
}

G2::G2(const G2 &G)
{
	coefficients[0] = G.coefficients[0];
	coefficients[1] = G.coefficients[1];
	coefficients[2] = G.coefficients[2];
	coefficients[3] = G.coefficients[3];
}

G2::G2(const std::initializer_list<double> &G)
{
	unsigned i = 0;
	for (; i < 4 && i < G.size(); i++)
	{
		coefficients[i] = *(G.begin() + i);
	}
	for (; i < 4; i++)
	{
		coefficients[i] = 0;
	}
}

G2& G2::operator= (const G2 &G)
{
	for (unsigned i = 0; i < 4; i ++)
	{
		coefficients[i] = G[i];
	}
	return *this;
}

double G2::operator[] (unsigned n) const
{
	if (n < 4)
	{
		return coefficients[n];
	} else {
		std::cerr << "Cannot access coefficient[" << n << "] of a geomatric in G2" << std::endl;
		throw std::invalid_argument("");
	}
}

std::ostream& operator<< (std::ostream &os, G2 G)
{
	return os << "(" << G[0] << " + " << G[1] << " e1 + " << G[2] << " e2 + " << G[3] << " e12)";
}

G2 operator+ (G2 A, G2 B)
{
	return G2(
		A[0] + B[0],
		A[1] + B[1],
		A[2] + B[2],
		A[3] + B[3]
	);
}

G2& operator+= (G2& A, G2 B)
{
	return A = A + B;
}

G2 operator* (double c, G2 A)
{
	return G2(
		A[0] * c,
		A[1] * c,
		A[2] * c,
		A[3] * c
	);
}

G2 operator* (G2 A, double c)
{
	return c * A;
}

G2 operator* (G2 A, G2 B)
{
	return G2(
		A[0] * B[0] + A[1] * B[1] + A[2] * B[2] - A[3] * B[3],
		A[0] * B[1] + A[1] * B[0] - A[2] * B[3] + A[3] * B[2],
		A[0] * B[2] + A[1] * B[3] + A[2] * B[0] - A[3] * B[1],
		A[0] * B[3] + A[1] * B[2] - A[2] * B[1] + A[3] * B[0]
	);
}

G2 inverse (G2 A)
{
	return conjugate(A) / (A[0] * A[0] - A[1] * A[1] - A[2] * A[2] + A[3] * A[3]);
}

G2 operator/ (G2 A, G2 B)
{
	return A * inverse(B);
}

G2 operator/ (double c, G2 A)
{
	return c * inverse(A);
}

G2 operator/ (G2 A, double c)
{
	if (!c)
	{
		std::cerr << "Cannot divide by zero." << std::endl;
		throw std::domain_error("");
	}
	return G2(A[0] / c, A[1] / c, A[2] / c, A[3] / c);
}

G2& operator*= (G2& A, G2 B)
{
	return A = A * B;
}

G2 dot (G2 A, G2 B)
{	
	return G2(
		A[0] * B[0] + A[1] * B[1] + A[2] * B[2] - A[3] * B[3],
		A[0] * B[1] + A[1] * B[0],
		A[0] * B[2] + A[2] * B[0],
		A[0] * B[3] + A[3] * B[0]
	);	
}

G2 inner (G2 A, G2 B)
{
	return dot(A, B);
}

G2 outer (G2 A, G2 B)
{
	return G2(
		0,
		A[3] * B[2] - A[2] * B[3],
		A[1] * B[3] - A[3] * B[1],
		A[1] * B[2] - A[2] * B[1]
	);
}

G2 norm (G2 A)
{
	return G2(
		A[0] * A[0] + A[1] * A[1] + A[2] * A[2] - A[3] * A[3],
		2 * A[0] * A[1],
		2 * A[0] * A[2],
		2 * A[0] * A[3]
	);
}

G2 conjugate (G2 A)
{
	return G2(A[0], -A[1], -A[2], -A[3]);
}

G2 pow (G2 A, unsigned b)
{
	if (!b) return G2(1);
	else if (b == 1) return A;
	return A * pow(A, b - 1);
}

G2 exp (G2 X)
{
	G2 out;
	for (unsigned n = 0; n <= APPROXIMATION_PERCISION; n++)
	{
		out += pow(X, n) / factorial(n);
	}
	return out;
}

G2 sin (G2 X)
{
	G2 out;
	for (unsigned n = 0; n < APPROXIMATION_PERCISION; n++)
	{
		out += (std::pow(-1, n) / factorial(2 * n + 1)) * pow(X, 2 * n + 1);
	}
	return out;
}

G2 cos (G2 X)
{
	G2 out;
	for (unsigned n = 0; n < APPROXIMATION_PERCISION; n++)
	{
		out += (std::pow(-1, n) / factorial(2 * n)) * pow(X, 2 * n);
	}
	return out;
}

// TODO move to a better location than the G2 implementation
unsigned factorial (unsigned i)
{
	if (i == 0 || i == 1) return 1;
	return i * factorial(i - 1);
}

}
