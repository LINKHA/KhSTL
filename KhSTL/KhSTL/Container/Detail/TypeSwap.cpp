#include "TypeSwap.h"
#include "TypeString.h"
#include "TypeVectorBase.h"

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

}
}