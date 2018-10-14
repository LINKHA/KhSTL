#ifndef KH_STL_TYPE_MAP_H_
#define KH_STL_TYPE_MAP_H_

#include "../../Utility/TypeDef.h"
#include "../../Utility/TypeRBTree.h"

namespace KhSTL {

template<typename _Kty
	, typename _Ty
	, typename _Comp = tLess<tPair<_Kty,_Ty>>
	, typename _Alloc = mapTempAllocator<_Kty>>
	class tMap : public RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>
{
	using This = tMap<_Kty, _Ty, _Comp, _Alloc>;

	using Base = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;

	using RBTreeType = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;

	using KeyType = _Kty;

	using ValueType = _Ty;

	using PairType = typename Base::ValueType;

	using KeyCompare = _Comp;

	
public:
	using pointer = typename RBTreeType::pointer;

	using reference = typename RBTreeType::reference;

	using Iterator = typename RBTreeType::Iterator;

	using size_type = typename RBTreeType::size_type;

	using difference_type = typename RBTreeType::difference_type;

	tMap() 
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
	~tMap()
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

		Insert(PairType(k, _Ty()));
	}
	tPair<Iterator, bool> Insert(const PairType& x)
	{
		return Base::insert_unique(x);
	}
	Iterator Find(const KeyType& x) 
	{ 
		return Base::find(x);
	}
};

}

#endif // KH_STL_TYPE_MAP_H_
