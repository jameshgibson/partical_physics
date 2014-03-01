#pragma once
#include <cmath>

int get_bin(double corner, double cube_size, double voxel_size);

double get_corner(int bin, double cube_size, double voxel_size);

template<class numeric>
typename numeric::value_type average(numeric numbers)
{
	typename numeric::value_type average = 0;
	typename numeric::iterator it;
	for(it = numbers.begin(); it != numbers.end(); ++it)
	{
		average += *it;
	}
	return (average / numbers.size());
}

template <class floating>
bool almost_equals(floating lhs, floating rhs, double epsilon = 0.0000001)
{
    return std::fabs(lhs - rhs) < epsilon;
}

bool within_range(double lhs, double rhs);
