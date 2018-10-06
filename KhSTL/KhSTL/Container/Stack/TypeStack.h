#ifndef KH_STL_TYPE_STACK_H_
#define KH_STL_TYPE_STACK_H_

#include "../Deque/TypeDeque.h"

namespace KhSTL {


template<typename _Ty
	, typename _Container = tDeque<_Ty>>
class tStack
{
public:

	/**
	* @brief : Insert element at beginning
	*/
	void Push(_Ty && value)
	{	
		_container.PushBack(std::move(value));
	}
	/**
	* @brief : Insert element at end
	*/
	void Push(const value_type& value)
	{
		_container.PushBack(value);
	}
	/**
	* @brief : Erase last element
	*/
	void Pop()
	{
		_container.PopBack();
	}
	/**
	* @brief : Get reference to container
	*/
	const _Container& GetContainer() const
	{
		return _container;
	}

	/**
	* @brief : Insert element at beginning
	*/
	template<class... _Valty>
	decltype(auto) Emplace(_Valty&&... _Val)
	{	
		_container.EmplaceBack(_STD forward<_Valty>(_Val)...);
	}
	/**
	* @brief : Test if stack is empty
	*/
	bool Empty() const
	{	
		return (_container.empty());
	}
	/**
	* @brief : Test length of stack
	*/
	unsigned Size() const
	{
		return _container.Size();
	}
	/**
	* @brief : Return last element of mutable stack
	*/
	_Ty& Top()
	{
		return _container.Back();
	}
	/**
	* @brief : Return last element of nonmutable stack
	*/
	const _Ty& top() const
	{
		return _container.Back();
	}


protected:
	_Container _container;
};


}

#endif // !KH_STL_TYPE_STACK_H_