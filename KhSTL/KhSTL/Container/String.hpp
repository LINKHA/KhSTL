#pragma once
#include "../KhSTL.h"

KH_STL_BEGIN

/**
* String
*/
class String
{
public:
	/**
	* @brief : Construct
	*/
	String() noexcept
		: _length(0)
		, _capacity(0)
		, _buffer(&_endZero)
	{
	}

	/**
	* @brief : Construct from another string
	*/
	String(const String& str)
		: _length(0)
		, _capacity(0)
		, _buffer(&_endZero)
	{
		*this = str;
	}

	/**
	* @brief : Move-construct from another string.
	*/
	String(String && str) noexcept
		: _length(0)
		, _capacity(0)
		, _buffer(&_endZero)
	{
		Swap(str);
	}

	/**
	* @brief : Construct from a C string.
	*/
	String(const char* str)   // NOLINT(google-explicit-constructor)
		: _length(0)
		, _capacity(0)
		, _buffer(&_endZero)
	{
		*this = str;
	}

	/**
	* @brief : Construct from a C string.
	*/
	String(char* str)          // NOLINT(google-explicit-constructor)
		: _length(0)
		, _capacity(0)
		, _buffer(&_endZero)
	{
		*this = (const char*)str;
	}

	~String()
	{

	}

	/**
	* @brief : Assign a string.
	*/
	String& operator =(const String& rhs)
	{
		if (&rhs != this)
		{
			Resize(rhs._length);
			CopyChars(_buffer, rhs._buffer, rhs._length);
		}

		return *this;
	}
	/// Resize the string.
	void Resize(unsigned newLength);

	void Swap(String& str);

	static unsigned CharPtrLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }
	
	/// Initial dynamic allocation size.
	static const unsigned MIN_CAPACITY = 8;

private:
	/// String length
	unsigned _length;
	/// Capacity, zero if buffer not allocated
	unsigned _capacity;
	/// String buffer, point to &endZero if buffer is not allocated
	char* _buffer;

	/// End zero for empty strings
	static char _endZero;
};

void String::Resize(unsigned newLength)
{
	if (!_capacity)
	{
		// If zero length requested, do not allocate buffer yet
		if (!newLength)
			return;

		// Calculate initial capacity
		_capacity = newLength + 1;
		if (_capacity < MIN_CAPACITY)
			_capacity = MIN_CAPACITY;

		_buffer = new char[_capacity];
	}
	else
	{
		if (newLength && _capacity < newLength + 1)
		{
			// Increase the capacity with half each time it is exceeded
			while (_capacity < newLength + 1)
				_capacity += (_capacity + 1) >> 1u;

			auto* newBuffer = new char[_capacity];
			// Move the existing data to the new buffer, then delete the old buffer
			if (_length)
				CopyChars(newBuffer, _buffer, _length);
			delete[] _buffer;

			_buffer = newBuffer;
		}
	}

	_buffer[newLength] = 0;
	_length = newLength;
}

KH_STL_END
