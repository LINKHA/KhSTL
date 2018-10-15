#ifndef KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_
#define KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_

namespace KhSTL {

template<typename _Ty
	, typename _Kty
	, typename _Comp
	, typename _Alloc>
	class tRBTreeAlloc
{
public:
	using ValueType = _Kty;
	using AllocType = typename _Alloc::ValueType;
public:
	tRBTreeAlloc()
		: _allocator(new _Alloc())
	{
	}
	~tRBTreeAlloc()
	{
		delete _allocator;
		_allocator = nullptr;
	}
protected:
	/**
	* @brief : Reserve a node
	*/
	AllocType* getNode()
	{
		auto* newNode = static_cast<AllocType*>(allocation());
		new(newNode) AllocType();
		return newNode;
	}
	/**
	* @brief : Reserve a node with initial value
	*/
	AllocType* getNode(const ValueType& value)
	{
		auto* newNode = static_cast<AllocType*>(allocation());
		new(newNode) AllocType(value);
		return newNode;
	}

	/**
	* @brief : Free a node
	*/
	void putNode(AllocType* node)
	{
		free(node);
	}
private:
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

	void* allocation()
	{
		return _allocator->Allocation();
	}

protected:
	_Alloc* _allocator;
};


}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_
