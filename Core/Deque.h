#pragma once
#pragma once
#include "Allocator.h"

namespace KhSTL {

template <typename _Ty, unsigned _Size>
	class DequeValue
{
public:
	using MapPoint = _Ty**;
	using Iterator = DequeIterator<_Ty, _Size>;
	using ConstIterator = DequeConstIterator<_Ty, _Size>;

public:

	DequeValue()
		: _start()
		, _finish()
		, _map(0)
		, _mapSize(0)
	{

	}

	virtual ~DequeValue()
	{

	}

protected:

	/// Control center
	MapPoint _map;
	unsigned _mapSize;

	Iterator _start;
	Iterator _finish;


};



template <typename _Ty
	, unsigned _Size
	, typename _Alloc>
	class DequeAlloc : public DequeValue <_Ty, _Size>
{
public:
	using ValueType = _Ty;
	using Ptr = _Ty * ;
	using MapPoint = _Ty * *;
	using Value = DequeValue <_Ty, _Size>;
	using This = DequeAlloc<_Ty, _Size, _Alloc>;
	using Base = DequeValue <_Ty, _Size>;
	using Iterator = typename Value::Iterator;
	using ConstIterator = typename Value::ConstIterator;
	using AllocType = typename _Alloc::ValueType;
public:
	DequeAlloc()
	{}
	virtual ~DequeAlloc()
	{}
protected:
	/**
	* @brief : Back-up when a buffer overflows
	*/
	void pushBackAux(const _Ty& value)
	{
		_Ty val = value;
		*(Value::_finish.node + 1) = allocateNode();
		//construct(Value::_finish.cur, val);
		new (Value::_finish.cur)_Ty(val);
		Value::_finish.SetNode(Value::_finish.node + 1);
		Value::_finish.cur = Value::_finish.first;
	}
	/**
	* @brief : Forward interpolation when a buffer overflows
	*/
	void pushFrontAux(const _Ty& value)
	{
		_Ty val = value;
		*(Value::_start.node - 1) = allocateNode();
		Value::_start.SetNode(Value::_start.node - 1);
		Value::_start.cur = Value::_start.last - 1;
		//construct(Value::_start.cur, val);
		new (Value::_start.cur)_Ty(val);
	}
	/**
	* @brief : Delete after buffer overflow
	*/
	void popBackAux()
	{
		freeNode(Value::_finish.first);
		Value::_finish.SetNode(Value::_finish.node - 1);
		Value::_finish.cur = Value::_finish.last - 1;
		//destroy(Value::_finish.cur);
		freeNode(Value::_finish.cur);
	}

