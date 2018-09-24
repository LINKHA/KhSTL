#ifndef KH_STL_VECTOR_INCLUDE
#define KH_STL_VECTOR_INCLUDE

#include "Detail/TY_Vector.h"
namespace KH_STL {
	template<typename T> using Vector =  KH_STL::Detail::tVector<T>;

}
#endif //!KH_STL_VECTOR_INCLUDE