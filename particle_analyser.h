#pragma once
#include <iostream>

#include "array_3d.h"

class particle_analyser
{
public:
	particle_analyser(double cube_size, double voxel_size);
	void read_file(std::istream &in);
	void output_voxels(std::ostream &out, unsigned int min_found);

private:
	typedef array_3d<std::vector<double> > data_t;

	double cube_size; 
	double voxel_size; 
	int array_size;
	data_t data;
	
	int get_array_size() const { return static_cast<int>(cube_size / voxel_size); }
};
