#include "spatial_analyser.h"
#include "helpers.h"

spatial_analyser::spatial_analyser(double cube_size, double voxel_size, double strip_split) :
    cube_size(cube_size), voxel_size(voxel_size), strip_split(strip_split)
{
    array_size = static_cast<int>(cube_size / voxel_size);
    strip_size = static_cast<int>(strip_split / voxel_size);
    voxels.resize(array_size, NO_ANGLE);
}

void spatial_analyser::read_file(std::istream &in)
{
    double x,y,z,size,angle;
    while(in >> x >> y >> z >> size >> angle)
    {
	int i = get_bin(x, cube_size, voxel_size);
	int j = get_bin(y, cube_size, voxel_size);
	int k = get_bin(z, cube_size, voxel_size);
		
	if (i < array_size && i >= 0 &&
	    j < array_size && j >= 0 &&
	    k < array_size && k >= 0)
	{
	    voxels.at(i, j, k) = angle;
	}
    }
}

double spatial_analyser::average_z_region(int start_bin)
{
    double sum = 0;
    int count = 0;
    for (int i = 0; i < array_size; ++i)
    {
	for (int j = 0; j < array_size; ++j)
	{
	    for (int k = start_bin; k < (start_bin + strip_size) && k < array_size; ++k)
	    {
		double angle = voxels.at(i, j ,k);
		if (angle != NO_ANGLE)
		{
		    sum += angle;
		    ++count;
		}
	    }
	}
    }

    if (count == 0)
	return NO_ANGLE;

    return sum / count;
}

int spatial_analyser::count_above_avg_voxels(int x, int y, int z, double z_avg, std::stringstream &buff)
{
    int count = 0;
    for (int i = x; i < x + params.region_size; ++i)
    {
	for ( int j = y; j < y + params.region_size; ++j)
	{
	    for ( int k = z; k < z + params.region_size; ++k)
	    {
		double angle = voxels.at(i, j, k);
		if (angle > (z_avg * params.avg_multiplier))
		{
		    buff << get_corner(i, cube_size, voxel_size) << " " 
			 << get_corner(j, cube_size, voxel_size) << " " 
			 << get_corner(k, cube_size, voxel_size) << " " 
			 << angle << std::endl;
		    ++count;
		}
	    }
	}
    }
    return count;
}

void spatial_analyser::analyse_regions(int start_bin, double z_avg, std::ostream &out)
{
    for (int i = 0; i <= array_size - params.region_size; ++i)
    {
	for (int j = 0; j <= array_size - params.region_size; ++j)
	{
	    for (int k = start_bin; k <= (start_bin + strip_size - params.region_size); ++k)
	    {
		std::stringstream buffer;
		int count = count_above_avg_voxels(i, j, k, z_avg, buffer);
		if (count >= params.interesting_threshold)
		{
		    /*out << get_corner(start_bin, cube_size, voxel_size) << " " 
		      << z_avg << " " 
		      << get_corner(i, cube_size, voxel_size) << " " 
		      << get_corner(j, cube_size, voxel_size) << " " 
		      << get_corner(k, cube_size, voxel_size) << std::endl;*/
		    std::string line;
		    while (std::getline(buffer, line))
		    {
			out << get_corner(start_bin, cube_size, voxel_size) << " " 
			    << z_avg << " " 
			    << get_corner(i, cube_size, voxel_size) << " " 
			    << get_corner(j, cube_size, voxel_size) << " " 
			    << get_corner(k, cube_size, voxel_size) << " ";
			out << line << " " << count << std::endl;
		    }
		}
	    }
	}
    }
}

void spatial_analyser::run_analysis(std::ostream &out, const spatial_paramaters &parameters)
{
    params = parameters;
    for (int z = params.strip_offset; z <= (array_size - strip_size); z += strip_size)
    {
	double z_avg = average_z_region(z);
	if (z_avg != NO_ANGLE)
	{
	    analyse_regions(z, z_avg, out);
	}
    }
}

