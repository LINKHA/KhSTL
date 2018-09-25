#ifndef KH_STL_VECTOR_H_
#define KH_STL_VECTOR_H_

#ifndef KH_STL_TYPE_VECTOR_H_
#	include "Container/Detail/TypeVector.h"
#endif


namespace KhSTL {
///
///
///
template<typename _Value> using Vector = KhSTL::Detail::tVector<_Value>;

}


#endif //!KH_STL_VECTOR_H_
