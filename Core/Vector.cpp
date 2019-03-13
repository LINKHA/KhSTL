#include "Allocator.h"
#include "Vector.h"



namespace KhSTL
{

VectorBase::VectorBase() :
    _buffer(nullptr)
{
}

void VectorBase::Swap(VectorBase& vector)
{
    KhSTL::Swap(_buffer, vector._buffer);
}

unsigned char* VectorBase::AllocateBuffer(size_t size)
{
    // Include space for _size and capacity
    return new unsigned char[size + 2 * sizeof(size_t)];
}

template<> void Swap<VectorBase>(VectorBase& first, VectorBase& second)
{
    first.Swap(second);
}

}
