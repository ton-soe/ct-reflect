#include <iostream>
#include "ct-refl.h"

struct vector
{
	float x, y, z;
};

REFLECT(vector, x, y, z)

template<typename T, size_t N = 0>
void Print(T& value)
{
	constexpr auto name = ctr::FieldName<T, N>();
	auto fieldValue = ctr::FieldPtr<T, N>(value);

	std::cout << name << " = " << *fieldValue << std::endl;

	if constexpr (N < ctr::FieldSize<vector>() - 1)
		Print<T, N + 1>(value);
}


int main(int argc, char** argv)
{
	vector v{ 1, 2, 3 };
	Print(v);
	return 0;
}