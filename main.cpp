#include <fstream>
#include <sstream>
#include <cmath>
#include <list>
#include <set>

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

    std::ifstream infile("Total_PoCA_Perfect_Cargo_Only_Lower_Plane.txt");
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

	for (int threshold = 31; threshold <= 31; ++threshold)
	{
	    for (double mult = 1; mult <= 1; mult += 0.1)
	    {
		std::stringstream results;
		spatial_paramaters params;
		params.avg_multiplier = mult;
		params.interesting_threshold = threshold;
		params.region_size = region_size;
		params.strip_offset = 2;
		params.no_recons = min_found;

		sa.run_analysis(results, params);
		analyse_results(results, params);
	    }
	}
    }

    //system("pause");

    return 0;
}

std::list<point_3d>::iterator find_point(std::list<point_3d> &points, double x, double y, double z)
{
    for (std::list<point_3d>::iterator it = points.begin(); it != points.end(); ++it)
    {
	if (within_range(x, it->x) &&
	    within_range(y, it->y) &&
	    within_range(z, it->z))
	{
	    return it;
	}
    }             
    return points.end();
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
    points.push_back(point_3d(-2.2, -0.65, -0.7));
    points.push_back(point_3d(-0.1, -0.65, -0.7));
    points.push_back(point_3d(2.0, 0.45, -0.7));
    // points.push_back(point_3d(-2.2, 0.45, 0.4));
    //    points.push_back(point_3d(2, -0.1, 0.4));

    // Run 2 / Run 7
    //points.push_back(point_3d(0, 0.65, -0.4));
    //points.push_back(point_3d(-0.1, -0.65, -0.4));
    //points.push_back(point_3d(2, -0.65, -0.4));
    //      points.push_back(point_3d(-2.2, -0.65, 0.05));
    //points.push_back(point_3d(2.05, -0.35, 0.05));


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
    std::list<point_3d> points;
    std::set<point_3d> errors;
    std::set<point_3d> good_points;
    get_expected_points(points);
    double z_pos, z_avg, region_x, region_y, region_z, voxel_x, voxel_y, voxel_z, angle;
    int count;
	
    while (results >> z_pos >> z_avg >> region_x >> region_y >> region_z >> voxel_x >> voxel_y >> voxel_z >> angle >> count)
    {
	std::list<point_3d>::iterator p = find_point(points, region_x, region_y, region_z);
	if (p != points.end())
	{
	    std::pair<std::set<point_3d>::iterator, bool> ret;
	    ret = good_points.insert(*p);
	    if (ret.second)
	    {
		std::cout << "found point: " << voxel_x << ", " << voxel_y
			  << ", " << voxel_z << std::endl;
	    }
	}
	else
	{
	    std::pair<std::set<point_3d>::iterator, bool> ret;
	    ret = errors.insert(point_3d (voxel_x, voxel_y, voxel_z));
	    if (ret.second)
	    {
		std::cout << "unexpected point: " << voxel_x << ", "
			  << voxel_y << ", " << voxel_z << std::endl;
	    }
	}
		
    }
	
    if (points.size() == good_points.size())
    {
	std::cout << "found all the points with the following parameters" << std::endl;
	std::cout << params.no_recons << " " << params.interesting_threshold << " "
		  << params.avg_multiplier << " " << errors.size() <<std::endl;
    }
}