	/**
	* @brief : Delete before buffer overflow
	*/
	void popFrontAux()
	{
		//destroy(Value::_start.cur);
		freeNode(Value::_finish.cur);
		freeNode(Value::_start.first);
		Value::_start.SetNode(Value::_start.node + 1);
		Value::_start.cur = Value::_start.first;
	}
	/**
	* @brief : Replication function
	*/
	void * __cdecl memmove(void * dst, const void * src, size_t count)
	{
		void * ret = dst;
		if (dst <= src || (char *)dst >= ((char *)src + count))
		{
			// If the dst and src regions do not overlap, 
			// copy one by one from the beginning
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst + 1;
				src = (char *)src + 1;
			}
		}
		else
		{
			// If the dst and src regions cross, you copy from the tail to 
			// the start position to avoid data conflicts
			dst = (char *)dst + count - 1;
			src = (char *)src + count - 1;
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst - 1;
				src = (char *)src - 1;
			}
		}
		return(ret);
	}
	int bufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Ty) < 512 ? int(512 / sizeof(_Ty)) : int(1));
	}
	/**
	* @brief : Various initialization
	*/
	void fillInitialize(unsigned num, const _Ty& value)
	{
		createMapAndNodes(num);
		MapPoint cur;
		for (cur = Value::_start.node; cur < Value::_finish.node; ++cur)
		{
			std::uninitialized_fill(*cur, *cur + bufferSize(), value);
		}
		std::uninitialized_fill(Value::_finish.first, Value::_finish.cur, value);
	}
	/**
	* @brief : Initialize the buffer size managed by each node in the (map), control center
	*/
	void createMapAndNodes(unsigned numElements)
	{
		unsigned numNodes = numElements / bufferSize() + 1;
		Value::_mapSize = std::max(initialMapSize(), numNodes + 2);
		Value::_map = allocateMap(Value::_mapSize);//allocateMap problem
		MapPoint nstart = Value::_map + (Value::_mapSize - numNodes) / 2;
		MapPoint nfinish = nstart + numNodes - 1;
		MapPoint cur;
		for (cur = nstart; cur <= nfinish; ++cur)
		{
			*cur = allocateNode();
		}
		Value::_start.SetNode(nstart);
		Value::_finish.SetNode(nfinish);
		Value::_start.cur = Value::_start.first;
		Value::_finish.cur = Value::_finish.first + numElements % bufferSize();
	}
	/**
	* @brief : Minimum number of (map) nodes in Control and Control Center
	*/
	unsigned initialMapSize() { return (unsigned)8; }

	/**
	* @brief : Release the buffer for the control center ( map ) node
	*/
	void freeNode(_Ty* node)
	{
		_allocator.Deallocate(node);
	}


	_Ty* allocate(unsigned n)
	{
		std::set_new_handler(0);
		_Ty* tmp = (_Ty*)(::operator new((unsigned)(n * sizeof(_Ty))));
		if (tmp == 0)
		{
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}
	/**
	* @brief : Configure the buffer size of each node in the control center (map)
	*/
	_Ty* allocateNode()
	{
		return (_Ty*)allocate(bufferSize());
	}

	/**
	* @brief : Configure the buffer size of each node in the control center (map)
	*/
	_Ty** allocateMap(unsigned n)
	{
		return (_Ty**)allocate(n * sizeof(_Ty*));
	}

private:
	AllocType* reserve()
	{
		return _allocator.Reserve();
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	AllocType* reserve(const AllocType& object)
	{
		return _allocator.Reserve(object);
	}
	/**
	* @brief : Destruct and free an object
	*/
	void free(AllocType* object)
	{
		_allocator.Free(object);
	}

	void* allocation()
	{
		return _allocator.Allocation();
	}
protected:
	_Alloc _allocator;
};





template<class _Ty
	, unsigned _Size>
	struct DequeIterator
{
public:
	using ValueType = _Ty;
	//using DifferenceType = ptrdiff_t;
	using This = DequeIterator;
	using Iterator = DequeIterator<_Ty, _Size>;
public:


	/**
	* @brief : Transfer buffer position
	*/
	void SetNode(_Ty** newNode)
	{
		node = newNode;
		first = *newNode;
		last = first + BufferSize();
	}

	unsigned BufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Ty) < 512 ? unsigned(512 / sizeof(_Size)) : unsigned(1));
	}

	_Ty& operator *() const { return *cur; }
	_Ty* operator ->()const { return &(operator *()); }

	This& operator ++()
	{
		++cur;

		if (cur == last)
		{
			SetNode(node + 1);
			cur = first;
		}
		return *this;
	}

	This& operator ++(int)
	{
		This it = *this;
		++*this;
		return it;
	}

	This& operator --()
	{
		if (cur == first)
		{
			SetNode(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}

	This& operator --(int)
	{
		This it = *this;
		--*this;
		return it;
	}

	This& operator +=(int n)
	{
		int offset = n + (cur - first);

		if (offset >= 0 && offset < BufferSize())
		{
			cur += n;
		}
		else
		{
			int nodeOffset = offset > 0
				? offset / BufferSize()
				: -int((-offset - 1) / BufferSize()) - 1;
			SetNode(node + nodeOffset);
			cur = first + (offset - nodeOffset * BufferSize());
		}
		return *this;
	}

	This operator +(int n) const
	{
		This it = *this;
		return it += n;
	}

	This& operator -=(int n)
	{
		return *this += -n;
	}

	This operator -(int n) const
	{
		This it = *this;
		return it -= n;
	}

	int operator -(const This& x)
	{
		return int(BufferSize())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	_Ty& operator [](int n)const { return *(*this + n); }

	bool operator ==(const This& x) const
	{
		return cur == x.cur;
	}

	bool operator !=(const This& x) const
	{
		return cur != x.cur;
	}

	bool operator <(const This& x) const
	{
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}


	_Ty* cur;
	_Ty* first;
	_Ty* last;
	_Ty** node;
};


template<class _Ty
	, unsigned _Size>
	struct DequeConstIterator
{
	using ValueType = _Ty;
	//using DifferenceType = ptrdiff_t;
	using This = DequeConstIterator;
	using Iterator = DequeConstIterator<_Ty, _Size>;

	/**
	* @brief : Transfer buffer position
	*/
	void SetNode(_Ty** newNode)
	{
		node = newNode;
		first = *newNode;
		last = first + DifferenceType(BufferSize());
	}

	unsigned BufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Ty) < 512 ? unsigned(512 / sizeof(_Size)) : unsigned(1));
	}

	const _Ty& operator *() const { return *cur; }
	const _Ty* operator ->()const { return &(operator *()); }

	This& operator ++()
	{
		++cur;

		if (cur == last)
		{
			SetNode(node + 1);
			cur = first;
		}
		return *this;
	}

	This& operator ++(int)
	{
		This it = *this;
		++*this;
		return it;
	}

	This& operator --()
	{
		if (cur == first)
		{
			SetNode(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}

	This& operator --(int)
	{
		This it = *this;
		--*this;
		return it;
	}

	This& operator +=(unsigned n)
	{
		unsigned offset = n + (cur - first);

		if (offset >= 0 && offset < unsigned(BufferSize()))
		{
			cur += n;
		}
		else
		{
			unsigned nodeOffset = offset > 0
				? offset / unsigned(BufferSize())
				: -unsigned((-offset - 1) / BufferSize()) - 1;
			SetNode(node + nodeOffset);
			cur = first + (offset - nodeOffset * unsigned(BufferSize()));
		}
		return *this;
	}

	This operator +(unsigned n) const
	{
		This it = *this;
		return it += n;
	}

	This& operator -=(unsigned n)const { return *this += -n; }

	This operator -(unsigned n)const
	{
		This it = *this;
		return it -= n;
	}

	unsigned operator -(const This& x)
	{
		return unsigned(BufferSize())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	_Ty& operator [](unsigned n)const { return *(*this + n); }

	bool operator ==(const This& x) const
	{
		return cur == x.cur;
	}

	bool operator !=(const This& x) const
	{
		return cur != x.cur;
	}

	bool operator <(const This& x) const
	{
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}


	_Ty* cur;
	_Ty* first;
	_Ty* last;
	_Ty** node;
};
template <typename _Ty
	, unsigned _Size = 0
	, typename _Alloc = Allocator<_Ty>>
	class Deque : public DequeAlloc<_Ty, _Size, _Alloc>
{
public:
	/// Value type
	using ValueType = _Ty;
	/// Map poiint is valueType**
	using MapPoint = _Ty**;
	/// DequeAlloc<_Ty, _Size, _Alloc>
	using Base = DequeAlloc<_Ty, _Size, _Alloc>;
	/// Deque<_Ty, _Size, _Alloc>
	using This = Deque<_Ty, _Size, _Alloc>;
	/// DequeAlloc<_Ty, _Size, _Alloc>
	using Alloc = DequeAlloc<_Ty, _Size, _Alloc>;
	/// Data value
	using Value = typename Alloc::Value;
	/// Value iterator
	using Iterator = typename Value::Iterator;
	/// Const value iterator
	using ConstIterator = typename Value::ConstIterator;
	/// Deque reverse iterator
	using ReverseIterator = ReverseIterator<Iterator>;
	/// Deque const reverse iterator
	using ConstReverseIterator = ReverseIterator<ConstIterator>;
public:
	/**
	* @brief : Construct
	*/
	Deque()
	{
		Alloc::fillInitialize(0, 0);
	}
	/**
	* @brief : Construct
	*/
	Deque(int index, const _Ty& value)
	{
		Alloc::fillInitialize(index, value);
	}
	/**
	* @brief : Move-construct from another list
	*/
	explicit Deque(Deque<_Ty, _Size, _Alloc> && deque) noexcept
	{
		Swap(deque);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	Deque(const std::initializer_list<_Ty>& deque)
		: Deque()
	{
		for (auto it = deque.begin(); it != deque.end(); it++)
		{
			PushBack(*it);
		}
	}
	/**
	* @brief : Destroy the deque
	*/
	~Deque()
	{
		Clear();
	}
	/**
	* @brief : Assign by moving rhs
	*/
	This& operator =(const This& rhs)
	{
		if (&rhs != this)
		{
			This copy(rhs);
			Swap(copy);
		}
		return *this;
	}
	/**
	* @brief : Assign by moving rhs
	*/
	This& operator =(This && rhs)
	{	// assign by moving _Right
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign an element
	*/
	This& operator +=(const _Ty& rhs)
	{
		PushBack(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign another vector
	*/
	This& operator +=(const This& rhs)
	{
		PushBack(rhs);
		return *this;
	}
	/**
		* @brief : Add an element
		*/
	This operator +(const _Ty& rhs) const
	{
		This ret(*this);
		ret.PushBack(rhs);
		return ret;
	}
	/**
	* @brief : Add another vector
	*/
	This operator +(const This& rhs) const
	{
		This ret(*this);
		ret.PushBack(rhs);
		return ret;
	}
	/**
	* @brief : Test for equality with another deque
	*/
	bool operator ==(const This& rhs) const
	{
		if (rhs._mapSize != Value::_mapSize)
			return false;

		Iterator buffer = Value::_start;
		Iterator rhsBuffer = rhs._start;
		for (unsigned i = 0; i < Value::_size; ++i)
		{
			if (buffer[i] != rhsBuffer[i])
				return false;
		}

		return true;
	}
	/**
	* @brief : Test for iterator inequality
	*/
	bool operator !=(const This& rhs) const
	{
		if (rhs._mapSize != Value::_mapSize)
			return true;

		Iterator buffer = Value::_start;
		Iterator rhsBuffer = rhs._start;
		for (unsigned i = 0; i < Value::_size; ++i)
		{
			if (*buffer[i] != *rhsBuffer[i])
				return true;
		}

		return false;
	}
	/**
	* @brief : Get the nth element of cghDeque
	*/
	_Ty& operator [](unsigned index)
	{
		return Value::_start[index];
	}
	/**
	* @brief : Get the nth element of cghDeque
	*/
	const _Ty& operator [](unsigned index) const
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
	inline Iterator Begin()
	{
		return Value::_start;
	}
	/**
	* @brief : Get const the head of the cghDeque
	*/
	inline ConstIterator Begin() const noexcept
	{
		return Value::_start;
	}
	/**
	* @brief : Get the tail of the cghDeque
	*/
	inline Iterator End()
	{
		return Value::_finish;
	}
	/**
	* @brief : Get const the tail of the cghDeque
	*/
	inline ConstIterator End() const noexcept
	{
		return Value::_finish;
	}
	inline ReverseIterator RBegin() { return ReverseIterator(End()); }

	inline ConstReverseIterator RBegin() const { return ReverseIterator(End()); }

	inline ReverseIterator REnd() { return ReverseIterator(Begin()); }

	inline ConstReverseIterator REnd() const { return ReverseIterator(Begin()); }

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
	void Resize(unsigned newSize, const _Ty& value)
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
	///**
	//* @brief : Erase an element by iterator. Return iterator to the next element
	//*/
	//Iterator Erase(Iterator it)
	//{
	//	freeNode(*it);

	//	return Iterator();
	//}
	///**
	//* @brief : Erase a range by iterators. Return an iterator to the next element
	//*/
	//Iterator Erase(const Iterator& start, const Iterator& end)
	//{
	//	Iterator it = start;
	//	while (it != end)
	//		it = Erase(it);

	//	return it;
	//}
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
	* @brief : Create an element at the postion
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
			Alloc::freeNode(*node);
		}
		if (Value::_start.node != Value::_finish.node)
		{
			destroy(Value::_start.cur, Value::_start.last);
			destroy(Value::_finish.first, Value::_finish.last);
			Alloc::freeNode(Value::_finish.first);
		}
		else
		{
			destroy(Value::_start.cur, Value::_finish.cur);
		}
		Value::_finish = Value::_start;
	}
	/**
	* @brief : Get the maximum length of the deque
	*/
	unsigned MaxSize() const
	{
		return Value::_finish - Value::_start;
	}
	/**
	* @brief : To determine whether or not to be Empty
	*/
	bool Empty() const
	{
		return Value::_finish == Value::_start;
	}
private:

	template<class _Ty1, class  _Ty2>
	inline void construct(_Ty1* pointer, const _Ty2& value)
	{
		new (pointer)_Ty1(value);
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

};

}