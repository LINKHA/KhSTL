#pragma once
namespace KH_STL {
namespace Detail
{
class tString;
class tVectorBase;


/**
* Swap two values.
*/
template <class T> inline void Swap(T& rhs, T& lfs)
{
	T temp = rhs;
	rhs = lfs;
	lfs = temp;
}

template <> void Swap<tString>(tString& rhs, tString& lfs);
template <> void Swap<tVectorBase>(tVectorBase& rhs, tVectorBase& lfs);

}
}
