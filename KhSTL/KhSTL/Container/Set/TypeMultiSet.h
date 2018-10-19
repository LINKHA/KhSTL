#ifndef KH_STL_TYPE_MULTI_SET_H_
#define KH_STL_TYPE_MULTI_SET_H_

#include "../../Utility/TypeRBTree.h"
#include "TypeSetTraits.h"

namespace KhSTL {


template<typename _Kty
	, typename _Comp = tLess<_Kty>
	, typename _Alloc = tAllocator<tRBTreeNode<tSetTraits<_Kty>>>>
	class tMultiSet : public RBTree<tSetTraits<_Kty>, _Comp, _Alloc>
{
public:
	using KeyType = _Kty;
	using ValueType = _Kty;
	using KeyCompare = _Comp;
	using Base = RBTree<tSetTraits<_Kty>, _Comp, _Alloc>;
	using RBTreeType = RBTree<tSetTraits<_Kty>, _Comp, _Alloc>;
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
	_Comp KeyComp() const { return Base::KeyComp(); }

	Iterator Begin()
	{
		return Base::Begin();
	}
	Iterator End()
	{
		return Base::End();
	}
	bool Empty()
	{
		return Base::Empty();
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
	Iterator Insert(const KeyType& x)
	{
		return Base::InsertEqual(x,x);
	}
	Iterator Find(const KeyType& x)
	{
		return Base::Find(x);
	}
};


}

#endif // !KH_STL_TYPE_MULTI_SET_H_