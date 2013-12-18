#pragma once

#include "array_3d.h"

template<class value>
array_3d<value>::array_3d() : dimensions(3)
{
}

template<class value>
array_3d<value>::array_3d(int size, value default_value) : dimensions(3)
{
	resize(size, size, size, default_value);
}

template<class value>
array_3d<value>::array_3d(int x_size, int y_size, int z_size, value default_value) : dimensions(3)
{
	resize(x_size, y_size, z_size, default_value);
}

template<class value>
void array_3d<value>::resize(int size, value default_value)
{
	resize(size, size, size, default_value);
}

template<class value>
void array_3d<value>::resize(int x_size, int y_size, int z_size, value default_value)
{
	my_array.resize(x_size);
	for (int i = 0; i < x_size; ++i)
	{
		my_array[i].resize(y_size);
		for (int j = 0; j < y_size; ++j)
		{
			my_array[i][j].resize(z_size, default_value);
		}
	}
}

template<class value>
value & array_3d<value>::at(int x, int y, int z)
{
	return my_array[x][y][z];
}