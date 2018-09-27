#ifndef KH_STL_TYPE_LINKED_LIST_H_
#define KH_STL_TYPE_LINKED_LIST_H_

#include <initializer_list>

namespace KhSTL {

struct tLinkedListNode
{
	/**
	* @brief :Construct
	*/
	tLinkedListNode()
		: next(nullptr)
	{}

	/// Pointer to next node
	tLinkedListNode* next;
};

template <typename _Value> class tLinkedList
{
public:
	tLinkedList()
		: _head(nullptr)
	{}
	/**
	* @brief : Non-copyable
	*/
	tLinkedList(const tLinkedList<_Value>& list) = delete;
	/**
	* @brief : Aggregate initialization constructor
	*/
	tLinkedList(const std::initializer_list<_Value>& list)
		: tLinkedList()
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			Insert(*it);
		}
	}
	/**
	* @brief : Non-assignable
	*/
	tLinkedList<_Value>& operator =(const tLinkedList<_Value>& list) = delete;
	/**
	*@brief : Destruc
	*/
	~tLinkedList()
	{
		Clear();
	}
	/**
	* @brief : Remove all elements
	*/
	void Clear()
	{
		_Value* element = _head;
		while (element)
		{
			_Value* next = Next(element);
			delete element;
			element = next;
		}
		_head = nullptr;
	}
	/**
	* @brief : Insert an element at the beginning
	*/
	void InsertFront(_Value* element)
	{
		if (element)
		{
			element->next = _head;
			_head = element;
		}
	}
	/**
	* @brief : Insert an element at the end
	*/
	void Insert(_Value* element)
	{
		if (_head)
		{
			_Value* tail = Last();
			element->next = tail->next;
			tail->next = element;
		}
		else
		{
			element->next = _head;
			_head = element;
		}
	}
	/**
	* @brief : Erase an element. Return true if successful
	*/
	bool Erase(_Value* element)
	{
		if (element && _head)
		{
			if (element == _head)
			{
				_head = Next(element);
				delete element;
				return true;
			}
			else
			{
				_Value* tail = _head;
				while (tail && tail->next != element)
					tail = Next(tail);
				if (tail)
				{
					tail->next = element->next;
					delete element;
					return true;
				}
			}
		}

		return false;
	}
	/**
	* @brief : Erase an element when the previous element is known (optimization.)
	*			Return true if successful
	*/
	bool Erase(_Value* element, _Value* previous)
	{
		if (previous && previous->next == element)
		{
			previous->next = element->next;
			delete element;
			return true;
		}
		else if (!previous)
		{
			if (_head == element)
			{
				_head = Next(element);
				delete element;
				return true;
			}
		}

		return false;
	}
	/**
	* @brief : Return first element, or null if empty
	*/
	_Value* First() const { return _head; }
	/**
	* @brief : Return last element, or null if empty
	*/
	_Value* Last() const
	{
		_Value* element = _head;
		if (element)
		{
			while (element->next)
				element = Next(element);
		}
		return element;
	}
	/**
	* @brief : Return next element, or null if no more elements
	*/
	_Value* Next(_Value* element) const { return element ? static_cast<_Value*>(element->next) : nullptr; }
	/**
	* @brief : Return whether is empty
	*/
	bool Empty() const { return _head == nullptr; }

private:
	/// First element
	_Value* _head;
};


}
#endif //!KH_STL_TYPE_LINKED_LIST_H_