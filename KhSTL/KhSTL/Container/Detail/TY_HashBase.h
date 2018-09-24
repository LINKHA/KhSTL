#pragma once
#include "TY_Allcator.h"
#include "TY_Swap.h"

namespace KH_STL 
{
namespace Detail {

/**
* Hash set/map node base class
*/
struct HashNodeBase
{
	/**
	* @brief : Construct
	*/
	HashNodeBase() 
		: down(nullptr)
		, prev(nullptr)
		, next(nullptr)
	{}

	/// Next node in the bucket.
	HashNodeBase* down;
	/// Previous node.
	HashNodeBase* prev;
	/// Next node.
	HashNodeBase* next;
};

/**
* Hash set/map iterator base class
*/
struct HashIteratorBase
{
	/**
	* @brief : Construct
	*/
	HashIteratorBase()
		: ptr(nullptr)
	{}
	/**
	* @brief : Construct with a node pointer
	*/
	explicit HashIteratorBase(HashNodeBase* ptr)
		: ptr(ptr)
	{}
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const HashIteratorBase& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const HashIteratorBase& rhs) const { return ptr != rhs.ptr; }
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
	HashNodeBase* ptr;
};

class HashBase 
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
	HashBase() :
		_head(nullptr),
		_tail(nullptr),
		_ptrs(nullptr),
		_allocator(nullptr)
	{}
	/**
	* @brief : Swap with another hash set or map
	*/
	void Swap(HashBase& rhs)
	{
		KH_STL::Detail::Swap(_head, rhs._head);
		KH_STL::Detail::Swap(_tail, rhs._tail);
		KH_STL::Detail::Swap(_ptrs, rhs._ptrs);
		KH_STL::Detail::Swap(_allocator, rhs._allocator);
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
	HashNodeBase** ptrs() const { return _ptrs ? _ptrs + 2 : nullptr; }

	/// List head node pointer.
	HashNodeBase* _head;
	/// List tail node pointer.
	HashNodeBase* _tail;
	/// Bucket head pointers.
	HashNodeBase** _ptrs;
	/// Node allocator.
	AllocatorBlock* _allocator;

};




}
}