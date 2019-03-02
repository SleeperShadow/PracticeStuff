#pragma once
#include <memory>
#include <stdexcept>
#include "Creators.h"

class Widget 
{
	//code code here
};
class Gadget 
{
	//code goes here
};

//template <class CreationPolicy>
//class WidgetManager : public CreationPolicy
//{
//public:
//	//some code here
//};
//
//typedef WidgetManager<OpNewCreator<Widget>> MyWidgetManager;

template <template <class Created> class CreationPolicy = OpNewCreator>
class WidgetManager : public CreationPolicy<Widget>
{
public:
	Gadget* createGadget()
	{
		Gadget* gadget = CreationPolicy<Gadget>().create();
		return gadget;
	}

	void switchPrototype(Widget* newPrototype) // valid so long as its used with PrototypeWidgetManager
	{
		CreationPolicy<Widget>& myPolicy = *this;
		delete myPolicy.getPrototype();
		myPolicy.setPrototype(newPrototype);
	}
};

typedef WidgetManager<OpNewCreator> MyWidgetManager;

typedef WidgetManager<PrototypeCreator> PrototypeWidgetManager;

void usePrototypeManager()
{
	PrototypeWidgetManager mgr;
	mgr.setPrototype(OpNewCreator<Widget>::create());
}

template <class T>
struct NoChecking
{
	static void check(T*) {}
};

template <class T>
struct EnforceNotNull
{
	static void check(T* ptr) 
	{
		if (!ptr) throw std::runtime_error("obj was nullptr!")
	}
};

template <class T>
struct EnsureNotNull
{
	static void check(T*& ptr)
	{
		if(!ptr) 
			ptr = new T;
	}
};

template 
<
	class T,
	template<class> class CheckingPolicy,
	template<class> class ThreadingModel
>
class SmartPtr : public CheckingPolicy<T>, public ThreadingModel<T>
{
public:
	T* operator->()
	{
		typename ThreadingModel<SmartPtr>::Lock guard(*this);
		CheckingPolicy<T>::check(pointee_);
		return _pointee;
	}

private:
	T* _pointee;
};

template <class T>
class DefaultSmartPtrStorage
{
public:
	typedef T* PointerType;
	typedef T& ReferenceType;
protected:
	PointerType getPointer()const
	{
		return _ptr;
	}
	ReferenceType getReference()const
	{
		return *_ptr;
	}

private:
	PointerType _ptr;
};

template<
	class T,
	template <class> class CheckingPolicy,
	template <class> class ThreadingPolicy,
	template <class> class StoragePolicy
>
class SmartPointer : public StoragePolicy<T>
{
public:


};

template<class T , template <class> class CheckingPolicy>
class MySmartPtr : public CheckingPolicy<T>
{
public:
	template<class T1, template <class> class CP1>
	MySmartPtr(MySmartPtr<T1, CP1> const& other) : _pointee(other._pointee), CheckingPolicy<T>(other)
	{

	}

private:
	T* _pointee;
};