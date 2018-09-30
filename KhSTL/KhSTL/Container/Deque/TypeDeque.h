#ifndef KH_STL_TYPE_DEQUE_H_
#define KH_STL_TYPE_DEQUE_H_

#include <cassert>

#include "TypeDequeBase.h"

#include "../../Allocator/TypeMemory.h"

#include "../../Allocator/TypeConstruct.h"


namespace KhSTL {


template <typename _Ty
	, unsigned _Size = 0
	//, typename _Alloc = tAllocator<_Ty>>
	, typename _Alloc = tmAllocator<_Ty>>
	class tDeque : public tDequeBase<_Ty, _Size,_Alloc>
{
public:
	using ValueType = _Ty;
	using Iterator = tDequeIterator<_Ty, _Size>;
	using ConstIterator = tDequeConstIterator<_Ty, _Size>;
	using MapPoint = _Ty**;
	typedef ptrdiff_t	difference_type;

	typedef simple_alloc<_Ty, _Alloc>		data_allocator; 
	typedef simple_alloc<_Ty*, _Alloc>		map_allocator; 
public:
	/**
	* @brief : Construct
	*/
	tDeque()
		: _start()
		, _finish()
		, _map(0)
		, _mapSize(0)
	{
		fillInitialize(0, 0);
	}
	
	///**
	//* @brief : Construct from another list
	//*/
	//explicit tDeque(const tList<_Ty>& list)
	//{
	//	// Reserve the tail node + initial capacity according to the list's size
	//	_allocator = AllocatorInitialize((unsigned)sizeof(Node), list.Size() + 1);
	//	_head = _tail = ReserveNode();
	//	*this = list;
	//}
	/**
	* @brief : Move-construct from another list
	*/
	explicit tDeque(tDeque<_Ty> && deque) noexcept
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
	* @brief : Construct
	*/
	tDeque(int index, const _Ty& value)
		: _start()
		, _finish()
		, _map(0)
		, _mapSize(0)
	{
		fillInitialize(index, value);
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
		return _start[difference_type(index)];
	}

	
	/**
	* @brief : Subscript mutable sequence with checking
	*/
	_Ty& At(unsigned index)
	{
		assert(_mapSize >= index);
		return (*(Begin() + static_cast<difference_type>(index)));
	}
	/**
	* @brief : Subscript nonmutable sequence with checking
	*/
	const _Ty& At(unsigned index) const
	{
		assert(_mapSize >= index);
		return (*(Begin() + static_cast<difference_type>(index)));
	}
	/**
	* @brief : Gets the value of the header of the cghDeque
	*/
	_Ty& Front()
	{
		return *_start;
	}
	/**
	* @brief : Gets const the value of the header of the cghDeque
	*/
	const _Ty& Front() const 
	{
		return *_start;
	}
	/**
	* @brief : Because the buffer is a closed and open interval, you need a step back
	*			from the finish to get the tail of the cghDeque
	*/
	_Ty& Back()
	{
		Iterator tmp = _finish;
		--tmp;
		return *tmp;
	}
	/**
	* @brief : Because the buffer is a closed and open interval, you need a step back
	*			from the finish to get the tail of the cghDeque
	*/
	const _Ty& Back() const
	{
		Iterator tmp = _finish;
		--tmp;
		return *tmp;
	}
	/**
	* @brief : Get the head of the cghDeque
	*/
	Iterator Begin()
	{ 
		return _start;
	}
	/**
	* @brief : Get const the head of the cghDeque
	*/
	ConstIterator Begin() const noexcept
	{
		return _start;
	}
	/**
	* @brief : Get the tail of the cghDeque
	*/
	Iterator End()
	{ 
		return _finish;
	}
	/**
	* @brief : Get const the tail of the cghDeque
	*/
	ConstIterator End() const noexcept
	{
		return _finish;
	}
	
