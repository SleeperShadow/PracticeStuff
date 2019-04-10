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

	template <class T>
	struct TupleUnit
	{
		T value_;
		operator T& () { return value_; }
		operator const T& () { return value_; }
	};

	template <class TList>
	struct Tuple : public GenScatterHierarchy<TList, TupleUnit>
	{

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


	 template <typename H, unsigned int i> struct FieldHelper;

	 template <typename H> struct FieldHelper<H, 0>
	 {
		 typedef typename H::TList::Head ElementType;
		 typedef typename H::template Rebind<ElementType>::Result UnitType;

		 enum {
			 isConst = TypeTraits<H>::isConst,
			 isTuple = Conversion<UnitType, TupleUnit<ElementType>>::sameType,
		 };
		 
		 typedef const typename H::LeftBase ConstLeftBase;
		 //if H is const select the const type
		 typedef typename SelectType<isConst, ConstLeftBase, typename H::LeftBase>::Result LeftBase;

		 typedef const typename H::RightBase ConstRightBase;
		 // if H is const select the const type
		 typedef typename SelectType<isConst, ConstRightBase, typename H::RightBase>::Result RightBase;

		 typedef typename SelectType<isTuple, const ElementType, UnitType>::Result UnqualifiedResultType;

		 typedef typename SelectType<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;

		 static ResultType& Do(H& obj)
		 {
			 LeftBase& leftBase = obj;
			 return leftBase;
		 }
	 };

	 template<typename H, unsigned int i> struct FieldHelper
	 {
		 typedef typename TL::TypeAt<typename H::TList, i>::Result ElementType;
		 typedef typename H::template Rebind<ElementType>::Result UnitType;

		 enum {
			 isConst = TypeTraits<H>::isConst,
			 isTuple = Conversion<UnitType, TupleUnit<ElementType>>::sameType,
		 };

		 typedef const typename H::RightBase ConstRightBase;
		 typedef typename SelectType<isConst, ConstRightBase, typename H::RightBase> RightBase;

		 typedef typename SelectType<isTuple, ElementType, UnitType>::Result UnqualifiedResultType;
		 typedef typename SelectType<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;

		 static ResultType& Do(H& obj)
		 {
			 RightBase& rightBase = obj;
			 return FieldHelper<RightBase, i - 1>::Do(rightBase);
		 }
	 };

	 template <int i, class H>
	 typename FieldHelper<H, i>::ResultType& Field(H& obj)
	 {
		 return FieldHelper<H, i>::Do(obj);
	 }

	 void tryOutIndexedGetter()
	 {
		 Info info;

		 (static_cast<Holder<std::string>&>(info))._value = "something";
		 std::cout << Field<0>(info)._value<<std::endl;
	 }
}