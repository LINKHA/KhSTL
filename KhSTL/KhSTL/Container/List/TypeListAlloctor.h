#ifndef KH_STL_LIST_ALLOCTOR_H_
#define KH_STL_LIST_ALLOCTOR_H_
#include "../../Allocator/TypeAllcator.h"
namespace KhSTL {

template <typename _Alloc>
class tListAlloc
{
public:
	using Allocator = _Alloc;
	using AllocType = typename _Alloc::ValueType;
protected:
	tListAlloc()
		: _allocator(nullptr)
	{
		_allocator = new _Alloc();
	}
	explicit tListAlloc(unsigned size)
		: _allocator(nullptr)
	{
		_allocator = new _Alloc(size + 1);
	}
	virtual ~tListAlloc()
	{
		delete _allocator;
		_allocator = nullptr;
	}
	AllocType* reserve()
	{
		return _allocator->Reserve();
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	AllocType* reserve(const AllocType& object)
	{
		return _allocator->Reserve(object);
	}
	/**
	* @brief : Destruct and free an object
	*/
	void free(AllocType* object)
	{
		_allocator->Free(object);
	}

	//template<typename _Other> void free(_Other* other)
	//{
	//	_allocator->Free(other);
	//}
	/**
	* @brief : Allocate allocator
	*/
	void* allocation()
	{
		return _allocator->Allocation();
	}
protected:
	_Alloc* _allocator;
};

}
#endif //!KH_STL_LIST_ALLOCTOR_H_s