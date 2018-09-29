#ifndef KH_STL_HASH_H_
#define KH_STL_HASH_H_

#ifndef KH_STL_TYPE_HASH_SET_H_
#	include "Container/TypeHashSet.h"
#endif //!KH_STL_TYPE_HASH_SET_H_

#ifndef KH_STL_TYPE_HASH_MAP_H_
#	include "Container/TypeHashMap.h"
#endif //!KH_STL_TYPE_HASH_MAP_H_


namespace KhSTL {
///
///
///
template<typename _Ty> using HashSet = KhSTL::tHashSet<_Ty>;
///
///
///
template<typename _Key, typename _Ty> using HashMap = KhSTL::tHashMap<_Key, _Ty>;
}

#endif //!KH_STL_HASH_H_