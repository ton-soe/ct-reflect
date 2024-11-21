#include <iostream>
#include "ct-refl.h"

struct vector
{
	float x, y, z;
};

REFLECT(vector, x, y, z)

template<typename T, size_t N = 0>
void Print(const T& value)
{
	auto fields = ctr::Reflect<T>::Fields();
	auto field = std::get<N>(fields);
	std::cout << field.name << " = " << value.*field.ptr << std::endl;
	if constexpr (N < std::tuple_size_v<decltype(fields)> -1)
		Print<T, N + 1>(value);
}

int main(int argc, char** argv)
{
	vector v{ 1, 2, 3 };
	Print(v);
	return 0;
}