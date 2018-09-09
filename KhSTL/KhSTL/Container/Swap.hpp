#pragma once
#include "../KhSTL.h"

namespace KH_STL {

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