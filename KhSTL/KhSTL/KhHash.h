#ifndef KH_STL_HASH_H_
#define KH_STL_HASH_H_

///
///
///
#ifndef KH_STL_TYPE_HASH_SET_H_
#	include "Container/Detail/TypeHashSet.h"
	namespace KhSTL {
		template<typename _Value> using tHashSet = Detail::tHashSet<_Value>;
	}
#endif //!KH_STL_TYPE_HASH_SET_H_

///
///
///
#ifndef KH_STL_TYPE_HASH_MAP_H_
#	include "Container/Detail/TypeHashMap.h"
	namespace KhSTL {
		template<typename _Key, typename _Value> using tHashMap = Detail::tHashMap<_Key, _Value>;
	}
#endif //!KH_STL_TYPE_HASH_MAP_H_


#endif //!KH_STL_HASH_H_