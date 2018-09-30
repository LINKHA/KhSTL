#ifndef KH_STL_SET_H_
#define KH_STL_SET_H_


#ifndef KH_STL_TYPE_HASH_SET_H_
#	include "Container/Set/TypeHashSet.h"
#endif //!KH_STL_TYPE_HASH_SET_H_

namespace KhSTL {
///
///
///
template<typename _Ty> using HashSet = KhSTL::tHashSet<_Ty>;

}

#endif // !KH_STL_SET_H_
