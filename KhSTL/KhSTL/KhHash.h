#ifndef KH_STL_HASH_H_
#define KH_STL_HASH_H_

#include "Container/Detail/TypeHashMap.h"
namespace KhSTL {
///
///
///
#ifndef KH_STL_TYPE_HASH_SET_H_
#	include "Container/Detail/TypeHashSet.h"
	template<typename _Value> using tHashSet							= Detail::tHashSet<_Value>;
#endif //!KH_STL_TYPE_HASH_SET_H_

	///
	///
	///
	template<typename _Key, typename _Value> using tHashMap			= Detail::tHashMap<_Key, _Value>;
}

#endif //!KH_STL_HASH_H_