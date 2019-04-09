#include <iostream>
#include "Conversions.h"
#include "TypeTraits.h"
#include "TypeLists.h"
#include "ClassGeneration.h"
#include <vector>


int main()
{
	std::cout << (Conversion<double, double>::exists ? "kappa" : "not kappa") << std::endl;
	std::cout << TypeTraits<std::vector<int>::iterator>::isPointer << std::endl;

	std::vector<int> r{ 1,23,3 };
	TypeTraits<std::vector<int>>::ParameterType vectorref = r;
	
	std::cout << TL::length< TL::signedIntegrals>::value << std::endl;
	std::cout<<TL::length<TL::EraseType<TL::signedIntegrals, long>::result>::value<<std::endl;


	TL::tryOutClassGeneration();
	TL::tryOutClassGeneration2();

	return 0;
}