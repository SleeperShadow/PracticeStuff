#pragma once

template <class From, class To>
class Conversion
{
	typedef From Small;
	struct Big { From dummy[2]; };
	static Small Test(To);
	static Big Test(...);
	static From MakeT();
public:
	enum {
		exists =
		sizeof(Test(MakeT())) == sizeof(Small)
	};
};