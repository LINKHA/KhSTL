#ifndef KH_STL_TYPE_QUEUE_H_
#define KH_STL_TYPE_QUEUE_H_

#include "../Deque/TypeDeque.h"

namespace KhSTL {


template<typename _Ty
	,typename _Container = tDeque<_Ty>>
class tQueue
{
public:
	void Push(value_type&& _Val)
	{	// insert element at beginning
		_container.PushBack(_Val);
	}

	template<class... _Valty>
	decltype(auto) emplace(_Valty&&... _Val)
	{	// insert element at beginning
		_container.emplace_back(std::forward<_Valty>(_Val)...);
	}

	bool Empty() const
	{	// test if queue is empty
		return _container.Empty();
	}

	unsigned Size() const
	{	// return length of queue
		return _container.Size();
	}

	_Ty& Front()
	{	// return first element of mutable queue
		return _container.Front();
	}

	const _Ty& Front() const
	{	// return first element of nonmutable queue
		return _container.Front();
	}

	_Ty& Back()
	{	// return last element of mutable queue
		return _container.Back();
	}

	const _Ty& Back() const
	{	// return last element of nonmutable queue
		return _container.Back();
	}

	void Push(const _Ty& value)
	{	// insert element at beginning
		_container.PushBack(value);
	}

	void Pop()
	{	// erase element at end
		_container.PopFront();
	}

	const _Container& GetContainer() const
	{	// get reference to container
		return _container;
	}

	void swap(tQueue& rhs)
	{	// exchange contents with _Right
		//_Swap_adl(_container, _Right.c);
	}

protected:
	_Container _container;	// the underlying container
};


}

#endif // !KH_STL_TYPE_QUEUE_H_