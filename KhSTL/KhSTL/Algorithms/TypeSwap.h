#ifndef KH_STL_TYPE_SWAP_H_
#define KH_STL_TYPE_SWAP_H_

//#include "../Container/List/TypeList.h"

namespace KhSTL {

class tString;
class tVectorBase;
class tHashBase;
//template <typename _Ty> class tListBase<_Ty>;

/**
* Swap two values.
*/
template <typename T> inline void Swap(T& rhs, T& lfs)
{
	T temp = rhs;
	rhs = lfs;
	lfs = temp;
}

template <> void Swap<tString>(tString& rhs, tString& lfs);
template <> void Swap<tVectorBase>(tVectorBase& rhs, tVectorBase& lfs);
template <> void Swap<tHashBase>(tHashBase& rhs, tHashBase& lfs);
//template <typename _Ty> void Swap<tListBase<_Ty>>(< tListBase<_Ty>& rhs, < tListBase<_Ty>& lfs);

}
#endif //!KH_STL_TYPE_SWAP_H_
