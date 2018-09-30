#ifndef KH_STL_DEQUE_BASE_H_
#define KH_STL_DEQUE_BASE_H_

#include "TypeDequeIterator.h"
#include "TypeDequeAllocator.h"

namespace KhSTL {

template <typename _Ty
	, unsigned _Size = 0
	, typename _Alloc = tAllocator<_Ty>>
	//, typename _Alloc = tmAllocator<_Ty>>
	class tDequeBase : public tDequeAlloc<_Alloc>
{
public:
	using Base = tDequeAlloc<_Alloc>;

	using MapPoint = _Ty**;

public:
	tDequeBase()
		//:_map(nullptr)
	{
		
	}
	virtual ~tDequeBase()
	{
		
	}

protected:

	/// Map point (value pptr)
	//MapPoint _map;
};


}
#endif //!KH_STL_DEQUE_BASE_H_