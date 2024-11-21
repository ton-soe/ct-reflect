#pragma once
#include <tuple>
#include "map-macro.h"

namespace ctr
{
	template<typename TStruct, typename TField>
	struct FieldInfo
	{
		using FieldType = TField;
		using StructType = TStruct;

		const char* name;
		TField TStruct::* const ptr;

		FieldInfo(const char* name, TField TStruct::* ptr) :
			name(name),
			ptr(ptr)
		{}
	};

	template<typename T>
	struct Reflect
	{
		static_assert(false, "Reflect not defined for type T");
	};
}

#define FIELD_REFLECT(Field) FieldInfo<Type, decltype(Type::Field)>(#Field, &Type::Field)

#define REFLECT(Class, ...)							\
namespace ctr										\
{													\
	template<>										\
	struct Reflect<Class>							\
	{												\
		using Type = Class;							\
		static auto Fields()						\
		{											\
			return std::make_tuple(					\
			MAP_LIST(FIELD_REFLECT, __VA_ARGS__)	\
		);											\
		}											\
	};												\
}