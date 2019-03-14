#pragma once
#include "Deque.h"

namespace KhSTL {


template<typename _Ty
	, typename _Container = Deque<_Ty>>
	class Stack
{
public:
	/// Value type
	using ValueType = _Ty;
public:
	Stack()
		:_container()
	{}

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
	void Push(const _Ty& value)
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
	* @brief : Insert element at beginning
	*/
	template<typename... _TyArg>
	_Ty Emplace(_TyArg&&... value)
	{	// insert element at beginning
		_container.EmplaceBack(std::forward<_TyArg>(value)...);
	}
	/**
	* @brief : Get reference to container
	*/
	const _Ty& GetContainer() const
	{
		return _container;
	}

	/**
	* @brief : Test if stack is Empty
	*/
	bool Empty() const
	{
		return (_container.Empty());
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