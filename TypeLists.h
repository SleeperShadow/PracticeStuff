//
// Created by Licht on 2019-03-13.
//

#ifndef PRACTICESTUFF_TYPELISTS_H
#define PRACTICESTUFF_TYPELISTS_H

#include "NullAndEmpty.h"
#include "NiftyContainer.h"

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


	template<typename TList, typename Type>struct EraseType;
	template<typename Type> struct EraseType<NullType, Type>
	{
		typedef NullType result;
	};

	template<typename Head, typename Tail> struct EraseType<TypeList<Head, Tail>, Head>
	{
		typedef Tail result;
	};

	template<typename Head, typename Tail, typename Type> struct EraseType<TypeList<Head, Tail>, Type>
	{
		typedef TypeList<Head, typename EraseType<Tail, Type>::result> result;
	};

	template<typename TList, typename Type> struct EraseAll;
	template<typename Type> struct EraseAll<NullType, Type>
	{
		typedef NullType result;
	};

	template<typename Tail, typename Type> struct EraseAll<TypeList<Type, Tail>, Type>
	{
		typedef typename EraseAll<Tail, Type>::result result;
	};

	template<typename Head, typename Tail, typename Type> struct EraseAll<TypeList<Head, Tail>, Type>
	{
		typedef TypeList<Head, typename EraseAll<Tail, Type>::result> result;
	};

	template<typename TList> struct  NoDuplicates;

	template<> struct NoDuplicates<NullType>
	{
		typedef NullType result;
	};

	template<typename Head, typename Tail> struct NoDuplicates<TypeList<Head, Tail>>
	{
	private:
		typedef typename NoDuplicates<Tail>::result L1;
		typedef typename EraseType<L1, Head>::result L2;
	public:
		typedef TypeList<Head, L2> result;
	};

	template<typename TList, typename Type, typename NewType> struct ReplaceType;

	template<typename Type, typename NewType> struct ReplaceType<NullType, Type, NewType>
	{
		typedef NullType result;
	};

	template<typename Tail, typename Type, typename NewType> struct ReplaceType<TypeList<Type, Tail>, Type, NewType>
	{
		typedef TypeList<NewType, Tail> result;
	};

	template<typename Head, typename Tail, typename Type, typename NewType> struct ReplaceType<TypeList<Head, Tail>, Type, NewType>
	{
		typedef TypeList<Head, typename ReplaceType<Tail, Type, NewType>::result> result;
	};

	template<typename TList, typename Type, typename NewType> struct ReplaceAll;

	template<typename Type, typename NewType> struct ReplaceAll<NullType, Type, NewType>
	{
		typedef NullType result;
	};

	template<typename Tail, typename Type, typename NewType> struct ReplaceAll<TypeList<Type, Tail>, Type, NewType>
	{
		typedef TypeList<NewType, typename ReplaceAll<Tail, Type, NewType>::result> result;
	};

	template<typename Head, typename Tail, typename Type, typename NewType> struct ReplaceAll<TypeList<Head, Tail>, Type, NewType>
	{
		typedef TypeList<Head, typename ReplaceAll<Tail, Type, NewType>::result> result;
	};

	template<class TList, class T> struct MostDerived;

	template<class T>
	struct MostDerived<NullType, T>
	{
		typedef T Result;
	};

	//Select class based on a boolean template, if SUPERSUBCLASS is true we return Candidate otherwise Head
	template<class Head, class Tail, class T>
	struct MostDerived<TypeList<Head, Tail>, T>
	{
	private:
		typedef typename MostDerived<Tail, T>::Result Candidate;
	public:
		typedef typename SelectType<SUPERSUBCLASS(Candidate, Head), Head, Candidate>::Result Result;
	};

	template<class T> struct DerivedToFront;

	template<>
	struct DerivedToFront<NullType>
	{
		typedef NullType Result;
	};

	template<class Head, class Tail>
	struct DerivedToFront<TypeList<Head, Tail>>
	{
	private:
		typedef typename MostDerived<Tail, Head>::Result mostDerived;
		typedef typename ReplaceType<Tail, mostDerived, Head>::Result L;
	public:
		typedef TypeList<mostDerived, L> Result;
	};
}


#endif //PRACTICESTUFF_TYPELISTS_H
