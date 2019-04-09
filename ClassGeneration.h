#pragma once
#include "TypeLists.h"
#include "TypeToTypeMapping.h"
#include <string>
#include <iostream>

namespace TL
{
	template <class TList, template <class> class Unit> class GenScatterHierarchy;

	template<class T1, class T2, template <class> class Unit>
	class GenScatterHierarchy<TypeList<T1, T2>, Unit>
		: public GenScatterHierarchy<T1, Unit>,
		  public GenScatterHierarchy<T2, Unit>
	{
	public:
		typedef TypeList<T1, T2> TList;
		typedef GenScatterHierarchy<T1, Unit> LeftBase;
		typedef GenScatterHierarchy<T2, Unit> RightBase;

		template <typename U>
		struct Rebind
		{
			typedef Unit<U> Result;
		};
	};

	// Non typelist type specialization
	template<class AtomicType, template <class> class Unit>
	class GenScatterHierarchy : public Unit<AtomicType>
	{
		typedef	Unit<AtomicType> LeftBase;
	};

	// Do nothing for NullType
	template<template <class> class Unit>
	class GenScatterHierarchy<NullType, Unit>
	{
	};

	// If we have the class below
	template<class T> class Holder
	{
	public:
		T _value;
	};

	// the below typedef gives us a class that inherits from Holder<int>, Holder<double> and Holder<float>
	// assuming that the compiler optimizes away the empty classes such as TypeList<NullType, Holder>
	typedef GenScatterHierarchy<TYPELIST_3(std::string, int, float), Holder> Info;

	// some interesting things can be done such as, though the cast is pretty ugly
	// The explicit cast is necessary to disambiguate the member variable name value_. Otherwise, the compiler
	// is confused as to which value_ member you are referring to.
	void tryOutClassGeneration()
	{
		Info info;
		
		(static_cast<Holder<std::string>&>(info))._value = "something";

		std::string name = (static_cast<Holder<std::string>&>(info))._value;
		std::cout << name << std::endl;
	}

	template < class T, class H>
	typename H::template Rebind<T>::Result& Field(H& obj)
	 {
	     return obj;
	 }
	
	 template < class T, class H>
	 const typename H::template Rebind<T>::Result& Field(const H& obj)
	 {
	     return obj;
	 }
	 // Rebind<Holder<int>>(obj) would save us the cast
	 void tryOutClassGeneration2()
	 {
		 Info info;

		 (static_cast<Holder<std::string>&>(info))._value = "something";

		 std::cout << Field<std::string>(info)._value << std::endl;
	 }




}