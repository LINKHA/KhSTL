#ifndef KH_STL_TYPE_MAP_H_
#define KH_STL_TYPE_MAP_H_

#include "../../Utility/TypeDef.h"
#include "../../Utility/TypeRBTree.h"
#include "TypeMapTraits.h"

namespace KhSTL {


template<typename _Kty
	, typename _Ty
	, typename _Comp = tLess<_Kty>
	, typename _Alloc = tAllocator<tRBTreeNode<tMapTraits<_Kty, _Ty>>>>
	class tMap : public RBTree<tMapTraits<_Kty, _Ty>, _Comp, _Alloc>
{
public:
	///
	using This = tMap<_Kty, _Ty, _Comp, _Alloc>;
	///
	using Base = RBTree<tMapTraits<_Kty, _Ty>, _Comp, _Alloc>;
	///
	using RBTreeType = RBTree<tMapTraits<_Kty, _Ty>, _Comp, _Alloc>;

	using KeyType = _Kty;

	using ValueType = _Ty;

	using PairType = typename Base::ValueType;

	using KeyCompare = _Comp;

	using Iterator = typename RBTreeType::Iterator;

	using ConstIterator = typename RBTreeType::ConstIterator;
	/// Map reverse iterator
	using ReverseIterator = tReverseIterator<Iterator>;
	/// Map const reverse iterator
	using ConstReverseIterator = tReverseIterator<ConstIterator>;
public:

	tMap() = default;

	tMap(const tMap& rhs)
	{
		*this = rhs;
	}

	~tMap()
	{
		Clear();
	}


	_Comp KeyComp() const 
	{
		return Base::KeyComp(); 
	}

	inline Iterator Begin() { return Base::Begin(); }

	inline ConstIterator Begin() const { return Base::Begin(); }

	inline Iterator End() { return Base::End(); }

	inline ConstIterator End() const { return Base::End(); }

	inline ReverseIterator RBegin() { return ReverseIterator(End()); }

	inline ConstReverseIterator RBegin() const { return ReverseIterator(End()); }

	inline ReverseIterator REnd() { return ReverseIterator(Begin()); }

	inline ConstReverseIterator REnd() const { return ReverseIterator(Begin()); }

	bool Empty() 
	{ 
		return Base::Empty();
	}
	unsigned Size() 
	{ 
		return Base::GetSize();
	}
	//_Ty& operator[](const KeyType& key)
	//{
	//	Iterator tmp1 = Insert(PairType(key, _Ty())).first;
	//	return (*tmp1).second;
	//}
	//_Ty& At(const KeyType key)
	//{

	//}
	//const _Ty& At(const KeyType key)
	//{

	//}
	tPair<Iterator, bool> Insert(const KeyType& key, const ValueType& value)
	{
		return Base::InsertUnique(key, value);
	}
	tPair<Iterator, bool> Insert(const PairType& pair)
	{
		return Base::InsertUnique(pair.first, pair);
	}
	Iterator Find(const KeyType& key)
	{ 
		return Base::Find(key);
	}

	void Clear()
	{

	}

};

}

#endif // KH_STL_TYPE_MAP_H_
