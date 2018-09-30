#ifndef KH_STL_MAP_H_
#define KH_STL_MAP_H_


#ifndef KH_STL_TYPE_HASH_MAP_H_
#	include "Container/Map/TypeHashMap.h"
#endif //!KH_STL_TYPE_HASH_MAP_H_

namespace KhSTL {
///
///
///
template<typename _Key,typename _Ty> 
	using HashMap = KhSTL::tHashMap<_Key,_Ty>;

}

#endif // !KH_STL_MAP_H_
