#ifndef KH_STL_HASH_MAP_H_
#define KH_STL_HASH_MAP_H_

#ifndef KH_STL_TYPE_HASH_MAP_H_
#	include "Container/HashMap/TypeHashMap.h"
#endif //!KH_STL_TYPE_HASH_MAP_H_
#ifndef KH_STL_TYPE_HASH_MULTI_SET_H_
#	include "Container/HashMap/TypeHashMultiMap.h"
#endif //!KH_STL_TYPE_HASH_MULTI_MAP_H_
#ifndef KH_STL_TYPE_HASH_UNORDERED_MULTI_SET_H_
#	include "Container/HashMap/TypeHashUnorderedMultiMap.h"
#endif //!KH_STL_TYPE_HASH_UNORDERED_MULTI_MAP_H_
#ifndef KH_STL_TYPE_HASH_UNORDERED_SET_H_
#	include "Container/HashMap/TypeHashUnorderedMap.h"
#endif //!KH_STL_TYPE_HASH_UNORDERED_MAP_H_

namespace KhSTL {
///
///
///
template<typename _Kty, typename _Ty>
using HashMap = KhSTL::tHashMap<_Kty, _Ty>;
///
///
///
template<typename _Ty> using HashMultiMap = KhSTL::tHashMultiMap<_Ty>;
///
///
///
template<typename _Ty> using HashUnorderedMultMap = KhSTL::tHashUnorderedMultMap<_Ty>;
///
///
///
template<typename _Ty> using HashUnorderedMap = KhSTL::tHashUnorderedMap<_Ty>;

}

#endif //!KH_STL_HASH_MAP_H_