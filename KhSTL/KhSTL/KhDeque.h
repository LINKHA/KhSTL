#ifndef KH_STL_DEQUE_H_
#define KH_STL_DEQUE_H_

#ifndef KH_STL_TYPE_DEQUE_H_
#	include "Container/Deque/TypeDeque.h"
#endif //!KH_STL_TYPE_DEQUE_H_

namespace KhSTL {
///
///
///
template<typename _Ty> using Deque = KhSTL::tDeque<_Ty>;

}

#endif // KH_STL_DEQUE_H_
