#pragma once

template <class T, class U>
class Conversion
{
	typedef T Small;
	struct Big { T dummy[2]; };
	static Small Test(U);
	static Big Test(...);
	static T MakeT();
public:
	enum {
		exists =
		sizeof(Test(MakeT())) == sizeof(Small),
	};

	enum {
		sameType = false,
	};
};

template<class T>
class Conversion<T,T>
{
public:
	enum
	{
		exists = true,
	};

	enum {
		sameType = true,
	};
};
// checks whether U is convertible to T, basically upcasting in the inheritance tree
#define SUPERSUBCLASS(T, U) \
(Conversion<const U*, const T*>::exists && \
!Conversion<const T*, const void*>::sameType)

#define SUPERSUBCLASS_STRICT(T, U) \
(SUPERSUBCLASS(T,U) && \
!Conversion<const T, const U>::sameType)