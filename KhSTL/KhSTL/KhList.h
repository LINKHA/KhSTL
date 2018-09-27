#ifndef KH_STL_LIST_H_
#define KH_STL_LIST_H_

#ifndef KH_STL_TYPE_LIST_H_
#	include "Container/TypeList.h"
#endif //!KH_STL_TYPE_PAIR_H_
#ifndef KH_STL_TYPE_LINKED_LIST_H_
#	include "Container/TypeLinkedList.h"
#endif //!KH_STL_TYPE_LINKED_LIST_H_

namespace KhSTL {
///
///
///
template<typename _Value> using List = KhSTL::tList<_Value>;
///
///
///
template<typename _Value> using LinkedList = KhSTL::tLinkedList<_Value>;


}

#endif //!KH_STL_LIST_H_