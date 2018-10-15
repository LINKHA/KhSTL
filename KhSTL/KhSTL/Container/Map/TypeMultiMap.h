#ifndef KH_STL_TYPE_MULTI_MAP_H_
#define KH_STL_TYPE_MULTI_MAP_H_


namespace KhSTL {


template<typename _Kty
	, typename _Ty
	, typename _Comp = tLess<tPair<_Kty, _Ty>>
	, typename _Alloc = tAllocator<tRBTreeNode<_Kty>>>
	class tMultiMap : public RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>
{
	using Base = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;
	using RBTreeType = RBTree<tPair<_Kty, _Ty>, _Comp, _Alloc>;
	using KeyType = _Kty;
	using ValueType = typename Base::ValueType;
	using KeyCompare = _Comp;

public:
	using pointer = typename RBTreeType::pointer;

	using reference = typename RBTreeType::reference;

	using Iterator = typename RBTreeType::Iterator;

	using size_type = typename RBTreeType::size_type;

	using difference_type = typename RBTreeType::difference_type;

	tMultiMap()
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
	~tMultiMap()
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

		Insert(ValueType(k, _Ty()));
	}
	Iterator Insert(const ValueType& x)
	{
		return Base::InsertEqual(x);
	}
	Iterator Find(const KeyType& x)
	{
		return Base::Find(x);
	}
};


}
#endif // !KH_STL_TYPE_MULTI_MAP_H_
