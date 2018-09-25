#ifndef KH_STL_TYPE_LIST_H_
#define KH_STL_TYPE_LIST_H_

#include "TypeListBase.h"
#include <initializer_list>

namespace KhSTL {
namespace Detail
{


/**
* Doubly-linked list template class
*/
template <typename _Value> class tList : public tListBase
{
public:
	/**
	* List node
	*/
	struct Node : public tListNodeBase
	{
		/**
		* @brief : Construct undefined
		*/
		Node() = default;
		/**
		* @brief : Construct with value
		*/
		explicit Node(const _Value& tValue) 
			: value(tValue)
		{}
		/**
		* @brief : Return next node
		*/
		Node* Next() const { return static_cast<Node*>(next); }
		/**
		* @brief : Return previous node
		*/
		Node* Prev() { return static_cast<Node*>(prev); }

		/// Node value
		_Value value;
	};

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
		explicit Iterator(Node* ptr) 
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
		_Value* operator ->() const { return &(static_cast<Node*>(ptr))->value; }
		/**
		* @brief : Dereference the node value
		*/
		_Value& operator *() const { return (static_cast<Node*>(ptr))->value; }
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
		explicit ConstIterator(Node* ptr)
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
		const _Value* operator ->() const { return &(static_cast<Node*>(ptr))->value; }
		/**
		* @brief : Dereference the node value
		*/
		const _Value& operator *() const { return (static_cast<Node*>(ptr))->value; }
	};

