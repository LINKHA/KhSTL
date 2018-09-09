#pragma once

#include <cstring>
#include <cstdio>
#include "WString.hpp"

namespace KH_STL {
class WString;

static const int BUFFER_LENGTH = 128;

/**
* String class for LINKH STL
*/
class String
{
public:
	/**
	* @brief : Construct
	*/
	String() noexcept;
	/**
	* @brief : Construct from another string
	*/
	String(const String& str);
	/**
	* @brief : Move-construct from another string
	*/
	String(String && str) noexcept;
	/**
	* @brief : Construct from a C string
	*/
	String(const char* str);
	/**
	* @brief : Construct from a C string
	*/
	String(char* str);
	/**
	* @brief : Construct from a char array and length
	*/
	String(const char* str, unsigned length);
	/**
	* @brief : Construction of a wide character array from the null end
	*/
	explicit String(const wchar_t* str);
	/**
	* @brief : Constructed from a wide array of characters ending in null
	*/
	explicit String(wchar_t* str);
	/**
	* @brief : Construct from the WString
	*/
	explicit String(const WString& str);
	/**
	* @brief : Construct from the int
	*/
	explicit String(int value);
	/**
	* @brief : Construct from the short
	*/
	explicit String(short value);
	/**
	* @brief : Construct from the long
	*/
	explicit String(long value);
	/**
	* @brief : Construct from the long long
	*/
	explicit String(long long value);
	/**
	* @brief : Construct from the unsigned
	*/
	explicit String(unsigned value);
	/**
	* @brief : Construct from the unsigned short
	*/
	explicit String(unsigned short value);
	/**
	* @brief : Construct from the unsigned long
	*/
	explicit String(unsigned long value);
	/**
	* @brief : Construct from the unsigned long long
	*/
	explicit String(unsigned long long value);
	/**
	* @brief : Construct from the float
	*/
	explicit String(float value);
	/**
	* @brief : Construct from the double
	*/
	explicit String(double value);
	/**
	* @brief : Construct from the bool
	*/
	explicit String(bool value);
	/**
	* @brief : Construct from the char
	*/
	explicit String(char value);
	/**
	* @brief : Construct from the char and unsigned length.
	*/
	String(char value, unsigned length);
	/**
	* @brief : Construct from a convertible value
	*/
	template <typename T> explicit String(const T& value) 
		: _length(0)
		, _capacity(0)
		, _buffer(&endZero)
	{
		*this = value.ToString();
	}

	/**
	* @brief : Destruct
	*/
	~String()
	{
		if (_capacity)
			delete[] _buffer;
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

String::String() noexcept
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{}

String::String(const String& str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = str;
}

String::String(String && str) noexcept
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Swap(str);
}

String::String(const char* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = str;
}

String::String(char* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = (const char*)str;
}

String::String(const char* str, unsigned length)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(length);
	CopyChars(_buffer, str, length);
}

String::String(const wchar_t* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str);
}

String::String(wchar_t* str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str);
}

String::String(const WString& str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str.CString());
}
String::String(int value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%d", value);
	*this = cBuffer;
}

String::String(short value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%d", value);
	*this = cBuffer;

}

String::String(long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%ld", value);
	*this = cBuffer;
}

String::String(long long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%lld", value);
	*this = cBuffer;

}

String::String(unsigned value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%u", value);
	*this = cBuffer;

}

String::String(unsigned short value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%u", value);
	*this = cBuffer;

}

String::String(unsigned long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%lu", value);
	*this = cBuffer;

}

String::String(unsigned long long value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%llu", value);
	*this = cBuffer;

}

String::String(float value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%g", value);
	*this = cBuffer;

}

String::String(double value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	char cBuffer[BUFFER_LENGTH];
	sprintf(cBuffer, "%.15g", value);
	*this = cBuffer;

}

String::String(bool value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	if (value)
		*this = "true";
	else
		*this = "false";

}

String::String(char value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(1);
	_buffer[0] = value;
}

String::String(char value, unsigned length)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	Resize(length);
	for (unsigned i = 0; i < length; ++i)
		_buffer[i] = value;

}

void String::Resize(unsigned newLength)
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

void String::SetUTF8FromWChar(const wchar_t* str)
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

void String::Swap(String & str)
{
	KH_STL::Swap(_length, str._length);
	KH_STL::Swap(_capacity, str._capacity);
	KH_STL::Swap(_buffer, str._buffer);
}

#include "String.inl"

}

