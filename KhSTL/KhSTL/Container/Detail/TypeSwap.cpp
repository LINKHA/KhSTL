#include "TypeSwap.h"
#include "TypeString.h"
#include "TypeVectorBase.h"
#include "TypeHashBase.h"
#include "TypeListBase.h"

namespace KhSTL {
namespace Detail
{

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
}