	/**
	* @brief : Construct empty
	*/
	tList()
	{
		_allocator = AllocatorInitialize((unsigned)sizeof(Node));
		_head = _tail = ReserveNode();
	}
	/**
	* @brief : Construct from another list
	*/
	tList(const tList<_Value>& list)
	{
		// Reserve the tail node + initial capacity according to the list's size
		_allocator = AllocatorInitialize((unsigned)sizeof(Node), list.Size() + 1);
		_head = _tail = ReserveNode();
		*this = list;
	}
	/**
	* @brief : Move-construct from another list
	*/
	tList(tList<_Value> && list) noexcept
	{
		Swap(list);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tList(const std::initializer_list<_Value>& list) 
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
		FreeNode(Tail());
		AllocatorUninitialize(_allocator);
	}
	/**
	* @brief : Assign from another list
	*/
	tList& operator =(const tList<_Value>& rhs)
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
	tList& operator =(tList<_Value> && rhs) noexcept
	{
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign an element
	*/
	tList& operator +=(const _Value& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign a list
	*/
	tList& operator +=(const tList<_Value>& rhs)
	{
		Insert(End(), rhs);
		return *this;
	}
	/**
	* @brief : Test for equality with another list
	*/
	bool operator ==(const tList<_Value>& rhs) const
	{
		if (rhs._size != _size)
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
	bool operator !=(const tList<_Value>& rhs) const
	{
		if (rhs._size != _size)
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
	void Push(const _Value& value) { InsertNode(Tail(), value); }
	/**
	* @brief : Insert an element to the beginning
	*/
	void PushFront(const _Value& value) { InsertNode(Head(), value); }
	/**
	* @brief : Insert an element at position
	*/
	void Insert(const Iterator& dest, const _Value& value) { InsertNode(static_cast<Node*>(dest.ptr), value); }
	/**
	* @brief : Insert a list at position
	*/
	void Insert(const Iterator& dest, const tList<_Value>& list)
	{
		auto* destNode = static_cast<Node*>(dest.ptr);
		ConstIterator it = list.Begin();
		ConstIterator end = list.End();
		while (it != end)
			InsertNode(destNode, *it++);
	}
	/**
	* @brief : Insert elements by iterators
	*/
	void Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
	{
		auto* destNode = static_cast<Node*>(dest.ptr);
		ConstIterator it = start;
		while (it != end)
			InsertNode(destNode, *it++);
	}
	/**
	* @brief : Insert elements
	*/
	void Insert(const Iterator& dest, const _Value* start, const _Value* end)
	{
		auto* destNode = static_cast<Node*>(dest.ptr);
		const _Value* ptr = start;
		while (ptr != end)
			InsertNode(destNode, *ptr++);
	}
	/**
	* @brief : Erase the last element
	*/
	void Pop()
	{
		if (_size)
			Erase(--End());
	}
	/**
	* @brief : Erase the first element
	*/
	void PopFront()
	{
		if (_size)
			Erase(Begin());
	}
	/**
	* @brief : Erase an element by iterator. Return iterator to the next element
	*/
	Iterator Erase(Iterator it)
	{
		return Iterator(EraseNode(static_cast<Node*>(it.ptr_)));
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
				FreeNode(static_cast<Node*>(i++.ptr));
				i.ptr->prev = 0;
			}

			_head = _tail;
			_size = 0;
		}
	}
	/**
	* @brief : Resize the list by removing or adding items at the end
	*/
	void Resize(unsigned newSize)
	{
		while (_size > newSize)
			Pop();

		while (_size < newSize)
			InsertNode(Tail(), _Value());
	}
	/**
	* @brief : Return iterator to value, or to the end if not found
	*/
	Iterator Find(const _Value& value)
	{
		Iterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return const iterator to value, or to the end if not found
	*/
	ConstIterator Find(const _Value& value) const
	{
		ConstIterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return whether contains a specific value
	*/
	bool Contains(const _Value& value) const { return Find(value) != End(); }
	/**
	* @brief : Return iterator to the first element
	*/
	Iterator Begin() { return Iterator(Head()); }
	/**
	* @brief : Return iterator to the first element
	*/
	ConstIterator Begin() const { return ConstIterator(Head()); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(Tail()); }
	/**
	* @brief : Return iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(Tail()); }
	/**
	* @brief : Return first element
	*/
	_Value& Front() { return *Begin(); }
	/**
	* @brief : Return const first element
	*/
	const _Value& Front() const { return *Begin(); }
	/**
	* @brief : Return last element
	*/
	_Value& Back() { return *(--End()); }
	/**
	* @brief : Return const last element
	*/
	const _Value& Back() const { return *(--End()); }
	/**
	* @brief : Return number of elements
	*/
	unsigned Size() const { return _size; }
	/**
	* @brief : Return whether list is empty
	*/
	bool Empty() const { return _size == 0; }



private:
	/**
	* @brief : Return the head node
	*/
	Node* Head() const { return static_cast<Node*>(_head); }
	/**
	* @brief : Return the tail node
	*/
	Node* Tail() const { return static_cast<Node*>(_tail); }
	/**
	* @brief : Allocate and insert a node into the list
	*/
	void InsertNode(Node* dest, const _Value& value)
	{
		if (!dest)
			return;

		Node* newNode = ReserveNode(value);
		Node* prev = dest->Prev();
		newNode->next = dest;
		newNode->prev = prev;
		if (prev)
			prev->next = newNode;
		dest->prev = newNode;

		// Reassign the head node if necessary
		if (dest == Head())
			_head = newNode;

		++_size;
	}
	/**
	* @brief : Erase and free a node. Return pointer to the next node, 
	or to the end if could not erase
	*/
	Node* EraseNode(Node* node)
	{
		// The tail node can not be removed
		if (!node || node == _tail)
			return Tail();

		Node* prev = node->Prev();
		Node* next = node->Next();
		if (prev)
			prev->next_ = next;
		next->prev_ = prev;

		// Reassign the head node if necessary
		if (node == Head())
			_head = next;

		FreeNode(node);
		--_size;

		return next;
	}

	/// Reserve a node.
	Node* ReserveNode()
	{
		auto* newNode = static_cast<Node*>(AllocatorReserve(_allocator));
		new(newNode) Node();
		return newNode;
	}

	/// Reserve a node with initial value.
	Node* ReserveNode(const _Value& value)
	{
		auto* newNode = static_cast<Node*>(AllocatorReserve(_allocator));
		new(newNode) Node(value);
		return newNode;
	}

	/// Free a node.
	void FreeNode(Node* node)
	{
		(node)->~Node();
		AllocatorFree(_allocator, node);
	}
};
	
template <typename _Value> typename Detail::tList<_Value>::ConstIterator begin(const Detail::tList<_Value>& v) { return v.Begin(); }

template <typename _Value> typename Detail::tList<_Value>::ConstIterator end(const Detail::tList<_Value>& v) { return v.End(); }

template <typename _Value> typename Detail::tList<_Value>::Iterator begin(Detail::tList<_Value>& v) { return v.Begin(); }

template <typename _Value> typename Detail::tList<_Value>::Iterator end(Detail::tList<_Value>& v) { return v.End(); }


}
}

#endif //!KH_STL_TYPE_LIST_H_
