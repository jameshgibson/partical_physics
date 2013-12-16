#include <fstream>
#include <sstream>

#include "particle_analyser.h"
#include "spatial_analyser.h"

int main()
{
    const double cube_size = 10.0;
    const double voxel_size = 0.05;

    particle_analyser *pa = new particle_analyser(cube_size, voxel_size);
    std::ifstream infile("test.txt");
    std::stringstream buff;

    pa->read_file(infile);
    pa->output_voxels(buff);

    spatial_analyser *sa = new spatial_analyser(cube_size, voxel_size, 0.2);
    sa->read_file(buff);
    sa->run_analysis(std::cout, 4, 20);

    delete pa;
    delete sa;

    return 0;
}
