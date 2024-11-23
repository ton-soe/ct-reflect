#pragma once
#include <tuple>
#include "ct-string.h"
#include "map-macro.h"

namespace ctr
{
	template<typename TStruct, typename TField, size_t TElem, CTString TFieldName, TField TStruct::* TPtr>
	struct FieldInfo
	{
		using FieldType = TField;
		using StructType = TStruct;

		constexpr static size_t fieldIndex = TElem;
		constexpr static char const* const name = &TFieldName.value[0];
		constexpr static TField TStruct::* const ptr = TPtr;
	};

	template<typename T>
	struct Reflect
	{
		static_assert(false, "Reflect not defined for type T");
	};

	template<typename T>
	constexpr size_t FieldCount()
	{
		return Reflect<T>::FieldSize;
	}

	template<typename T, size_t Index>
	constexpr size_t SizeOfField()
	{
		return sizeof(std::remove_pointer_t<decltype(std::tuple_element_t<Index, typename Reflect<T>::Fields>::ptr)>);
	}

	template<typename T, size_t Index>
	constexpr char const* const FieldName()
	{
		return std::tuple_element_t<Index, typename Reflect<T>::Fields>::name;
	}

	template<typename T, size_t Index>
	auto FieldPtr(T& value)
	{
		return &(value.*std::tuple_element_t<Index, typename Reflect<T>::Fields>::ptr);
	}

	template<typename T, size_t Index>
	auto FieldPtr(const T& value)
	{
		return &(value.*std::tuple_element_t<Index, typename Reflect<T>::Fields>::ptr);
	}
}

#define CURRENT_ELEM(Current) __COUNTER__ - Current
#define FIELD_INFO(Field) FieldInfo<Type, decltype(Type::Field), CURRENT_ELEM(beg), #Field, &Type::Field>
#define FIELD_TYPE(Field) decltype(Type::Field)

#define REFLECT(Class, ...)\
namespace ctr\
{\
	template<>\
	struct Reflect<Class>\
	{\
		using Type = Class;\
		\
		constexpr static size_t beg = __COUNTER__ + 1;\
		using Fields = std::tuple<MAP_LIST(FIELD_INFO, __VA_ARGS__)>;\
		constexpr static size_t FieldSize = CURRENT_ELEM(beg);\
		\
	};\
}