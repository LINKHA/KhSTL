#ifndef KH_STL_CORE_TYPE_SWAP_H_
#define KH_STL_CORE_TYPE_SWAP_H_
namespace KH_STL {
namespace Detail
{

/**
* Swap two values.
*/
template <class T> inline void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}



}
}

#endif // !KH_STL_CORE_TYPE_SWAP_H_