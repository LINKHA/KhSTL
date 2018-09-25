#ifndef KH_STL_TYPE_HASH_BASE_H_
#define KH_STL_TYPE_HASH_BASE_H_
#include "TypeAllcator.h"
#include "TypeSwap.h"

namespace KhSTL {
namespace Detail 
{

/**
* Hash set/map node base class
*/
struct tHashNodeBase
{
	/**
	* @brief : Construct
	*/
	tHashNodeBase()
		: down(nullptr)
		, prev(nullptr)
		, next(nullptr)
	{}

	/// Next node in the bucket.
	tHashNodeBase* down;
	/// Previous node.
	tHashNodeBase* prev;
	/// Next node.
	tHashNodeBase* next;
};

/**
* Hash set/map iterator base class
*/
struct tHashIteratorBase
{
	/**
	* @brief : Construct
	*/
	tHashIteratorBase()
		: ptr(nullptr)
	{}
	/**
	* @brief : Construct with a node pointer
	*/
	explicit tHashIteratorBase(tHashNodeBase* ptr)
		: ptr(ptr)
	{}
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const tHashIteratorBase& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const tHashIteratorBase& rhs) const { return ptr != rhs.ptr; }
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
	tHashNodeBase* ptr;
};

class tHashBase 
{
public:
	/// Initial amount of buckets
	static const unsigned MIN_BUCKETS = 8;
	/// Maximum load factor
	static const unsigned MAX_LOAD_FACTOR = 4;
public:
	/**
	* @brief : Construct
	*/
	tHashBase() :
		_head(nullptr),
		_tail(nullptr),
		_ptrs(nullptr),
		_allocator(nullptr)
	{}
	/**
	* @brief : Swap with another hash set or map
	*/
	void Swap(tHashBase& rhs)
	{
		Detail::Swap(_head, rhs._head);
		Detail::Swap(_tail, rhs._tail);
		Detail::Swap(_ptrs, rhs._ptrs);
		Detail::Swap(_allocator, rhs._allocator);
	}
	/**
	* @brief : Return number of elements
	*/
	unsigned Size() const { return _ptrs ? (reinterpret_cast<unsigned*>(_ptrs))[0] : 0; }
	/**
	* @brief : Return number of buckets
	*/
	unsigned NumBuckets() const { return _ptrs ? (reinterpret_cast<unsigned*>(_ptrs))[1] : 0; }
	/**
	* @brief : Return whether has no elements
	*/
	bool Empty() const { return Size() == 0; }
protected:
	/**
	* @brief : Allocate bucket head pointers + room for size and bucket count variables
	*/
	void allocateBuckets(unsigned size, unsigned numBuckets);
	/**
	* @brief : Reset bucket head pointers
	*/
	void resetPtrs();
	/**
	* @brief : Set new size
	*/
	void setSize(unsigned size) { if (_ptrs) (reinterpret_cast<unsigned*>(_ptrs))[0] = size; }
	/**
	* @brief : Return bucket head pointers
	*/
	tHashNodeBase** ptrs() const { return _ptrs ? _ptrs + 2 : nullptr; }

	/// List head node pointer.
	tHashNodeBase* _head;
	/// List tail node pointer.
	tHashNodeBase* _tail;
	/// Bucket head pointers.
	tHashNodeBase** _ptrs;
	/// Node allocator.
	tAllocatorBlock* _allocator;

};




}
}

#endif //!KH_STL_TYPE_HASH_BASE_H_