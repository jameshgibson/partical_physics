#pragma once
#include "helpers.h"

struct point_3d
{
    double x, y, z;
    point_3d(double x, double y, double z) : x(x), y(y), z(z)
	{
	}

    bool operator<(const point_3d &p) const { 
	if (this->x < p.x)
	    return true;
	if (this->y < p.y)
	    return true;
	if (this->z < p.z)
	    return true;
	return false;
    }
};
