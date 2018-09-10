#ifndef KH_STL_CORE_TYPE_STRING_H_
#define KH_STL_CORE_TYPE_STRING_H_

#include <cstring>
#include <cstdio>
#include "Type_WString.hpp"

namespace KH_STL {
namespace Detail
{

class WString;

static const int BUFFER_LENGTH = 128;

/**
* String class for LINKH STL
*/
class tString
{
public:
	/**
	* @brief : Construct
	*/
	tString() noexcept;
	/**
	* @brief : Construct from another string
	*/
	tString(const tString& str);
	/**
	* @brief : Move-construct from another string
	*/
	tString(String && str) noexcept;
	/**
	* @brief : Construct from a C string
	*/
	tString(const char* str);
	/**
	* @brief : Construct from a C string
	*/
	tString(char* str);
	/**
	* @brief : Construct from a char array and length
	*/
	tString(const char* str, unsigned length);
	/**
	* @brief : Construction of a wide character array from the null end
	*/
	explicit tString(const wchar_t* str);
	/**
	* @brief : Constructed from a wide array of characters ending in null
	*/
	explicit tString(wchar_t* str);
	/**
	* @brief : Construct from the WString
	*/
	explicit tString(const WString& str);
	/**
	* @brief : Construct from the int
	*/
	explicit tString(int value);
	/**
	* @brief : Construct from the short
	*/
	explicit tString(short value);
	/**
	* @brief : Construct from the long
	*/
	explicit tString(long value);
	/**
	* @brief : Construct from the long long
	*/
	explicit tString(long long value);
	/**
	* @brief : Construct from the unsigned
	*/
	explicit tString(unsigned value);
	/**
	* @brief : Construct from the unsigned short
	*/
	explicit tString(unsigned short value);
	/**
	* @brief : Construct from the unsigned long
	*/
	explicit tString(unsigned long value);
	/**
	* @brief : Construct from the unsigned long long
	*/
	explicit tString(unsigned long long value);
	/**
	* @brief : Construct from the float
	*/
	explicit tString(float value);
	/**
	* @brief : Construct from the double
	*/
	explicit tString(double value);
	/**
	* @brief : Construct from the bool
	*/
	explicit tString(bool value);
	/**
	* @brief : Construct from the char
	*/
	explicit tString(char value);
	/**
	* @brief : Construct from the char and unsigned length.
	*/
	tString(char value, unsigned length);
	/**
	* @brief : Construct from a convertible value
	*/
	template <typename T> explicit tString(const T& value)
		: _length(0)
		, _capacity(0)
		, _buffer(&endZero)
	{
		*this = value.ToString();
	}

	/**
	* @brief : Destruct
	*/
	~tString()
	{
		if (_capacity)
			delete[] _buffer;
	}

	/**
	* @brief : Assign a string.
	*/
	tString& operator =(const tString& rhs)
	{
		if (&rhs != this)
		{
			Resize(rhs._length);
			CopyChars(_buffer, rhs._buffer, rhs._length);
		}
		return *this;
	}


	/**
	* @brief : Resize the string
	*/
	void Resize(unsigned newLength);
	/**
	* @brief : Constructing UTF 8 content with wide characters
	*/
	void SetUTF8FromWChar(const wchar_t* str);


	void Swap(String& str);


	static unsigned CharPtrLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }

	/// Initial dynamic allocation size.
	static const unsigned MIN_CAPACITY = 8;

private:
	/**
	* @brief : Copy chars from one buffer to another.
	*/
	static void CopyChars(char* dest, const char* src, unsigned count)
	{
#ifdef _MSC_VER
		if (count)
			memcpy(dest, src, count);
#else
		char* end = dest + count;
		while (dest != end)
		{
			*dest = *src;
			++dest;
			++src;
	}
#endif
}

	/// string length
	unsigned _length;
	/// capacity, zero if buffer not allocated
	unsigned _capacity;
	/// string buffer, point to &endZero if buffer is not allocated
	char* _buffer;

	/// end zero for empty strings
	static char endZero;
};

tString::tString() noexcept
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{}

tString::tString(const tString& str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = str;
}

tString::tString(tString && str) noexcept
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Swap(str);
}

tString::tString(const char* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = str;
}

tString::tString(char* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = (const char*)str;
}

tString::tString(const char* str, unsigned length)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(length);
	CopyChars(_buffer, str, length);
}

tString::tString(const wchar_t* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str);
}

tString::tString(wchar_t* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str);
}

tString::tString(const WString& str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str.CString());
}
tString::tString(int value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%d", value);
	*this = cBuffer;
}

tString::tString(short value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%d", value);
	*this = cBuffer;

}

tString::tString(long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%ld", value);
	*this = cBuffer;
}

tString::tString(long long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%lld", value);
	*this = cBuffer;

}

tString::tString(unsigned value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%u", value);
	*this = cBuffer;

}

tString::tString(unsigned short value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%u", value);
	*this = cBuffer;

}

tString::tString(unsigned long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%lu", value);
	*this = cBuffer;

}

tString::tString(unsigned long long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%llu", value);
	*this = cBuffer;

}

tString::tString(float value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%g", value);
	*this = cBuffer;

}

tString::tString(double value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%.15g", value);
	*this = cBuffer;

}

tString::tString(bool value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	if (value)
		*this = "true";
	else
		*this = "false";

}

tString::tString(char value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(1);
	_buffer[0] = value;
}

tString::tString(char value, unsigned length)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(length);
	for (unsigned i = 0; i < length; ++i)
		_buffer[i] = value;

}

void tString::Resize(unsigned newLength)
{
	if (!_capacity)
	{
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

void tString::SetUTF8FromWChar(const wchar_t* str)
{
	char temp[7];

	Clear();

	if (!str)
		return;

#ifdef _WIN32
	while (*str)
	{
		unsigned unicodeChar = DecodeUTF16(str);
		char* dest = temp;
		EncodeUTF8(dest, unicodeChar);
		*dest = 0;
		Append(temp);
	}
#else
	while (*str)
	{
		char* dest = temp;
		EncodeUTF8(dest, (unsigned)*str++);
		*dest = 0;
		Append(temp);
	}
#endif
}

void tString::Swap(String & str)
{
	KH_STL::Detail::Swap(_length, str._length);
	KH_STL::Detail::Swap(_capacity, str._capacity);
	KH_STL::Detail::Swap(_buffer, str._buffer);
}

#include "Type_String.inl"

}
}

#endif //!KH_STL_CORE_TYPE_STRING_H_