#pragma once
#include <tuple>
#include "ct-string.h"
#include "map-macro.h"

namespace ctr
{
	template<class TStruct, typename TField, size_t TElem, CTString TFieldName, TField TStruct::* TPtr>
	struct FieldInfo
	{
		using FieldType = TField;
		using StructType = TStruct;

		constexpr static size_t fieldIndex = TElem;
		constexpr static char const* const name = &TFieldName.value[0];
		constexpr static TField TStruct::* const ptr = TPtr;
	};

	template<class T>
	struct Reflect
	{
		using _enabled = std::false_type;
	};

	template<typename TValue>
	concept Reflectable = std::is_same_v<typename Reflect<TValue>::_enabled, std::true_type>;

	template<Reflectable T>
	constexpr size_t FieldCount()
	{
		return Reflect<T>::FieldSize;
	}

	template<Reflectable T, size_t Index>
	constexpr size_t SizeOfField()
	{
		return sizeof(std::remove_pointer_t<decltype(std::tuple_element_t<Index, typename Reflect<T>::Fields>::ptr)>);
	}

	template<Reflectable T, size_t Index>
	constexpr char const* const FieldName()
	{
		return std::tuple_element_t<Index, typename Reflect<T>::Fields>::name;
	}

	template<Reflectable T, size_t Index>
	auto FieldPtr(T& value)
	{
		return &(value.*std::tuple_element_t<Index, typename Reflect<T>::Fields>::ptr);
	}

	template<Reflectable T, size_t Index>
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
		using _enabled = std::true_type;\
		using Type = Class;\
		\
		constexpr static size_t beg = __COUNTER__ + 1;\
		using Fields = std::tuple<MAP_LIST(FIELD_INFO, __VA_ARGS__)>;\
		constexpr static size_t FieldSize = CURRENT_ELEM(beg);\
		\
	};\
}