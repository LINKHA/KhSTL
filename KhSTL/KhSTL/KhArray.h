#ifndef KH_STL_ARRAY_H_
#define KH_STL_ARRAY_H_

#ifndef KH_STL_TYPE_ARRAY_H_
#	include "Container/TypeArray.h"
#endif //!KH_STL_TYPE_ARRAY_H_

namespace KhSTL {
///
///
///
template<typename _Value,unsigned _Max = 0> using Array = KhSTL::tArray<_Value, _Max>;

}
#endif //!KH_STL_ARRAY_H_