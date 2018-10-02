#ifndef KH_STL_TYPE_MAP_H_
#define KH_STL_TYPE_MAP_H_

#include "../../Allocator/TypeAllocator.h"
#include "../../Utility/TypePair.h"
#include "../../Utility/TypeDef.h"

namespace KhSTL {

template <typename _Kty
	, typename _Ty
	, typename _Sort = tLess<_Ty>
	, typename _Alloc = tAllocator<tPair<const _Kty,_Ty>>>
	class tMap
{
public:
	using KeyType = _Kty;
	using DataType = _Ty;
	using ValueType = tPair<const _Kty, _Ty>;
	using Compare = _Sort;
	using RBTree = tTree<_Kty, _Ty, std::identity<_Ty>, _Arr, _Alloc>;

	using pointer = typename RBTree::pointer;
	using reference = typename RBTree::reference;
	using iterator = typename RBTree::iterator;
	using size_type = typename RBTree::size_type;
	using difference_type = typename RBTree::difference_type;

public:

	tMap() 
		:_tree(_Sort())
	{}

	tMap(const tMap<_Kty, _Ty, _Sort, _Alloc>& x)
		:_tree(x._tree)
	{}

	tMap<_Kty, _Ty, _Sort, _Alloc>& operator =(const tMap<_Kty, _Ty, _Sort, _Alloc>& x)
	{
		_tree = x._tree;
		return *this;
	}

	_Sort KeyComp() const
	{ 
		return _tree.KeyComp();
	}
	Iterator Begin() 
	{
		return _tree.Begin(); 
	}

	Iterator End() 
	{
		return _tree.End(); 
	}

	bool Empty() 
	{ 
		return _tree.Empty(); 
	}

	unsigned Size() 
	{ 
		return _tree.Size(); 
	}

	unsigned MaxSize() 
	{
		return _tree.MaxSize(); 
	}

	void operator[](const KeyType& k)
	{
		Insert(ValueType(k, _Ty()));
	}

	tPair<Iterator, bool> Insert(const ValueType& x)
	{
		return _tree.insert_unique(x);
	}

	Iterator Find(const KeyType& x) { return _tree.Find(x); }

private:
	RBTree _tree;
};



}

#endif // KH_STL_TYPE_MAP_H_
