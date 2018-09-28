#ifndef KH_STL_DEQUE_H_
#define KH_STL_DEQUE_H_

#ifndef KH_STL_TYPE_DEQUE_H_
#	include "Container/TypeDeque.h"
#endif //!KH_STL_TYPE_DEQUE_H_

namespace KhSTL {
///
///
///
template<typename _Value> using Deque = KhSTL::tDeque<_Value>;

}

#endif // KH_STL_DEQUE_H_
