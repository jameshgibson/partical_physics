#include <fstream>
#include <sstream>
#include <cmath>
#include <list>

#include "particle_analyser.h"
#include "spatial_analyser.h"
#include "helpers.h"
#include "point_3d.h"

void analyse_results(std::istream &results, const spatial_paramaters &params);

int main()
{
    const double cube_size = 10.0;
    const double voxel_size = 0.05;
    const int region_size = 4;

    std::ifstream infile("Total_PoCA_1mm_Cargo_Only_Upper_Plane.txt");
    std::stringstream buffer;

    particle_analyser pa(cube_size, voxel_size);

    pa.read_file(infile);
    pa.output_voxels(buffer, 2);

    const double z_split_width = 0.2;

    spatial_analyser sa(cube_size, voxel_size, z_split_width);
    sa.read_file(buffer);

    for (int min_found = 3; min_found <= 3; ++min_found)
    {
	std::stringstream buffer;
	pa.output_voxels(buffer, min_found);

	spatial_analyser sa(cube_size, voxel_size, z_split_width);
	sa.read_file(buffer);

	for (int threshold = 5; threshold <= 5; ++threshold)
	{
	    for (double mult = 1; mult <= 1; mult += 0.1)
	    {
		std::stringstream results;
		spatial_paramaters params;
		params.avg_multiplier = mult;
		params.interesting_threshold = threshold;
		params.region_size = region_size;
		params.strip_offset = 1;
		params.no_recons = min_found;

		sa.run_analysis(std::cout, params);
		analyse_results(results, params);
	    }
	}
    }

    //system("pause");

    return 0;
}

bool find_and_remove_point(std::list<point_3d> &points, double x, double y, double z)
{
    for (std::list<point_3d>::iterator it = points.begin(); it != points.end(); ++it)
    {
	if (almost_equals(x, it->x) && 
	    almost_equals(y, it->y) &&
	    almost_equals(z, it->z))
	{
	    points.erase(it);
	    return true;
	}
    }	
    return false;
}

void get_expected_points(std::list<point_3d> &points)
{
    // alternatively read these from a file to avoid having 
    // to recompile.
    // expected format is just x y z seperated by spaces on each line.
    /*
      std::ifstream filestream("expected_points.txt");
      double x, y, z;
      while (filestream >> x >> y >> z)
      {
      points.push_back(point_3d(x, y, z));
      }
    */
    // or just add them here like below
    // Run 1 / Run 6
    //points.push_back(point_3d(-2.2, -0.65, -0.7));
    //     points.push_back(point_3d(-0.1, -0.65, -0.7));
    //	points.push_back(point_3d(2.0, 0.45, -0.7));
    // points.push_back(point_3d(-2.2, 0.45, 0.4));
    //    points.push_back(point_3d(2, -0.1, 0.4));

    // Run 2 / Run 7
    //points.push_back(point_3d(0, 0.65, -0.4));
    //points.push_back(point_3d(-0.1, -0.65, -0.4));
    //points.push_back(point_3d(2, -0.65, -0.4));
    points.push_back(point_3d(-2.2, -0.65, 0.05));
    points.push_back(point_3d(2.05, -0.35, 0.05));


    // Run 3 / Run 8
    //points.push_back(point_3d(-1.45, 0.65, -1.1));
    //points.push_back(point_3d(-2.2, -0.65, 0.05));
    //points.push_back(point_3d(2, 0.65, 0.05));
    //points.push_back(point_3d(-0.1, -0.65, -0.7));
    //points.push_back(point_3d(2, 0.45, -0.7));

    // Empty with threats
    //points.push_back(point_3d(-0.1, -0.1, -1.25));
    //points.push_back(point_3d(1.65, 0.4, -1.25));
    //points.push_back(point_3d(-1.85, -0.6, -1.25));
    //points.push_back(point_3d(1.65, -0.6, -1.25));
    //points.push_back(point_3d(-1.85, 0.4, -1.25));


}

void analyse_results(std::istream &results, const spatial_paramaters &params)
{
    double z_pos, z_avg, region_x, region_y, region_z, voxel_x, voxel_y, voxel_z, angle;
    int count=0;

    std::list<point_3d> points;
    get_expected_points(points);

    while (results >> z_pos >> z_avg >> region_x >> region_y >> region_z)// >> 
	//voxel_x >> voxel_y >> voxel_z >> angle >> count)
    {
	if (find_and_remove_point(points, region_x, region_y, region_z))
	{
	    //std::cout << "found point: " << region_x << ", " << region_y 
	    //		<< ", " << region_z << std::endl;
	}
	else
	{
	    count++;
	    //std::cout << "unexpected point: " << region_x << ", "
	    //	<< region_y << ", " << region_z << std::endl;
	}
	    
    }

    if (points.empty())
    {
	//std::cout << "found all the points with the following parameters" << std::endl;
	std::cout << params.no_recons << " " << params.interesting_threshold << " "
		  << params.avg_multiplier << " " << count <<std::endl;
    }
}
