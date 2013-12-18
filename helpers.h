#pragma once

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