	/**
	* @brief : Return deque size
	*/
	unsigned Size()
	{
		return _finish - _start;
	}
	/**
	* @brief : Determine new length, padding as needed
	*/
	void Resize(unsigned newSize)
	{	
		while (_mapSize < newSize)
		{
			EmplaceBack();
		}

		while (newSize < _mapSize)
		{
			PopBack();
		}
	}
	/**
	* @brief : Determine new length, padding as needed
	*/
	void Resize(unsigned newSize,const _Ty& value)
	{
		while (_mapSize < newSize)
		{
			PushBack(value);
		}

		while (newSize < _mapSize)
		{
			PopBack();
		}
	}
	/**
	* @brief : Get the maximum length of the deque
	*/
	unsigned MaxSize() const 
	{ 
		return _finish - _start;
	}
	/**
	* @brief : To determine whether or not to be empty
	*/
	bool Empty() const 
	{ 
		return _finish == _start; 
	}
	/**
	* @brief : Add an element at the end
	*/
	void PushBack(const _Ty& value)
	{
		if (_finish.cur != _finish.last - 1)
		{
			construct(_finish.cur, value);
			++_finish.cur;
		}
		else
		{
			pushBackAux(value);
		}
	}
	/**
	* @brief : Add an element at the front
	*/
	void PushFront(const _Ty& value)
	{
		if (_start.cur != _start.first)
		{
			construct(_start.cur - 1, value);
			--_start.cur;
		}
		else
		{
			pushFrontAux(value);
		}
	}
	/**
	* @brief : Eject elements from the tail of the deque
	*/
	void PopBack()
	{
		if (_finish.cur != _finish.first)
		{
			destroy(_finish.cur);
			--_finish.cur;
		}
		else
		{
			popBackAux();
		}
	}
	/**
	* @brief : Eject elements from the cghDeque header
	*/
	void PopFront()
	{
		if (_start.cur != _start.last - 1)
		{
			destroy(_start.cur);
			++_start.cur;
		}
		else
		{
			popFrontAux();
		}
	}
	/**
	* @brief : Insert an element to a specified location
	*/
	Iterator Insert(Iterator position, const _Ty& value)
	{
		return (Emplace(position, std::move(value)));
	}
	/**
	* @brief : Create an element at the beginning
	*/
	template<typename... _TyArg> 
		_Ty& EmplaceFront(_TyArg&&... args)
	{	
		if (_start.cur != _start.first)
		{
			// Optimize common case
			--_start->cur;
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
		if (_finish.cur != _finish.last - 1)
		{
			// Optimize common case
			++_finish->cur;
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
		difference_type index = pos - _start;


		if (index <= Size() / 2)
		{
			EmplaceFront(std::forward<_TyArg>(args)...);
			std::rotate(Begin(), Begin() + 1, Begin() + static_cast<difference_type>(1 + index));
		}
		else
		{
			EmplaceBack(std::forward<_TyArg>(args)...);
			std::rotate(Begin() + static_cast<difference_type>(index), End() - 1, End());
		}
		return (Begin() + static_cast<difference_type>(index));
	}
	
	/**
	* @brief : Clear all elements of cghDeque
	*/
	void Clear()
	{
		for (MapPoint node = _start.node + 1; node < _finish.node; ++node)
		{
			destroy(*node, *node + bufferSize());
			data_allocator::deallocate(*node, bufferSize());
		}
		if (_start.node != _finish.node)
		{
			destroy(_start.cur, _start.last);
			destroy(_finish.first, _finish.last);
			data_allocator::deallocate(_finish.first, bufferSize());
		}
		else 
		{
			destroy(_start.cur, _finish.cur);
		}
		_finish = _start; 
	}
	


protected:
	/**
	* @brief : Back-up when a buffer overflows
	*/
	void pushBackAux(const _Ty& value)
	{
		_Ty val = value;
		*(_finish.node + 1) = allocateNode(); 
		construct(_finish.cur, val); 
		_finish.SetNode(_finish.node + 1); 
		_finish.cur = _finish.first; 
	}
	/**
	* @brief : Forward interpolation when a buffer overflows
	*/
	void pushFrontAux(const _Ty& value)
	{
		_Ty val = value;
		*(_start.node - 1) = allocateNode(); 
		_start.SetNode(_start.node - 1); 
		_start.cur = _start.last - 1; 
		construct(_start.cur, val); 
	}
	/**
	* @brief : Delete after buffer overflow
	*/
	void popBackAux()
	{
		deallocateNode(_finish.first); 
		_finish.SetNode(_finish.node - 1); 
		_finish.cur = _finish.last - 1; 
		destroy(_finish.cur); 
	}

	/**
	* @brief : Delete before buffer overflow
	*/
	void popFrontAux()
	{
		destroy(_start.cur);
		deallocateNode(_start.first);
		_start.SetNode(_start.node + 1);
		_start.cur = _start.first;
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
	size_t bufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Ty) < 512 ? size_t(512 / sizeof(_Ty)) : size_t(1));
	}
	/**
	* @brief : Various initialization
	*/
	void fillInitialize(unsigned num, const _Ty& value)
	{
		createMapAndNodes(num);
		MapPoint cur;
		for (cur = _start.node; cur < _finish.node; ++cur)
		{
			std::uninitialized_fill(*cur, *cur + bufferSize(), value);
		}
		std::uninitialized_fill(_finish.first, _finish.cur, value);
	}
	/**
	* @brief : Initialize the buffer size managed by each node in the (map), control center
	*/
	void createMapAndNodes(unsigned numElements)
	{
		unsigned numNodes = numElements / bufferSize() + 1;
		_mapSize = std::max(initialMapSize(), numNodes + 2);
		_map = map_allocator::allocate(_mapSize);
		MapPoint nstart = _map + (_mapSize - numNodes) / 2;
		MapPoint nfinish = nstart + numNodes - 1;
		MapPoint cur;
		for (cur = nstart; cur <= nfinish; ++cur)
		{
			*cur = allocateNode(); 
		}
		_start.SetNode(nstart); 
		_finish.SetNode(nfinish); 
		_start.cur = _start.first; 
		_finish.cur = _finish.first + numElements % bufferSize(); 
	}
	/**
	* @brief : Minimum number of (map) nodes in Control and Control Center
	*/
	unsigned initialMapSize() { return (unsigned)8; }
	/**
	* @brief : Configure the buffer size of each node in the control center (map)
	*/
	_Ty* allocateNode()
	{
		return data_allocator::allocate(bufferSize() / sizeof(_Ty));
	}
	/**
	* @brief : Release the buffer for the control center ( map ) node
	*/
	void deallocateNode(void* node)
	{
		data_allocator::deallocate(node);
	}

	

	
private:
	Iterator _start;
	Iterator _finish;
	/// Control center
	MapPoint _map; 
	unsigned _mapSize;
};


}
#endif //!KH_STL_TYPE_DEQUE_H_