#include "particle_analyser.h"
#include "helpers.h"

particle_analyser::particle_analyser(double cube_size, double voxel_size) :
    cube_size(cube_size), voxel_size(voxel_size)
{
    array_size = static_cast<int>(cube_size / voxel_size);
    data.resize(array_size, std::vector<double>());
}

void particle_analyser::read_file(std::istream &in)
{
    int id;
    double x, y, z, angle;

    while(in >> id >> angle >> x >> y >> z)
    {
	int i = get_bin(x, cube_size, voxel_size);
	int j = get_bin(y, cube_size, voxel_size);
	int k = get_bin(z, cube_size, voxel_size);

	if (i < array_size && i >= 0 &&
	    j < array_size && j >= 0 &&
	    k < array_size && k >= 0)
	{
	    data.at(i, j, k).push_back(angle);
	}
    }
}

void particle_analyser::output_voxels(std::ostream &out)
{
    for (int i = 0; i < array_size; ++i)
    {
	for (int j = 0; j < array_size; ++j)
	{
	    for (int k = 0; k < array_size; ++k)
	    {
		std::vector<double> nums = data.at(i, j, k);
		if (nums.size() >= 2)
		{
		    out << get_corner(i, cube_size, voxel_size) << " "
			<< get_corner(j, cube_size, voxel_size) << " " 
			<< get_corner(k, cube_size, voxel_size) << " " 
			<< voxel_size << " " 
			<< average(nums) << std::endl;
		}
	    }
	}	
    }
}
