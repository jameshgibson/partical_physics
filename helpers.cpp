#include "helpers.h"

int get_bin(double corner, double cube_size, double voxel_size)
{
	const double offset = cube_size / 2.0;
	double bin = (corner + offset) / voxel_size;
	return static_cast<int>(bin + 0.000000001);
}

double get_corner(int bin, double cube_size, double voxel_size)
{
	const double offset = cube_size / 2.0;
	return static_cast<double>(bin) * voxel_size - offset; 
}

