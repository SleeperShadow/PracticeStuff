//
// Created by Licht on 2019-03-04.
//

#ifndef PRACTICESTUFF_NIFTYCONTAINER_H
#define PRACTICESTUFF_NIFTYCONTAINER_H

template<int v>
struct Int2Type
{
	enum { value = v };
};

// clumsy type selection
/*
template <typename Type, bool isPolymorphic>
struct NiftyValueContainerTraits
{
	typedef Type* value_type;
};

template <typename Type>
struct NiftyValueContainerTraits<Type, false>
{
	typedef Type value_type;
};*/


// better type selection
template <bool flag, typename T, typename U>
struct SelectType
{
	typedef T type;
};

template <typename T, typename U>
struct SelectType<false, T, U>
{
	typedef U type;
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
private:
	// clumsy definition of type selection
/*	typedef  NiftyValueContainerTraits<T, isPolymorphic> traits;
	typedef typename traits::value_type value_type;*/

// better

	typedef typename SelectType<isPolymorphic, T*, T>::type value_Type;
private:
	void add(T* obj, Int2Type<true>)
	{
		auto objClone = obj->clone();
		// do sth with obj
	}
	void add(T* obj, Int2Type<false>)
	{
		auto objCopy = new T(*obj);
		// do sth with copy constructed obj
	}

public:

	void add(T* obj)
	{
		add(obj, Int2Type<isPolymorphic>());
	}


};

#endif //PRACTICESTUFF_NIFTYCONTAINER_H
