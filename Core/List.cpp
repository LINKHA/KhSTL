#include "List.h"



namespace KhSTL
{

template<> void Swap<ListBase>(ListBase& first, ListBase& second)
{
    first.Swap(second);
}

void ListBase::AllocatePtrs()
{
    _ptrs = new ListNodeBase*[3];

    SetSize(0);
    _ptrs[1] = nullptr;
    _ptrs[2] = nullptr;
}

}
