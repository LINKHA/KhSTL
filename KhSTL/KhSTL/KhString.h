#ifndef KH_STL_STRING_H_
#define KH_STL_STRING_H_



#ifndef KH_STL_TYPE_STRING_H_
#	include "Container/Detail/TypeString.h"
#endif //!KH_STL_TYPE_STRING_H_

#ifndef KH_STL_TYPE_WSTRING_H_
#	include "Container/Detail/TypeWString.h"
#endif //!KH_STL_TYPE_WSTRING_H_

namespace KhSTL {
///
///
///
using String = KhSTL::Detail::tString;
///
///
///
using WString = KhSTL::Detail::tWString;
}




#endif //!KH_STL_STRING_H_