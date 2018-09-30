#ifndef KH_STL_TYPE_VECTOR_BASE_H_
#define KH_STL_TYPE_VECTOR_BASE_H_

#include "../Algorithm/TypeAlgorithm.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:6293)
#endif

namespace KhSTL {
/**
* tpye vector base class
*/
class tVectorBase
{
public:
	tVectorBase() noexcept 
		: _size(0)
		, _capacity(0)
		, _buffer(nullptr)
	{}
	~tVectorBase() = default;
	/**
	* @brief : Swap with another vector
	*/
	void Swap(tVectorBase& rhs)
	{
		KhSTL::Swap(_size, rhs._size);
		KhSTL::Swap(_capacity, rhs._capacity);
		KhSTL::Swap(_buffer, rhs._buffer);
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



#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif //!KH_STL_TYPE_VECTOR_BASE_H_
