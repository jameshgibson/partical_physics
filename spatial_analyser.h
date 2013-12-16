#pragma once
#include <iostream>
#include <sstream>
#include <limits>

#include "array_3d.h"

#define NO_ANGLE std::numeric_limits<double>::min() 

class spatial_analyser
{
public:
    spatial_analyser(double cube_size, double voxel_size, double strip_split);
    void read_file(std::istream &in);
    void run_analysis(std::ostream &out, int region_size, int interesting_threshold);

private:
    double cube_size; 
    double voxel_size;    
    double strip_split;
    int array_size;
    int strip_size;
    array_3d<double> voxels;

    double average_z_region(int start_bin);
    void analyse_regions(int start_bin, double z_avg, int region_size, int interesting_threshold, std::ostream &out);
    int count_above_avg_voxels(int region_size, int x, int y, int z, double z_avg, std::stringstream &buff);
};
