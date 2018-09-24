#include "TypeHashBase.h"

namespace KhSTL {
namespace Detail {
	


void tHashBase::allocateBuckets(unsigned size, unsigned numBuckets)
{
	delete[] _ptrs;

	auto ptrs = new tHashNodeBase*[numBuckets + 2];
	auto* data = reinterpret_cast<unsigned*>(ptrs);
	data[0] = size;
	data[1] = numBuckets;
	_ptrs = ptrs;

	resetPtrs();
}

void tHashBase::resetPtrs()
{
	// Reset bucket pointers
	if (!_ptrs)
		return;

	unsigned numBuckets = NumBuckets();
	tHashNodeBase** tptrs = ptrs();
	for (unsigned i = 0; i < numBuckets; ++i)
		tptrs[i] = nullptr;
}





}
}