#ifndef KH_STL_TYPE_SWAP_H_
#define KH_STL_TYPE_SWAP_H_
namespace KhSTL {
namespace Detail
{
class tString;
class tVectorBase;


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

}
}
#endif //!KH_STL_TYPE_SWAP_H_
