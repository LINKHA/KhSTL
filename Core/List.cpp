#include "List.h"



namespace KhSTL
{

template<> void Swap<ListBase>(ListBase& first, ListBase& second)
{
    first.Swap(second);
}

void ListBase::AllocatePtrs()
{
    ptrs = new ListNodeBase*[3];

    SetSize(0);
    ptrs[1] = nullptr;
    ptrs[2] = nullptr;
}

}
