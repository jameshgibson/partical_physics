#pragma once
#include <vector>

template<class value>
class array_3d
{
	typedef std::vector<value> array_t;
	typedef std::vector<array_t> array_2d_t;
	typedef std::vector<array_2d_t > array_3d_t;
public:
	array_3d();
	array_3d(int size, value default_value);
	array_3d(int x_size, int y_size, int z_size, value default_value);

	void resize(int size, value default_value);
	void resize(int x_size, int y_size, int z_size, value default_value);
	value & at(int x, int y, int z);

	value * begin() { return &my_array[0][0]; };
	value * end() { return begin() + dimensions * my_array.size(); }
private:
	array_3d_t my_array;
	const int dimensions;
};

#include "array_3d-inl.h"