#ifndef KH_STL_TYPE_LIST_H_
#define KH_STL_TYPE_LIST_H_

#include "TypeListBase.h"
#include <initializer_list>

namespace KhSTL {


/**
* Doubly-linked list template class
*/
template <typename _Ty,
	typename _Alloc = tAllocator<_Ty>> 
	class tList : public tListBase <_Ty, _Alloc>
{
public:
	using Base = tListBase <_Ty, _Alloc>;
public:
	

	/**
	* List iterator
	*/
	struct Iterator : public tListIteratorBase
	{
		/**
		* @brief : Construct
		*/
		Iterator() = default;
		/**
		* @brief : Construct with a node pointer
		*/
		explicit Iterator(tListNode<_Ty>* ptr) 
			: tListIteratorBase(ptr)
		{}
		/**
		* @brief : Preincrement the pointer
		*/
		Iterator& operator ++()
		{
			GotoNext();
			return *this;
		}
		/**
		* @brief : Postincrement the pointer
		*/
		Iterator operator ++(int)
		{
			Iterator it = *this;
			GotoNext();
			return it;
		}
		/**
		* @brief : Predecrement the pointer
		*/
		Iterator& operator --()
		{
			GotoPrev();
			return *this;
		}
		/**
		* @brief : Postdecrement the pointer
		*/
		Iterator operator --(int)
		{
			Iterator it = *this;
			GotoPrev();
			return it;
		}
		/**
		* @brief : Point to the node value
		*/
		_Ty* operator ->() const { return &(static_cast<tListNode<_Ty>*>(ptr))->value; }
		/**
		* @brief : Dereference the node value
		*/
		_Ty& operator *() const { return (static_cast<tListNode<_Ty>*>(ptr))->value; }
	};

	/**
	* List const iterator
	*/
	struct ConstIterator : public tListIteratorBase
	{
		/**
		* @brief : Construct
		*/
		ConstIterator() = default;
		/**
		* @brief : Construct with a node pointer
		*/
		explicit ConstIterator(tListNode<_Ty>* ptr)
			: tListIteratorBase(ptr)
		{}
		/**
		* @brief : Construct from a non-const iterator
		*/
		ConstIterator(const Iterator& rhs)         // NOLINT(google-explicit-constructor)
			: tListIteratorBase(rhs.ptr)
		{}
		/**
		* @brief : Assign from a non-const iterator
		*/
		ConstIterator& operator =(const Iterator& rhs)
		{
			ptr = rhs.ptr;
			return *this;
		}
		/**
		* @brief : Preincrement the pointer
		*/
		ConstIterator& operator ++()
		{
			GotoNext();
			return *this;
		}
		/**
		* @brief : Postincrement the pointer
		*/
		ConstIterator operator ++(int)
		{
			ConstIterator it = *this;
			GotoNext();
			return it;
		}
		/**
		* @brief : Predecrement the pointer
		*/
		ConstIterator& operator --()
		{
			GotoPrev();
			return *this;
		}
		/**
		* @brief : Postdecrement the pointer
		*/
		ConstIterator operator --(int)
		{
			ConstIterator it = *this;
			GotoPrev();
			return it;
		}
		/**
		* @brief : Point to the node value
		*/
		const _Ty* operator ->() const { return &(static_cast<tListNode<_Ty>*>(ptr))->value; }
		/**
		* @brief : Dereference the node value
		*/
		const _Ty& operator *() const { return (static_cast<tListNode<_Ty>*>(ptr))->value; }
	};

