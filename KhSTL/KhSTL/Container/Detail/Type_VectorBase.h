#pragma once

#include "Type_Swap.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:6293)
#endif

namespace KH_STL {
namespace Detail
{
/**
* tpye vector base class
*/
class tVectorBase
{
public:
	tVectorBase() noexcept :
		_size(0),
		_capacity(0),
		_buffer(nullptr)
	{}
	~tVectorBase() = default;
	/**
	* @brief : Swap with another vector
	*/
	void Swap(tVectorBase& rhs)
	{
		KH_STL::Detail::Swap(_size, rhs._size);
		KH_STL::Detail::Swap(_capacity, rhs._capacity);
		KH_STL::Detail::Swap(_buffer, rhs._buffer);
	}

protected:
	static unsigned char* allocateBuffer(unsigned size) { return new unsigned char[size]; }
	/// Size of vector.
	unsigned _size;
	/// Buffer capacity.
	unsigned _capacity;
	/// Buffer.
	unsigned char* _buffer;
};


}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
