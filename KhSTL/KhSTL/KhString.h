#ifndef KH_STL_STRING_H_
#define KH_STL_STRING_H_


///
///
///
#ifndef KH_STL_TYPE_STRING_H_
#	include "Container/Detail/TypeString.h"
	namespace KhSTL{
		using String = Detail::tString;
	}
#endif //!KH_STL_TYPE_STRING_H_

///
///
///
#ifndef KH_STL_TYPE_WSTRING_H_
#	include "Container/Detail/TypeWString.h"
	namespace KhSTL {
		using WString = Detail::tWString;
	}
#endif //!KH_STL_TYPE_WSTRING_H_



#endif //!KH_STL_STRING_H_