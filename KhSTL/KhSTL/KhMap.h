#ifndef KH_STL_MAP_H_
#define KH_STL_MAP_H_



#ifndef KH_STL_TYPE_MAP_H_
#	include "Container/Map/TypeMap.h"
#endif //!KH_STL_TYPE_MAP_H_
#ifndef KH_STL_TYPE_MULTI_MAP_H_
#	include "Container/Map/TypeMultiMap.h"
#endif //!KH_STL_TYPE_MULTI_MAP_H_
#ifndef KH_STL_TYPE_UNORDERED_MAP_H_
#	include "Container/Map/TypeUnorderedMap.h"
#endif //!KH_STL_TYPE_UNORDERED_MAP_H_
#ifndef KH_STL_TYPE_UNORDERED_MULTI_MAP_H_
#	include "Container/Map/TypeUnorderedMultiMap.h"
#endif //!KH_STL_TYPE_UNORDERED_MULTI_MAP_H_

namespace KhSTL {

///
///
///
template<typename _Kty, typename _Ty>
	using Map = KhSTL::tMap<_Kty, _Ty>;
///
///
///
template<typename _Kty, typename _Ty>
	using MultiMap = KhSTL::tMultiMap<_Kty, _Ty>;
///
///
///
template<typename _Kty, typename _Ty>
	using UnorderedMap = KhSTL::tTypeUnorderedMap<_Kty, _Ty>;
///
///
///
template<typename _Kty, typename _Ty>
	using UnorderedMultiMap = KhSTL::tUnorderedMultiMap<_Kty, _Ty>;
}

#endif // !KH_STL_MAP_H_
