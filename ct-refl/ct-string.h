#pragma once
#include <algorithm>

namespace ctr
{
	template<size_t N>
	struct CTString
	{
		constexpr CTString(const char(&str)[N])
		{
			std::copy_n(str, N, value);
		}

		char value[N];
	};
}