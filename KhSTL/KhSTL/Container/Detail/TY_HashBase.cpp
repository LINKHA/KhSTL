#include "TY_HashBase.h"

namespace KH_STL {
namespace Detail {
	


void HashBase::allocateBuckets(unsigned size, unsigned numBuckets)
{
	delete[] _ptrs;

	auto ptrs = new HashNodeBase*[numBuckets + 2];
	auto* data = reinterpret_cast<unsigned*>(ptrs);
	data[0] = size;
	data[1] = numBuckets;
	_ptrs = ptrs;

	resetPtrs();
}

void HashBase::resetPtrs()
{
	// Reset bucket pointers
	if (!_ptrs)
		return;

	unsigned numBuckets = NumBuckets();
	HashNodeBase** tptrs = ptrs();
	for (unsigned i = 0; i < numBuckets; ++i)
		tptrs[i] = nullptr;
}





}
}