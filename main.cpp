#include <iostream>
#include "Conversions.h"
#include "TypeTraits.h"
#include <vector>


int main()
{
	std::cout << (Conversion<double, double>::exists ? "kappa" : "not kappa") << std::endl;
	std::cout << TypeTraits<std::vector<int>::iterator>::isPointer << std::endl;

	std::vector<int> r{ 1,23,3 };
	TypeTraits<std::vector<int>>::ParameterType vectorref = r;


	return 0;
}