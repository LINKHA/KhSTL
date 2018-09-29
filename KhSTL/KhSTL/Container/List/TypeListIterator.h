#ifndef KH_STL_LIST_ITERATOR_H_
#define KH_STL_LIST_ITERATOR_H_

#include "TypeListNode.h"

namespace KhSTL {

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

}
#endif //!KH_STL_LIST_ITERATOR_H_s