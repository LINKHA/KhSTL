#ifndef KH_STL_PAIR_H_
#define KH_STL_PAIR_H_

///
///
///
#ifndef KH_STL_TYPE_PAIR_H_
#	include "Container/Detail/TypePair.h"
	namespace KhSTL {
		template<typename _Key, typename _Value> using Pair = KhSTL::Detail::tPair<_Key, _Value>;
	}
#endif //!KH_STL_TYPE_PAIR_H_


#endif //!KH_STL_HASH_H_