#ifndef KH_STL_LIST_H_
#define KH_STL_LIST_H_


#ifndef KH_STL_TYPE_LIST_H_
#	include "Container/List/TypeList.h"
#endif //!KH_STL_TYPE_PAIR_H_
#ifndef KH_STL_TYPE_LINKED_LIST_H_
#	include "Container/List/TypeLinkedList.h"
#endif //!KH_STL_TYPE_LINKED_LIST_H_
#ifndef KH_STL_TYPE_FORWARD_LIST_H_
#	include "Container/List/TypeForwardList.h"
#endif //!KH_STL_TYPE_FORWARD_LIST_H_


namespace KhSTL {
///
///
///
template<typename _Ty> using List = KhSTL::tList<_Ty>;
///
///
///
template<typename _Ty> using LinkedList = KhSTL::tLinkedList<_Ty>;
///
///
///
template<typename _Ty> using ForwardList = KhSTL::tForwardList<_Ty>;

}

#endif //!KH_STL_LIST_H_