#ifndef KH_STL_TYPE_DEQUE_H_
#define KH_STL_TYPE_DEQUE_H_

#include "TypeDequeAllocator.h"

namespace KhSTL {

	template<class T1, class  T2>
	inline void construct(T1* p, const T2& value)
	{
		new (p)T1(value);
	}

	template<typename T>
	inline void destroy(T* pointer)
	{
		pointer->~T();
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		for (; first < last; ++first)
			destroy(&*first);
	}

template <typename _Ty
	, unsigned _Size = 0
	, typename _Alloc = tAllocator<_Ty>>
	class tDeque : public tDequeAlloc<_Ty, _Size, _Alloc>
{
public:
	///Value type
	using ValueType = _Ty;
	///Map poiint is valueType**
	using MapPoint = _Ty**;
	///Base class
	using Base = tDequeAlloc<_Ty, _Size, _Alloc>;
	///This class
	using This = tDeque<_Ty, _Size, _Alloc>;
	///Alloc class
	using Alloc = tDequeAlloc<_Ty, _Size, _Alloc>;
	///Data value
	using Value = typename Alloc::Value; //tDequeValue <_Ty, _Size>
	///Value iterator
	using Iterator = typename Value::Iterator;
	///Const value iterator
	using ConstIterator = typename Value::ConstIterator;

public:
	/**
	* @brief : Construct
	*/
	tDeque()
	{
		Alloc::fillInitialize(0, 0);
	}
	/**
	* @brief : Construct
	*/
	tDeque(int index, const _Ty& value)
	{
		Alloc::fillInitialize(index, value);
	}
	/**
	* @brief : Move-construct from another list
	*/
	explicit tDeque(tDeque<_Ty, _Size, _Alloc> && deque) noexcept
	{
		Swap(deque);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tDeque(const std::initializer_list<_Ty>& deque)
		: tDeque()
	{
		for (auto it = deque.begin(); it != deque.end(); it++)
		{
			PushBack(*it);
		}
	}

	/**
	* @brief : Destroy the deque
	*/
	~tDeque() 
	{}
	/**
	* @brief : Get the nth element of cghDeque
	*/
	_Ty& operator [](unsigned index)
	{
		return Value::_start[index];
	}

	
	/**
	* @brief : Subscript mutable sequence with checking
	*/
	_Ty& At(unsigned index)
	{
		assert(Value::_mapSize >= index);
		return (*(Begin() + index));
	}
	/**
	* @brief : Subscript nonmutable sequence with checking
	*/
	const _Ty& At(unsigned index) const
	{
		assert(Value::_mapSize >= index);
		return (*(Begin() + index));
	}
	/**
	* @brief : Gets the value of the _header of the cghDeque
	*/
	_Ty& Front()
	{
		return *Value::_start;
	}
	/**
	* @brief : Gets const the value of the _header of the cghDeque
	*/
	const _Ty& Front() const 
	{
		return *Value::_start;
	}
	/**
	* @brief : Because the buffer is a closed and open interval, you need a step back
	*			from the finish to get the tail of the cghDeque
	*/
	_Ty& Back()
	{
		Iterator tmp = Value::_finish;
		--tmp;
		return *tmp;
	}
	/**
	* @brief : Because the buffer is a closed and open interval, you need a step back
	*			from the finish to get the tail of the cghDeque
	*/
	const _Ty& Back() const
	{
		Iterator tmp = Value::_finish;
		--tmp;
		return *tmp;
	}
	/**
	* @brief : Get the head of the cghDeque
	*/
	Iterator Begin()
	{ 
		return Value::_start;
	}
	/**
	* @brief : Get const the head of the cghDeque
	*/
	ConstIterator Begin() const noexcept
	{
		return Value::_start;
	}
	/**
	* @brief : Get the tail of the cghDeque
	*/
	Iterator End()
	{ 
		return Value::_finish;
	}
	/**
	* @brief : Get const the tail of the cghDeque
	*/
	ConstIterator End() const noexcept
	{
		return Value::_finish;
	}
	
	/**
	* @brief : Return deque size
	*/
	unsigned Size()
	{
		return Value::_finish - Value::_start;
	}
	/**
	* @brief : Determine new length, padding as needed
	*/
	void Resize(unsigned newSize)
	{	
		while (Value::_mapSize < newSize)
		{
			EmplaceBack();
		}

		while (newSize < Value::_mapSize)
		{
			PopBack();
		}
	}
	/**
	* @brief : Determine new length, padding as needed
	*/
	void Resize(unsigned newSize,const _Ty& value)
	{
		while (Value::_mapSize < newSize)
		{
			PushBack(value);
		}

		while (newSize < Value::_mapSize)
		{
			PopBack();
		}
	}
	/**
	* @brief : Get the maximum length of the deque
	*/
	unsigned MaxSize() const 
	{ 
		return Value::_finish - Value::_start;
	}
	/**
	* @brief : To determine whether or not to be empty
	*/
	bool Empty() const 
	{ 
		return Value::_finish == Value::_start;
	}
	/**
	* @brief : Add an element at the end
	*/
	void PushBack(const _Ty& value)
	{
		if (Value::_finish.cur != Value::_finish.last - 1)
		{
			construct(Value::_finish.cur, value);
			++Value::_finish.cur;
		}
		else
		{
			Alloc::pushBackAux(value);
		}
	}
	/**
	* @brief : Add an element at the front
	*/
	void PushFront(const _Ty& value)
	{
		if (Value::_start.cur != Value::_start.first)
		{
			construct(Value::_start.cur - 1, value);
			--Value::_start.cur;
		}
		else
		{
			Alloc::pushFrontAux(value);
		}
	}
	/**
	* @brief : Eject elements from the tail of the deque
	*/
	void PopBack()
	{
		if (Value::_finish.cur != Value::_finish.first)
		{
			destroy(Value::_finish.cur);
			--Value::_finish.cur;
		}
		else
		{
			Alloc::popBackAux();
		}
	}
	/**
	* @brief : Eject elements from the cghDeque _header
	*/
	void PopFront()
	{
		if (Value::_start.cur != Value::_start.last - 1)
		{
			destroy(Value::_start.cur);
			++Value::_start.cur;
		}
		else
		{
			Alloc::popFrontAux();
		}
	}
	/**
	* @brief : Insert an element to a cosnt specified location
	*/
	Iterator Insert(ConstIterator position, const _Ty& value)
	{
		return Emplace(position, std::move(value));
	}

	/**
	* @brief : Create an element at the beginning
	*/
	template<typename... _TyArg> 
		_Ty& EmplaceFront(_TyArg&&... args)
	{	
		if (Value::_start.cur != Value::_start.first)
		{
			// Optimize common case
			--Value::_start.cur;
			new (&Front()) _Ty(std::forward<_TyArg>(args)...);
		}
		else
		{
			_Ty value(std::forward<_TyArg>(args)...);
			PushFront(std::move(value));
	}
		return Front();
	}
	/**
	* @brief : Create an element at the end
	*/
	template <typename... _TyArg> 
		_Ty& EmplaceBack(_TyArg&&... args)
	{
		if (Value::_finish.cur != Value::_finish.last - 1)
		{
			// Optimize common case
			++Value::_finish.cur;
			new (&Back()) _Ty(std::forward<_TyArg>(args)...);
		}
		else
		{
			_Ty value(std::forward<_TyArg>(args)...);
			PushBack(std::move(value));
		}
		return Back();
	}
	/**
	* @brief :
	*/
	template<class... _TyArg>
	Iterator Emplace(ConstIterator pos, _TyArg&&... args)
	{
		unsigned index = pos - Value::_start;


		if (index <= Size() / 2)
		{
			EmplaceFront(std::forward<_TyArg>(args)...);
			std::rotate(Begin(), Begin() + 1, Begin() + 1 + index);
		}
		else
		{
			EmplaceBack(std::forward<_TyArg>(args)...);
			std::rotate(Begin() + index, End() - 1, End());
		}
		return Begin() + index;
	}
	/**
	* @brief : Clear all elements of deque
	*/
	void Clear()
	{
		for (MapPoint node = Value::_start.node + 1; node < Value::_finish.node; ++node)
		{
			destroy(*node, *node + Alloc::bufferSize());
			//Alloc::deallocData(*node, Alloc::bufferSize());
			Alloc::freeNode(*node);
		}
		if (Value::_start.node != Value::_finish.node)
		{
			destroy(Value::_start.cur, Value::_start.last);
			destroy(Value::_finish.first, Value::_finish.last);
			//Alloc::deallocData(Value::_finish.first, Alloc::bufferSize());
			Alloc::freeNode(Value::_finish.first);
		}
		else 
		{
			destroy(Value::_start.cur, Value::_finish.cur);
		}
		Value::_finish = Value::_start; 
	}

};


}
#endif //!KH_STL_TYPE_DEQUE_H_