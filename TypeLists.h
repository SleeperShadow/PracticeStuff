//
// Created by Licht on 2019-03-13.
//

#ifndef PRACTICESTUFF_TYPELISTS_H
#define PRACTICESTUFF_TYPELISTS_H

#include ""
#include "NullAndEmpty.h"

template <class T, class U>
struct TypeList
{
	typedef T head;
	typedef U tail;
};

template <class T>
struct TypeList<T, NullType>
{
	typedef T head;
	typedef NullType tail;
};


#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>

#define TYPELIST_5(...) ...

namespace TL
{

	typedef TYPELIST_3(char, signed char, unsigned char) charList;
	typedef TYPELIST_4(signed char, short int, int, long int) signedIntegrals;

	template <class TList> struct length;
	template <> struct length<NullType>
	{
		enum {value = 0};
	};
	template <class T, class U> struct length<TypeList<T, U>>
	{
		enum {value = 1 + length<U>::value};
	};

	template <class TList, unsigned int index> struct TypeAt;

	template <class Head, class Tail> struct TypeAt<TypeList<Head, Tail>, 0>
	{
		typedef Head result;
	};

	template <class Head, class Tail, unsigned int index>
	struct TypeAt<TypeList<Head,Tail>, index>
	{
		typedef typename TypeAt<Tail, index - 1>::result result;
	};

	template<class TList, class T> struct IndexOf;

	template<class T> struct IndexOf<NullType, T>
	{
		enum { value = -1 };
	};

	template <class T, class Tail> struct IndexOf<TypeList<T, Tail>, T>
	{
		enum { value = 0 };
	};

	template <class Head, class Tail, class T> struct IndexOf<TypeList<Head, Tail>, T>
	{
	private:
		enum { temp = IndexOf<Tail, T>::value};
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };
	};

	template <class TList, class T> struct Append;

	template <> struct Append<NullType, NullType>
	{
		typedef NullType result;
	};
	template <class T> struct Append<NullType, T>
	{
		typedef TYPELIST_1(T) result;
	};

	template <class Head, class Tail> struct Append<NullType, TypeList<Head, Tail>>
	{
		typedef TypeList<Head, Tail> result;
	};

	template <class Head, class Tail, class T> struct Append<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head, typename Append<Tail, T>::result> result;
	};

	typedef Append<signedIntegrals, TYPELIST_3(float, double, long double)>::result signedTypes;
}


#endif //PRACTICESTUFF_TYPELISTS_H
