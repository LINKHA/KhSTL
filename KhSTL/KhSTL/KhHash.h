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
template<typename _Value> using HashSet = KhSTL::tHashSet<_Value>;
///
///
///
template<typename _Key, typename _Value> using HashMap = KhSTL::tHashMap<_Key, _Value>;
}

#endif //!KH_STL_HASH_H_