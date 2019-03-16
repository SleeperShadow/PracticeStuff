//
// Created by Licht on 2019-03-04.
//

#ifndef PRACTICESTUFF_TYPETOTYPEMAPPING_H
#define PRACTICESTUFF_TYPETOTYPEMAPPING_H

namespace sample
{
	class Widget
	{
	public:
		template <class U>
		Widget(U const& arg, int sz)
		{

		}
	};
}
//dummy implementation
template <class T, class U>
T* create(U const& arg)
{
	return new T(arg);
}
// if some type has its own specific constructor
//  we have to overload and pass in a Object of the type we want to construct
// such as Widget for example
// which means we have to construct a Widget, which for complex objects is a huge drawback
template <class U>
sample::Widget* create(U const& arg, sample::Widget)
{
	return new sample::Widget(arg, -1);
}

template <typename T>
struct Type2Type
{
	typedef T originalType;
};

//type 2 type implementation
template <class T, class U>
T* create(U const& arg, Type2Type<T>)
{
	return new T(arg);
}

template <class U>
sample::Widget* create(U const& arg, Type2Type<sample::Widget>)
{
	return new sample::Widget(arg, -1);
}

#endif //PRACTICESTUFF_TYPETOTYPEMAPPING_H