	/**
	* @brief : Construct empty
	*/
	tList()
		: Base()
	{
		//_allocator = AllocatorInitialize((unsigned)sizeof(Node));
		//_head = _tail = reserveNode();
	}
	/**
	* @brief : Construct from another list
	*/
	tList(const tList<_Ty>& list)
		: Base(list.Size() + 1)
	{
		
		//_allocator = AllocatorInitialize((unsigned)sizeof(Node), list.Size() + 1);
		//_head = _tail = reserveNode();
		*this = list;
	}
	/**
	* @brief : Move-construct from another list
	*/
	tList(tList<_Ty> && list) noexcept
	{
		Swap(list);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tList(const std::initializer_list<_Ty>& list) 
		: tList()
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			Push(*it);
		}
	}
	/**
	* @brief : Destruct
	*/
	~tList()
	{
		Clear();
		//freeNode(tail());
		//AllocatorUninitialize(_allocator);
	}
	/**
	* @brief : Assign from another list
	*/
	tList& operator =(const tList<_Ty>& rhs)
	{
		// Clear, then insert the nodes of the other list. In case of self-assignment do nothing
		if (&rhs != this)
		{
			Clear();
			Insert(End(), rhs);
		}
		return *this;
	}
	/**
	* @brief : Move-assign from another list
	*/
	tList& operator =(tList<_Ty> && rhs) noexcept
	{
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign an element
	*/
	tList& operator +=(const _Ty& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign a list
	*/
	tList& operator +=(const tList<_Ty>& rhs)
	{
		Insert(End(), rhs);
		return *this;
	}
	/**
	* @brief : Test for equality with another list
	*/
	bool operator ==(const tList<_Ty>& rhs) const
	{
		if (rhs.Base::_size != Base::_size)
			return false;

		ConstIterator i = Begin();
		ConstIterator j = rhs.Begin();
		while (i != End())
		{
			if (*i != *j)
				return false;
			++i;
			++j;
		}

		return true;
	}
	/**
	* @brief : Test for inequality with another list
	*/
	bool operator !=(const tList<_Ty>& rhs) const
	{
		if (rhs.Base::_size != Base::_size)
			return true;

		ConstIterator i = Begin();
		ConstIterator j = rhs.Begin();
		while (i != End())
		{
			if (*i != *j)
				return true;
			++i;
			++j;
		}

		return false;
	}
	/**
	* @brief : Insert an element to the end
	*/
	void PushBack(const _Ty& value) { Base::insertNode(Base::tail(), value); }
	/**
	* @brief : Insert an element to the beginning
	*/
	void PushFront(const _Ty& value) { Base::insertNode(Base::head(), value); }
	/**
	* @brief : Insert an element at position
	*/
	void Insert(const Iterator& dest, const _Ty& value) { insertNode(static_cast<tListNode<_Ty>*>(dest.ptr), value); }
	/**
	* @brief : Insert a list at position
	*/
	void Insert(const Iterator& dest, const tList<_Ty>& list)
	{
		auto* destNode = static_cast<tListNode<_Ty>*>(dest.ptr);
		ConstIterator it = list.Begin();
		ConstIterator end = list.End();
		while (it != end)
			insertNode(destNode, *it++);
	}
	/**
	* @brief : Insert elements by iterators
	*/
	void Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
	{
		auto* destNode = static_cast<tListNode<_Ty>*>(dest.ptr);
		ConstIterator it = start;
		while (it != end)
			insertNode(destNode, *it++);
	}
	/**
	* @brief : Insert elements
	*/
	void Insert(const Iterator& dest, const _Ty* start, const _Ty* end)
	{
		auto* destNode = static_cast<tListNode<_Ty>*>(dest.ptr);
		const _Ty* ptr = start;
		while (ptr != end)
			insertNode(destNode, *ptr++);
	}
	/**
	* @brief : Erase the last element
	*/
	void PopBack()
	{
		if (Base::_size)
			Erase(--End());
	}
	/**
	* @brief : Erase the first element
	*/
	void PopFront()
	{
		if (Base::_size)
			Erase(Begin());
	}
	/**
	* @brief : Erase an element by iterator. Return iterator to the next element
	*/
	Iterator Erase(Iterator it)
	{
		return Iterator(eraseNode(static_cast<tListNode<_Ty>*>(it.ptr)));
	}
	/**
	* @brief : Erase a range by iterators. Return an iterator to the next element
	*/
	Iterator Erase(const Iterator& start, const Iterator& end)
	{
		Iterator it = start;
		while (it != end)
			it = Erase(it);

		return it;
	}
	/**
	* @brief : Clear the list
	*/
	void Clear()
	{
		if (Size())
		{
			for (Iterator i = Begin(); i != End();)
			{
				Base::freeNode(static_cast<tListNode<_Ty>*>(i++.ptr));
				i.ptr->prev = 0;
			}

			Base::_head = Base::_tail;
			Base::_size = 0;
		}
	}
	/**
	* @brief : Resize the list by removing or adding items at the end
	*/
	void Resize(unsigned newSize)
	{
		while (Base::_size > newSize)
			PopBack();

		while (Base::_size < newSize)
			insertNode(Base::tail(), _Ty());
	}
	/**
	* @brief : Return iterator to value, or to the end if not found
	*/
	Iterator Find(const _Ty& value)
	{
		Iterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return const iterator to value, or to the end if not found
	*/
	ConstIterator Find(const _Ty& value) const
	{
		ConstIterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return whether contains a specific value
	*/
	bool Contains(const _Ty& value) const { return Find(value) != End(); }
	/**
	* @brief : Return iterator to the first element
	*/
	Iterator Begin() { return Iterator(Base::head()); }
	/**
	* @brief : Return iterator to the first element
	*/
	ConstIterator Begin() const { return ConstIterator(Base::head()); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(Base::tail()); }
	/**
	* @brief : Return iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(Base::tail()); }
	/**
	* @brief : Return first element
	*/
	_Ty& Front() { return *Begin(); }
	/**
	* @brief : Return const first element
	*/
	const _Ty& Front() const { return *Begin(); }
	/**
	* @brief : Return last element
	*/
	_Ty& Back() { return *(--End()); }
	/**
	* @brief : Return const last element
	*/
	const _Ty& Back() const { return *(--End()); }
	/**
	* @brief : Return number of elements
	*/
	unsigned Size() const { return Base::_size; }
	/**
	* @brief : Return whether list is empty
	*/
	bool Empty() const { return Base::_size == 0; }

};
	
template <typename _Ty> typename tList<_Ty>::ConstIterator begin(const tList<_Ty>& v) { return v.Begin(); }

template <typename _Ty> typename tList<_Ty>::ConstIterator end(const tList<_Ty>& v) { return v.End(); }

template <typename _Ty> typename tList<_Ty>::Iterator begin(tList<_Ty>& v) { return v.Begin(); }

template <typename _Ty> typename tList<_Ty>::Iterator end(tList<_Ty>& v) { return v.End(); }


}
#endif //!KH_STL_TYPE_LIST_H_
