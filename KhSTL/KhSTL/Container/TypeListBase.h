#ifndef KH_STL_TYPE_LIST_BASE_H_
#define KH_STL_TYPE_LIST_BASE_H_

#include "../Algorithms/TypeSwap.h"
#include "../Allocator/TypeAllcator.h"


namespace KhSTL {

/**
* Doubly-linked list node base class
*/
struct tListNodeBase
{
	/**
	* @brief : Construct
	*/
	tListNodeBase() 
		: prev(nullptr)
		, next(nullptr)
	{}

	/// Previous node.
	tListNodeBase* prev;
	/// Next node.
	tListNodeBase* next;
};

/**
* Doubly-linked list iterator base class
*/
struct tListIteratorBase
{
	/**
	* @brief : Construct
	*/
	tListIteratorBase() 
		: ptr(nullptr)
	{}
	/**
	* @brief : Construct with a node pointer
	*/
	explicit tListIteratorBase(tListNodeBase* ptr) 
		: ptr(ptr)
	{}
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const tListIteratorBase& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const tListIteratorBase& rhs) const { return ptr != rhs.ptr; }
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

	/// Node pointer.
	tListNodeBase* ptr;
};

class tListBase 
{
public:
	tListBase() :
		_head(nullptr),
		_tail(nullptr),
		_allocator(nullptr),
		_size(0)
	{
	}

	/// Swap with another linked list.
	void Swap(tListBase& rhs)
	{
		KhSTL::Swap(_head, rhs._head);
		KhSTL::Swap(_tail, rhs._tail);
		KhSTL::Swap(_allocator, rhs._allocator);
		KhSTL::Swap(_size, rhs._size);
	}

protected:
	/// Head node pointer.
	tListNodeBase* _head;
	/// Tail node pointer.
	tListNodeBase* _tail;
	/// Node allocator.
	tAllocatorBlock* _allocator;
	/// Number of nodes.
	unsigned _size;

};



}
#endif //!KH_STL_TYPE_LIST_BASE_H_
