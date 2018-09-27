#ifndef KH_STL_TYPE_ARRAY_H_
#define KH_STL_TYPE_ARRAY_H_
#include "TypeIterator.h"

#include <initializer_list>

#include <iostream>

namespace KhSTL {


template <typename _Value,unsigned _Max> class tArray 
{
public:
	using ValueType = _Value;
	using Iterator = tIterator<_Value>;
	using ConstIterator = tConstIterator<_Value>;
public:
	/**
	* @brief : Construct empty
	*/
	tArray() noexcept
		: _max(_Max)
		, _elems(new _Value[_Max])
	{}
	/**
	* @brief :
	*/
	tArray(std::initializer_list<_Value> list)
		: tArray()
		, _max(_Max)
		, _elems(new _Value[_Max])
	{
		assert(list.size() <= _max);
		unsigned i = 0;
		for (auto it = list.begin(); it != list.end(); it++)
		{
			_elems[i++] = *it;
		}
	}
	/**
	* @brief : Destruct
	*/
	~tArray()
	{
		destructElements();
		delete[] _elems;
	}
	/**
	* @brief : Return element at index
	*/
	_Value& operator [](unsigned index)
	{
		assert(index >= 0 && index <= _Max - 1);

		return _elems[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const _Value& operator [](unsigned index) const
	{
		assert(index >= 0 && index <= _Max - 1);
		return _elems[index];
	}
	/**
	* @brief : Return array max length
	*/
	constexpr unsigned Size() const noexcept
	{	// return length of sequence
		return (_Max);
	}
	/**
	* @brief : Test array is enpty
	*/
	constexpr bool Empty() const noexcept
	{	
		return _Max == 0;
	}
	/**
	* @brief : Return element at index
	*/
	_Value& At(unsigned index)
	{
		assert(index < _Max);
		return _elems[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const _Value& At(unsigned index) const
	{
		assert(index < _Max);
		return _elems[index];
	}
	/**
	* @brief : Return first element of mutable sequence
	*/
	_Value& front() noexcept 
	{	// 
		return (_elems[0]);
	}
	/**
	* @brief : Return first const element of mutable sequence
	*/
	constexpr const _Value& Front() const noexcept 
	{
		return (_elems[0]);
	}
	/**
	* @brief : Return last element of mutable sequence
	*/
	_Value& Back() noexcept
	{
		return (_elems[_Max - 1]);
	}
	/**
	* @brief : Return const last element of mutable sequence
	*/
	constexpr const _Value& Back() const noexcept 
	{
		return (_elems[_Max - 1]);
	}
	/**
	* @brief : Return pointer to mutable data array
	*/
	_Value* Data() noexcept
	{	
		return (_elems);
	}
	/**
	* @brief : return const pointer to nonmutable data array
	*/
	const _Value* Data() const noexcept
	{	// 
		return (_elems);
	}
	/**
	* @brief : Return iterator to the beginning
	*/
	Iterator Begin() { return Iterator(_elems); }
	/**
	* @brief : Return const iterator to the beginning
	*/
	ConstIterator Begin() const { return ConstIterator(_elems); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(_elems + _Max); }
	/**
	* @brief : Return const iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(_elems + _Max); }
	/**
	* @brief : Swap with another vector
	*/
	void Swap(tArray& rhs)
	{
		KhSTL::Swap(_max, rhs._max);
		KhSTL::Swap(*_elems, *rhs._elems);
	}
private:
	/**
	* @brief : Call the elements' destructors
	*/
	void destructElements()
	{
		while (_max--)
		{
			delete _elems[_max];
		}
	}
	/// Size of vector.
	unsigned _max;
	/// Value array
	_Value* _elems;
};



}
#endif //!KH_STL_TYPE_ARRAY_H_