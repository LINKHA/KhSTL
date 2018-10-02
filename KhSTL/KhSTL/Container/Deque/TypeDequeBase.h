#ifndef KH_STL_TYPE_DEQUE_BASE_H_
#define KH_STL_TYPE_DEQUE_BASE_H_

#include "TypeDequeIterator.h"
#include "TypeDequeAllocator.h"

namespace KhSTL {

template <typename _Ty
	, unsigned _Size>
	class tDequeBase
{
public:
	using MapPoint = _Ty**;

	using Iterator = tDequeIterator<_Ty, _Size>;
	using ConstIterator = tDequeConstIterator<_Ty, _Size>;

public:

	tDequeBase()
		: _start()
		, _finish()
		, _map(0)
		, _mapSize(0)
	{
		
	}

	virtual ~tDequeBase()
	{
		
	}

protected:

	/// Control center
	MapPoint _map;
	unsigned _mapSize;

	Iterator _start;
	Iterator _finish;


};


}
#endif //!KH_STL_TYPE_DEQUE_BASE_H_