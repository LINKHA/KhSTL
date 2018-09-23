#include "Type_Swap.h"
#include "Type_String.h"
#include "Type_VectorBase.h"

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