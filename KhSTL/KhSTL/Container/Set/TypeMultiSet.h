#ifndef KH_STL_TYPE_MULTI_SET_H_
#define KH_STL_TYPE_MULTI_SET_H_

#include "../../Utility/TypeRBTree.h"

namespace KhSTL {


template<typename _Kty
	, typename _Comp = tLess<_Kty>
	, typename _Alloc = mapTempAllocator<_Kty>>
	class tMultiSet : public RBTree<_Kty, _Comp, _Alloc>
{
	using KeyType = _Kty;
	using ValueType = _Kty;
	using KeyCompare = _Comp;
	using Base = RBTree<_Kty, _Comp, _Alloc>;
	using RBTreeType = RBTree<_Kty, _Comp, _Alloc>;

public:
	using pointer = typename RBTreeType::pointer;

	using reference = typename RBTreeType::reference;

	using Iterator = typename RBTreeType::Iterator;

	using size_type = typename RBTreeType::size_type;

	using difference_type = typename RBTreeType::difference_type;

	tMultiSet()
		//:_reTree(_Comp()) 
	{}

	//	tMap(const tMap<_Kty, _Comp, _Alloc>& rhs) 
	//		:_reTree(rhs._reTree)
	//	{}

		//tMap<_Kty, _Ty, _Comp, _Alloc>& operator =(const tMap<_Kty, _Ty, _Comp, _Alloc>& x)
		//{
		//	//_reTree = x._reTree;
		//	return *this;
		//}
	~tMultiSet()
		//:_reTree(_Comp()) 
	{

	}
	_Comp key_comp() const { return Base::key_comp(); }

	Iterator Begin()
	{
		return Base::Begin();
	}
	Iterator End()
	{
		return Base::End();
	}
	bool empty()
	{
		return Base::empty();
	}
	size_type size()
	{
		return Base::GetSize();
	}
	size_type max_size()
	{
		return Base::max_size();
	}
	void operator[](const KeyType& k)
	{

		Insert(k);
	}
	Iterator Insert(const ValueType& x)
	{
		return Base::insert_equal(x);
	}
	Iterator Find(const KeyType& x)
	{
		return Base::find(x);
	}
};


}

#endif // !KH_STL_TYPE_MULTI_SET_H_