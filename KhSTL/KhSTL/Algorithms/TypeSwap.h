#ifndef KH_STL_TYPE_SWAP_H_
#define KH_STL_TYPE_SWAP_H_
namespace KhSTL {

class tString;
class tVectorBase;
class tHashBase;
class tListBase;

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
template <> void Swap<tListBase>(tListBase& rhs, tListBase& lfs);

}
#endif //!KH_STL_TYPE_SWAP_H_
