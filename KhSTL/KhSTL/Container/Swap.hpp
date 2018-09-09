#pragma once
#include "../KhSTL.h"

KH_STL_BEGIN

/**
* Swap two values.
*/
template <class T> inline void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

KH_STL_END