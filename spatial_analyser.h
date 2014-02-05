#pragma once
#include <iostream>
#include <sstream>
#include <limits>

#include "array_3d.h"

#define NO_ANGLE std::numeric_limits<double>::min() 

struct spatial_paramaters 
{
	int region_size;
	int strip_offset;
	int interesting_threshold;
	double avg_multiplier;
        int no_recons;
};

class spatial_analyser
{
public:
	spatial_analyser(double cube_size, double voxel_size, double strip_split);
	void read_file(std::istream &in);
	void run_analysis(std::ostream &out, const spatial_paramaters &parameters);

private:
	double cube_size; 
	double voxel_size;    
	double strip_split;
	int array_size;
	int strip_size;
	spatial_paramaters params;
	array_3d<double> voxels;

	double average_z_region(int start_bin);
	void analyse_regions(int start_bin, double z_avg, std::ostream &out);
	int count_above_avg_voxels(int x, int y, int z, double z_avg, std::stringstream &buff);
};
