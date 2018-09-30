#ifndef KH_STL_PAIR_H_
#define KH_STL_PAIR_H_

#ifndef KH_STL_TYPE_PAIR_H_
#	include "Utility/TypePair.h"
#endif //!KH_STL_TYPE_PAIR_H_


namespace KhSTL {
///
///
///
template<typename _First, typename _Second> using Pair = KhSTL::tPair<_First, _Second>;

///
///
///
template<typename _First, typename _Second> constexpr KhSTL::tPair<_First, _Second>
	MakePair(_First&& _Val1, _Second&& _Val2)
{	
	using Mypair = KhSTL::tPair<_First, _Second>;
	return (Mypair(_Val1, _Val2));
}


}

#endif //!KH_STL_HASH_H_