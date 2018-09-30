#ifndef KH_STL_TYPE_VECTOR_BASE_H_
#define KH_STL_TYPE_VECTOR_BASE_H_

namespace KhSTL{
template <typename _Ty>
	class tVectorBase
{
public:
	tVectorBase() noexcept = default;

	/*tVectorBase() noexcept
		: _size(0)
		, _capacity(0)
		, _buffer(nullptr)
	{}*/
	~tVectorBase() = default;
	/**
	* @brief : Swap with another vector
	*/
	void Swap(tVectorBase<_Ty>& rhs)
	{
		KhSTL::Swap(_size, rhs._size);
		KhSTL::Swap(_capacity, rhs._capacity);
		KhSTL::Swap(_buffer, rhs._buffer);
	}
	/**
	* @brief : Return the buffer with right type
	*/
	_Ty* Buffer() const
	{
		return reinterpret_cast<_Ty*>(_buffer);
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
#endif //!KH_STL_TYPE_VECTOR_BASE_H_