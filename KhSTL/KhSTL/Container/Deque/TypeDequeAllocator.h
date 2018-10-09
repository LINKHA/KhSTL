#ifndef KH_STL_TYPE_DEQUE_ALLOCATOR_H_
#define KH_STL_TYPE_DEQUE_ALLOCATOR_H_

#include "TypeDequeValue.h"
#include <algorithm>
#include "../../Allocator/TypeAllocator.h"



namespace KhSTL {

template<typename _Ty>
inline _Ty* __allocate(unsigned size, _Ty*)
{
	std::set_new_handler(0);
	_Ty* tmp = (_Ty*)(::operator new((unsigned)(size * sizeof(_Ty))));
	if (tmp == 0)
	{
		std::cerr << "out of memory" << std::endl;
		exit(1);
	}
	return tmp;
}

template<class T>
inline void __deallocate(T* buffer)
{
	::operator delete(buffer);
}

template<class T1, class  T2>
inline void __construct(T1* p, const T2& value)
{
	new(p)T1(value);
}

template<class T>
inline void __destroy(T* ptr)
{
	ptr->~T();
}


template <typename _Ty
	, unsigned _Size
	, typename _Alloc>
class tDequeAlloc : public tDequeValue <_Ty, _Size>
{
public:
	using ValueType = _Ty;
	using Ptr = _Ty*;
	using MapPoint = _Ty**;
	using Value = tDequeValue <_Ty, _Size>;
	using This = tDequeAlloc<_Ty, _Size, _Alloc>;
	using Base = tDequeValue <_Ty, _Size>;
	using Iterator = typename Value::Iterator;
	using ConstIterator = typename Value::ConstIterator;
public:
	tDequeAlloc() {}
	~tDequeAlloc() {}

	template <typename T1, typename T2>
	inline void construct(T1* p, const T2& value)
	{
		new (p)T1(value);
	}
protected:
	/**
	* @brief : Back-up when a buffer overflows
	*/
	void pushBackAux(const _Ty& value)
	{
		_Ty val = value;
		*(Value::_finish.node + 1) = allocateNode();
		construct(Value::_finish.cur, val);
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
		construct(Value::_start.cur, val);
	}
	/**
	* @brief : Delete after buffer overflow
	*/
	void popBackAux()
	{
		deallocateNode(Value::_finish.first);
		Value::_finish.SetNode(Value::_finish.node - 1);
		Value::_finish.cur = Value::_finish.last - 1;
		destroy(Value::_finish.cur);
	}

	/**
	* @brief : Delete before buffer overflow
	*/
	void popFrontAux()
	{
		destroy(Value::_start.cur);
		deallocateNode(Value::_start.first);
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
	unsigned bufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Ty) < 512 ? unsigned(512 / sizeof(_Ty)) : unsigned(1));
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
		Value::_map = allocateMap(Value::_mapSize);
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
	* @brief : Configure the buffer size of each node in the control center (map)
	*/
	_Ty* allocateNode()
	{
		return allocateData(bufferSize() / sizeof(_Ty));
	}
	/**
	* @brief : Release the buffer for the control center ( map ) node
	*/
	void deallocateNode(void* node)
	{
		deallocate(node);
	}
private:
	Ptr allocate(unsigned n, const void* hint = 0)
	{
		return __allocate((unsigned)n, (Ptr)0);
	}
	void dealloc(Ptr p, unsigned n)
	{
		__deallocate(p);
	}

	void dealloc(void* p)
	{
		__deallocate(p);
	}

	_Ty* allocateData(unsigned n)
	{
		return 0 == n ? 0 : (_Ty*)allocate(n * sizeof(_Ty));
	}

	_Ty* allocateData(void)
	{
		return (_Ty*)allocate(sizeof(_Ty));
	}

	_Ty** allocateMap(unsigned n)
	{
		return 0 == n ? 0 : (_Ty**)allocate(n * sizeof(_Ty*));
	}

	_Ty** allocateMap(void)
	{
		return (_Ty**)allocate(sizeof(_Ty*));
	}

	void deallocData(_Ty* p, unsigned n)
	{
		if (0 != n)
			__deallocate(p);
	}

	void deallocMap(_Ty** p, unsigned n)
	{
		if (0 != n)
			__deallocate(p);
	}

	void deallocate(void* p)
	{
		__deallocate(p);
	}



};

}


#endif // !KH_STL_TYPE_DEQUE_ALLOCATOR_H_