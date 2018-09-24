#pragma once
#include "TY_Swap.h"
#include "TY_Allcator.h"


namespace KH_STL {
namespace Detail
{


/**
* Doubly-linked list node base class
*/
struct ListNodeBase
{
	/**
	* @brief : Construct
	*/
	ListNodeBase() :
		prev(nullptr),
		next(nullptr)
	{}

	/// Previous node.
	ListNodeBase* prev;
	/// Next node.
	ListNodeBase* next;
};

/**
* Doubly-linked list iterator base class
*/
struct ListIteratorBase
{
	/**
	* @brief : Construct
	*/
	ListIteratorBase() :
		ptr(nullptr)
	{}
	/**
	* @brief : Construct with a node pointer
	*/
	explicit ListIteratorBase(ListNodeBase* ptr) :
		ptr(ptr)
	{}
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const ListIteratorBase& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const ListIteratorBase& rhs) const { return ptr != rhs.ptr; }
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
	ListNodeBase* ptr;
};

class ListBase 
{
public:
	ListBase() :
		_head(nullptr),
		_tail(nullptr),
		_allocator(nullptr),
		_size(0)
	{
	}

	/// Swap with another linked list.
	void Swap(ListBase& rhs)
	{
		Detail::Swap(_head, rhs._head);
		Detail::Swap(_tail, rhs._tail);
		Detail::Swap(_allocator, rhs._allocator);
		Detail::Swap(_size, rhs._size);
	}

protected:
	/// Head node pointer.
	ListNodeBase* _head;
	/// Tail node pointer.
	ListNodeBase* _tail;
	/// Node allocator.
	AllocatorBlock* _allocator;
	/// Number of nodes.
	unsigned _size;

};



}
}