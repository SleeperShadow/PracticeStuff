#pragma once
template<bool> struct CompileTimeErorr;

//template<> struct CompileTimeErorr<true>
//{
//};
//
//#define STATIC_CHECK(expr) \
//(CompileTimeErorr<(expr) ? 1:0>())
//

template<bool> struct CompileTimeChecker
{
	CompileTimeChecker(...);
};

template<> struct CompileTimeChecker<true> {};

#define STATIC_CHECK(expr,msg)\
{\
	class ERROR_##msg{}; \
	(void)sizeof(CompileTimeChecker<expr != 0>((ERROR_##msg())));\
}

template <class To, class From>
To safe_reinterpret_cast(From from)
{
	STATIC_CHECK(sizeof(From) <= sizeof(To),
		Destination_Type_Too_Narrow);

	return reinterpret_cast<To>(from);
}