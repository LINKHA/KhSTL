#include "TypeSwap.h"
#include "../Container/TypeString.h"
#include "../Container/TypeVectorBase.h"
#include "../Container/TypeHashBase.h"
#include "../Container/TypeListBase.h"

namespace KhSTL {

template<> void Swap(tString& rhs, tString& lfs)
{
	rhs.Swap(lfs);
}
template<> void Swap(tVectorBase& rhs, tVectorBase& lfs)
{
	rhs.Swap(lfs);
}
template <> void Swap(tHashBase& rhs, tHashBase& lfs)
{
	rhs.Swap(lfs);
}
template <> void Swap(tListBase& rhs, tListBase& lfs)
{
	rhs.Swap(lfs);
}


}