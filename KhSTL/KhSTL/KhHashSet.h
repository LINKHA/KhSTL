#ifndef KH_STL_HASH_SET_H_
#define KH_STL_HASH_SET_H_

#ifndef KH_STL_TYPE_HASH_SET_H_
#	include "Container/HashSet/TypeHashSet.h"
#endif //!KH_STL_TYPE_HASH_SET_H_
#ifndef KH_STL_TYPE_HASH_MULTI_SET_H_
#	include "Container/HashSet/TypeHashMultiSet.h"
#endif //!KH_STL_TYPE_HASH_MULTI_SET_H_
#ifndef KH_STL_TYPE_HASH_UNORDERED_MULTI_SET_H_
#	include "Container/HashSet/TypeHashUnorderedMultiSet.h"
#endif //!KH_STL_TYPE_HASH_UNORDERED_MULTI_SET_H_
#ifndef KH_STL_TYPE_HASH_UNORDERED_SET_H_
#	include "Container/HashSet/TypeHashUnorderedSet.h"
#endif //!KH_STL_TYPE_HASH_UNORDERED_SET_H_

namespace KhSTL {
///
///
///
template<typename _Kty, typename _Ty>
using HashSet = KhSTL::tHashSet<_Kty, _Ty>;
///
///
///
template<typename _Ty> using HashMultiSet = KhSTL::tHashMultiSet<_Ty>;
///
///
///
template<typename _Ty> using HashUnorderedMultSet = KhSTL::tHashUnorderedMultSet<_Ty>;
///
///
///
template<typename _Ty> using HashUnorderedSet = KhSTL::tHashUnorderedSet<_Ty>;

}

#endif //!KH_STL_HASH_SET_H_