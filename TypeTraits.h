#pragma once
#include "NullAndEmpty.h"
#include "Conversions.h"

template <typename T>
class TypeTraits
{
private:
	template <class U> struct PointerTraits
	{
		enum {result = false};
		typedef NullType PointeeType;
	};
	template <class U> struct PointerTraits<U*>
	{
		enum {result = true};
		typedef U PointeeType;
	};
	template <class U> struct Primitive { enum {result = false}; };
	template <> struct Primitive<bool> { enum { result = true }; };
	template <> struct Primitive<signed char> { enum { result = true }; };
	template <> struct Primitive<unsigned char> { enum { result = true }; };
	template <> struct Primitive<unsigned short> { enum { result = true }; };
	template <> struct Primitive<wchar_t> { enum { result = true }; };
	template <> struct Primitive<signed short> { enum { result = true }; };
	template <> struct Primitive<unsigned int> { enum { result = true }; };
	template <> struct Primitive<signed int> { enum { result = true }; };
	template <> struct Primitive<float> { enum { result = true }; };
	template <> struct Primitive<double> { enum { result = true }; };
	template <> struct Primitive<long int> { enum { result = true }; };
	template <> struct Primitive<long long> { enum { result = true }; };
	template <> struct Primitive<long double> { enum { result = true }; };
	template <> struct Primitive<unsigned long> { enum { result = true }; };

	
	template <class U> struct PToMTraits
	{
		enum { result = false };
	};
	template <class U, class V>
	struct PToMTraits<U V::*>
	{
		enum { result = true };
	};

	template<bool, class T> struct SelectType { typedef T type; };
	template<class T> struct SelectType<true, T> { typedef T& type; };

	template <class U> struct UnConst { typedef U Result; };
	template <class U> struct UnConst <const U> { typedef U Result; };

	template <class U> struct IsConst { enum { Result = false }; };
	template <class U> struct IsConst <const U> { enum { Result = true }; };
public:
	enum { isPointer = PointerTraits<T>::result };
	typedef typename PointerTraits<T>::PointeeType PointeeType;

	enum { isPrimitive = Primitive<T>::result };
	enum { isMemberPointer = PToMTraits<T>::result };

	typedef typename SelectType<!isPrimitive && !isMemberPointer && !isPointer, T>::type ParameterType;
	typedef typename UnConst<T>::Result NonConstType;

	enum {
		isConst = IsConst<T>::Result,
	};
};