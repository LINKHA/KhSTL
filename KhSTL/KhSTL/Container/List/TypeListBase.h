#ifndef KH_STL_TYPE_LIST_BASE_H_
#define KH_STL_TYPE_LIST_BASE_H_

#include "TypeListNode.h"

namespace KhSTL {


template <typename _Ty> class tListBase
{
public:
	tListBase()
		: _head(nullptr)
		, _tail(nullptr)
		, _size(0)
	{
	}
	tListBase(unsigned size) // Reserve the tail node + initial capacity according to the list's size
		: _head(nullptr)
		, _tail(nullptr)
		, _size(0)
	{
	}
	virtual ~tListBase()
	{
		
	}

	/**
	* @brief : Swap with another list
	*/
	void Swap(tListBase& rhs)
	{
		KhSTL::Swap(_head, rhs._head);
		KhSTL::Swap(_tail, rhs._tail);
		KhSTL::Swap(_size, rhs._size);
		KhSTL::Swap(Base::_allocator, rhs.Base::_allocator);
	}
protected:
	/**
	* @brief : Return the head node
	*/
	tListNode<_Ty>* head() const { return static_cast<tListNode<_Ty>*>(_head); }
	/**
	* @brief : Return the tail node
	*/
	tListNode<_Ty>* tail() const { return static_cast<tListNode<_Ty>*>(_tail); }
	
protected:
	/// Head node pointer.
	tListNode<_Ty>* _head;
	/// Tail node pointer.
	tListNode<_Ty>* _tail;
	/// Number of nodes.
	unsigned _size;

};

template <typename _Ty> inline
	void Swap(tListBase<_Ty>& rhs, tListBase<_Ty>& lfs)
{
	rhs.Swap(lfs);
}

}
#endif //!KH_STL_TYPE_LIST_BASE_H_
