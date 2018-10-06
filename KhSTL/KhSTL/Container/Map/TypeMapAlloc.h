#ifndef KH_STL_TYPE_MAP_ALLOCATOR_H_
#define KH_STL_TYPE_MAP_ALLOCATOR_H_

namespace KhSTL {


template<typename _Kty
	, typename _Ty
	, typename _Comp = tLess<_Kty>
	, typename _Alloc = mapTempAllocator<_Kty>>
	class tMapAlloc : public RBTree<_Kty, _Ty, _Comp>
{
public:

public:

};


}

#endif // KH_STL_TYPE_MAP_ALLOCATOR_H_
