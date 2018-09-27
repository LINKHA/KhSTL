#ifndef KH_STL_DEQUE_BASE_H_
#define KH_STL_DEQUE_BASE_H_

#include "../Algorithms/TypeSwap.h"
#include "../Allocator/TypeAllcator.h"

namespace KhSTL {
/**
* Deque node base class
*/
struct tDequeNodeBase
{
	/**
	* @brief : Construct
	*/
	tDequeNodeBase()
		: prev(nullptr)
		, next(nullptr)
	{}
	/// Previous node.
	tDequeNodeBase* prev;
	/// Next node.
	tDequeNodeBase* next;
};

/**
* Hash set/map iterator base class
*/
struct tDequeIteratorBase
{
	/**
	* @brief : Construct
	*/
	tDequeIteratorBase()
		: ptr(nullptr)
	{}
	/**
	* @brief : Construct with a node pointer
	*/
	explicit tDequeIteratorBase(tDequeNodeBase* ptr)
		: ptr(ptr)
	{}
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const tDequeIteratorBase& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const tDequeIteratorBase& rhs) const { return ptr != rhs.ptr; }
	/**
	* @brief : Go to the next node
	*/
	void GotoNext()
	{
		if (ptr)
			ptr = ptr->next;
	}
	/**
	* @brief : Go to the previous node
	*/
	void GotoPrev()
	{
		if (ptr)
			ptr = ptr->prev;
	}

	/// Node pointer
	tDequeNodeBase* ptr;
};

class tDequeBase
{
public:
	tDequeBase()
		: _allocator(nullptr)
	{}

private:
	/// Node allocator.
	tAllocatorBlock* _allocator;
};


}
#endif //!KH_STL_DEQUE_BASE_H_