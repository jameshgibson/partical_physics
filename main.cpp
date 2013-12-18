#include <fstream>
#include <sstream>

#include "particle_analyser.h"
#include "spatial_analyser.h"

int main()
{
    const double cube_size = 10.0;
    const double voxel_size = 0.05;

    std::ifstream infile("test.txt");
    std::stringstream buffer;

    particle_analyser pa(cube_size, voxel_size);
	
    pa.read_file(infile);
    pa.output_voxels(buffer);

    const double z_split_width = 0.2;

    spatial_analyser sa(cube_size, voxel_size, z_split_width);
    sa.read_file(buffer);

    // search: 4x4x4 voxel regions
    const int region_size = 4; 
    // only report region if more than this number of voxels are greater than the average
    const int interesting_threshold = 20; 
	
    sa.run_analysis(std::cout, region_size, interesting_threshold);

    return 0;
}
