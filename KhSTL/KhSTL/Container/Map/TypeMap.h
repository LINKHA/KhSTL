#ifndef KH_STL_TYPE_MAP_H_
#define KH_STL_TYPE_MAP_H_

#include "../../Utility/TypeDef.h"
#include "../../Utility/TypeRBTree.h"

namespace KhSTL {

template<typename _Kty
	, typename _Ty
	, typename _Comp = tLess<tPair<_Kty,_Ty>>
	, typename _Alloc = tAllocator<tRBTreeNode<tPair<_Kty, _Ty>>>>
	class tMap : public RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>
{
public:
	///tMap<_Kty, _Ty, _Comp, _Alloc>
	using This = tMap<_Kty, _Ty, _Comp, _Alloc>;
	///RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>
	using Base = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;
	///RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>
	using RBTreeType = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;

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

	tMap() noexcept = default;

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

	int Iterator Begin() 
	{
		return Base::Begin();
	}
	int Iterator End() 
	{ 
		return Base::End();
	}
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
	unsigned max_size()
	{ 
		return Base::max_size();
	}
	void operator[](const KeyType& k)
	{

		Insert(PairType(k, _Ty()));
	}
	tPair<Iterator, bool> Insert(const PairType& x)
	{
		return Base::InsertUnique(x);
	}
	Iterator Find(const KeyType& x) 
	{ 
		return Base::Find(x);
	}

	void Clear()
	{

	}


};

}

#endif // KH_STL_TYPE_MAP_H_
