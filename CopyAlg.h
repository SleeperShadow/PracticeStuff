#include "TypeTraits.h"
#include "NiftyContainer.h"

enum CopyAlgoSelector { Conservative, Fast};


template<typename InputIt, typename OutputIt>
OutputIt CopyImpl(InputIt first, InputIt last, OutputIt result, Int2Type<Conservative>)
{
	for (; first != last; ++first, ++result)
		* result = *first;
	return result;
}

template<typename InputIt, typename OutputIt>
OutputIt CopyImpl(InputIt first, InputIt last, OutputIt result, Int2Type<Fast>)
{
	const size_t n = last - first;
	//supposedly we have a real fast function called BitBlast that Copies stuff
	//BitBlast(first, result, n * sizeof(*first));
	return result + n;
}

template<typename InputIt, typename OutputIt>
OutputIt Copy(InputIt first, InputIt last, OutputIt result)
{
	typedef TypeTraits<InputIt>::PointeeType srcPointee;
	typedef TypeTraits<OutputIt>::PointeeType dstPointee;
	enum 
	{
		copyAlgorithm = TypeTraits<InputIt>::isPointer && TypeTraits<OutputIt>::isPointer && 
		sizeof(srcPointee) == sizeof(dstPointee) ? Fast : Conservative
	};
	return CopyImpl(first, last, result, Int2Type<copyAlgorithm>);
}

