#include "TY_Swap.h"
#include "TY_String.h"
#include "TY_VectorBase.h"

namespace KH_STL {
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