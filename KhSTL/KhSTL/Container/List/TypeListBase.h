#ifndef KH_STL_TYPE_LIST_BASE_H_
#define KH_STL_TYPE_LIST_BASE_H_

#include "TypeListNode.h"
#include "TypeListAlloctor.h"
#include "TypeListIterator.h"

namespace KhSTL {


template <typename _Ty,
	typename _Alloc = tAllocator<tListNode<_Ty>>>
	class tListBase : public tListAlloc<_Alloc>
{
public:
	using Base = tListAlloc<_Alloc>;
public:
	tListBase() 
		: Base()
		, _head(nullptr)
		, _tail(nullptr)
		, _size(0)
	{
		_head = _tail = reserveNode();
	}
	tListBase(unsigned size) // Reserve the tail node + initial capacity according to the list's size
		: Base(size)
		, _head(nullptr)
		, _tail(nullptr)
		, _size(0)
	{
		_head = _tail = reserveNode();
	}
	virtual ~tListBase()
	{
		freeNode(tail());
	}

	/// Swap with another linked list.
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
	/**
	* @brief : Allocate and insert a node into the list
	*/
	void insertNode(tListNode<_Ty>* dest, const _Ty& value)
	{
		if (!dest)
			return;

		tListNode<_Ty>* newNode = reserveNode(value);
		tListNode<_Ty>* prev = dest->Prev();
		newNode->next = dest;
		newNode->prev = prev;
		if (prev)
			prev->next = newNode;
		dest->prev = newNode;

		// Reassign the head node if necessary
		if (dest == head())
			_head = newNode;

		++_size;
	}
	/**
	* @brief : Erase and free a node. Return pointer to the next node,
	or to the end if could not erase
	*/
	tListNode<_Ty>* eraseNode(tListNode<_Ty>* node)
	{
		// The tail node can not be removed
		if (!node || node == _tail)
			return tail();

		tListNode<_Ty>* prev = node->Prev();
		tListNode<_Ty>* next = node->Next();
		if (prev)
			prev->next = next;
		next->prev = prev;

		// Reassign the head node if necessary
		if (node == head())
			_head = next;

		freeNode(node);
		--_size;

		return next;
	}
	/**
	* @brief : Reserve a node
	*/
	tListNode<_Ty>* reserveNode()
	{
		auto* newNode = static_cast<tListNode<_Ty>*>(Base::allocation());
		new(newNode) tListNode<_Ty>();
		return newNode;
	}
	/**
	* @brief : Reserve a node with initial value
	*/
	tListNode<_Ty>* reserveNode(const _Ty& value)
	{
		auto* newNode = static_cast<tListNode<_Ty>*>(Base::allocation());
		new(newNode) tListNode<_Ty>(value);
		return newNode;
	}
	/**
	* @brief : Free a node
	*/
	void freeNode(tListNode<_Ty>* node)
	{
		Base::free(node);
	}
protected:
	/// Head node pointer.
	tListNode<_Ty>* _head;
	/// Tail node pointer.
	tListNode<_Ty>* _tail;
	/// Number of nodes.
	unsigned _size;

};

template <typename _Ty, typename _Alloc> inline 
	void Swap(tListBase<_Ty, _Alloc>& rhs,tListBase<_Ty, _Alloc>& lfs)
{
	rhs.Swap(lfs);
}

}
#endif //!KH_STL_TYPE_LIST_BASE_H_
