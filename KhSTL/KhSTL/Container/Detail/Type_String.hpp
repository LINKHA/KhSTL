#ifndef KH_STL_CORE_TYPE_STRING_H_
#define KH_STL_CORE_TYPE_STRING_H_

#include <cstring>
#include <cstdio>
#include <cassert>

#include "Type_WString.hpp"
#include "Type_Iterator.hpp"
#include "Type_BasicString.hpp"
namespace KH_STL {
namespace Detail
{

class WString;

static const int BUFFER_LENGTH = 128;

/**
* String class for LINKH STL
*/
class tString //: public tBasic_String<>
{
	using Iterator = tIterator<char>;
	using ConstIterator = tConstIterator<char>;
public:
	/**
	* @brief : Construct
	*/
	tString() noexcept;
	/**
	* @brief : Construct from another string
	*/
	explicit tString(const tString& str);
	/**
	* @brief : Move-construct from another string
	*/
	explicit tString(String && str) noexcept;
	/**
	* @brief : Construct from the C string
	*/
	explicit tString(const char* str);
	/**
	* @brief : Construct from the C string
	*/
	explicit tString(char* str);
	/**
	* @brief : Construct from the char array and length
	*/
	tString(const char* str, unsigned length);
	/**
	* @brief : Construction of the wide character array from the null end
	*/
	explicit tString(const wchar_t* str);
	/**
	* @brief : Constructed from the wide array of characters ending in null
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
	* @brief : Construct from the convertible value
	*/
	template <typename T> explicit tString(const T& value);
	/**
	* @brief : Destruct
	*/
	~tString();

	/**
	* @brief : Assign the string.
	*/
	tString& operator =(const tString& rhs);
	/**
	* @brief : Move assign the string.
	*/
	tString& operator =(tString && rhs) noexcept;
	/**
	* @brief : Assign the C str
	*/
	tString& operator =(const char* rhs);
	/**
	* @brief : Add assign the string
	*/
	tString& operator +=(const String& rhs);
	/**
	* @brief : Add assign the C str
	*/
	tString& operator +=(const char* rhs);
	/**
	* @brief : Add assign the char
	*/
	tString& operator +=(char rhs);
	/**
	* @brief : Add assign the int(concatenate as string)
	*/
	tString& operator +=(int rhs);
	/**
	* @brief : Add assign the short(concatenate as string) 
	*/
	tString& operator +=(short rhs);
	/**
	* @brief : Add assign the long(concatenate as string) 
	*/
	tString& operator +=(long rhs);
	/**
	* @brief : Add assign the long long(concatenate as string) 
	*/
	tString& operator +=(long long rhs);
	/**
	* @brief : Add assign the unsigned(concatenate as string)
	*/
	tString& operator +=(unsigned rhs);
	/**
	* @brief : Add assign the short unsigned(concatenate as string) 
	*/
	tString& operator +=(unsigned short rhs);
	/**
	* @brief : Add assign the long unsigned(concatenate as string)
	*/
	tString& operator +=(unsigned long rhs);
	/**
	* @brief : Add assign the long long unsigned(concatenate as string)
	*/
	tString& operator +=(unsigned long long rhs);
	/**
	* @brief : Add assign the float(concatenate as string) 
	*/
	tString& operator +=(float rhs);
	/**
	* @brief : Add assign the bool(concatenate as string)
	*/
	tString& operator +=(bool rhs);
	/**
	* @brief : Add assign the arbitrary type(concatenate as string) 
	*/
	template <class T> tString& operator +=(const T& rhs);
	/**
	* @brief : Add the string
	*/
	tString operator +(const tString& rhs) const;
	/**
	* @brief : Add the C str
	*/
	tString operator +(const char* rhs) const;
	/**
	* @brief : Test for equality with another string
	*/
	bool operator ==(const tString& rhs) const;
	/**
	* @brief : Test for inequality with another string.
	*/
	bool operator !=(const tString& rhs) const;
	/**
	* @brief : Test if string is less than another string
	*/
	bool operator <(const tString& rhs) const;
	/**
	* @brief : Test if string is greater than another string
	*/
	bool operator >(const tString& rhs) const;
	/**
	* @brief : Test for equality with the C string
	*/
	bool operator ==(const char* rhs) const;
	/**
	* @brief : Test for inequality with the C string
	*/
	bool operator !=(const char* rhs) const;
	/**
	* @brief : Test if string is less than the C string
	*/
	bool operator <(const char* rhs) const;
	/**
	* @brief : Test if string is greater than the C string
	*/
	bool operator >(const char* rhs) const;
	/**
	* @brief :  Return char at index
	*/
	char& operator [](unsigned index);
	/**
	* @brief : Return const char at index
	*/
	const char& operator [](unsigned index) const;

	/**
	* @brief : Return char at index
	*/
	char& At(unsigned index)
	{
		assert(index < _length);
		return _buffer[index];
	}
	/**
	* @brief : Return char at index
	*/
	const char& At(unsigned index) const
	{
		assert(index < length);
		return _buffer[index];
	}
	/**
	* @brief : Replace substring with another substring
	*/
	void Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength);
	/**
	* @brief : Replace all occurrences of the char
	*/
	void Replace(char replaceTarget, char replaceParam, bool caseSensitive = true);
	/**
	* @brief : Replace all occurrences of the string
	*/
	void Replace(const tString& replaceTarget, const tString& replaceParam, bool caseSensitive = true);
	/**
	* @brief : Replace substring
	*/
	void Replace(unsigned pos, unsigned length, const tString& replaceParam);
	/**
	* @brief : Replace substring with a C string
	*/
	void Replace(unsigned pos, unsigned length, const char* replaceParam);
	/**
	* @brief : Replace substring by iterators
	*/
	Iterator Replace(const Iterator& start, const Iterator& end, const tString& replaceParam);
	/**
	* @brief : Return string with all occurrences of the character replaced
	*/
	tString Replaced(char replaceTarget, char replaceParam, bool caseSensitive = true) const;
	/**
	* @brief : Return string with all occurrences of the string replaced
	*/
	tString Replaced(const tString& replaceTarget, const tString& replaceParam, bool caseSensitive = true) const;
	/**
	* @brief : Append the string
	*/
	tString& Append(const tString& str);
	/**
	* @brief : Append the C string
	*/
	tString& Append(const char* str);
	/**
	* @brief : Append the char
	*/
	tString& Append(char c);
	/**
	* @brief : Append char
	*/
	tString& Append(const char* str, unsigned length);
	/**
	* @brief : Insert string
	*/
	void Insert(unsigned pos, const tString& str);
	/**
	* @brief : Insert character
	*/
	void Insert(unsigned pos, char c);
	/**
	* @brief : Insert string by iterator
	*/
	Iterator Insert(const Iterator& dest, const tString& str);
	/**
	* @brief : Insert the string partially by iterators
	*/
	Iterator Insert(const Iterator& dest, const Iterator& start, const Iterator& end);
	/**
	* @brief : Insert the character by iterator
	*/
	Iterator Insert(const Iterator& dest, char c);
	/**
	* @brief : Erase substring
	*/
	void Erase(unsigned pos, unsigned length = 1);
	/**
	* @brief : Erase char by iterator
	*/
	Iterator Erase(const Iterator& it);
	/**
	* @brief : Erase substring by iterators
	*/
	Iterator Erase(const Iterator& start, const Iterator& end);
	/**
	* @brief : Resize the string
	*/
	void Resize(unsigned newLength);
	/**
	* @brief : Set new capacity
	*/
	void Reserve(unsigned newCapacity);
	/**
	* @brief : Reallocate so that no extra memory is used
	*/
	void Compact();
	/**
	* @brief : Clear the string
	*/
	void Clear();
	/**
	* @brief : Swap with another string
	*/
	void Swap(tString& str);
	/**
	* @brief : Return iterator to the beginning
	*/
	Iterator Begin() { return Iterator(_buffer); }
	/**
	* @brief : Return const iterator to the beginning
	*/
	ConstIterator Begin() const { return ConstIterator(_buffer); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(_buffer + _length); }
	/**
	* @brief : Return const iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(_buffer + _length); }
	/**
	* @brief : Return first char, or 0 if empty
	*/
	char Front() const { return _buffer[0]; }
	/**
	* @brief : Return last char, or 0 if empty
	*/
	char Back() const { return _length ? _buffer[_length - 1] : _buffer[0]; }
	/**
	* @brief : Return a substring from position to end
	*/
	tString SubString(unsigned pos) const;
	/**
	* @brief : Return a substring with length from position
	*/
	tString SubString(unsigned pos, unsigned length) const;
	/**
	* @brief : Return string with whitespace trimmed from the beginning and the end
	*/
	tString Trimmed() const;
	/**
	* @brief : Return string in uppercase
	*/
	tString ToUpper() const;
	/**
	* @brief : Return string in lowercase
	*/
	tString ToLower() const;
	/**
	* @brief : Return substrings split by a separator char. By default don't return empty strings
	*/
	tVector<tString> Split(char separator, bool keepEmptyStrings = false) const;
	/**
	* @brief : Return index to the first occurrence of a string, or NO_POS if not found
	*/
	unsigned Find(const tString& str, unsigned startPos, bool caseSensitive) const;

	/**
	* @brief : Constructing UTF 8 content with wide characters
	*/
	void SetUTF8FromWChar(const wchar_t* str);


	/**
	* @brief : Return C str
	*/
	const char* CStr() const { return _buffer; }

	static unsigned CStrLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }
	/**
	* @brief : Return substrings split by a separator char. By default don't return empty strings.
	*/
	static tVector<tString> Split(const char* str, char separator, bool keepEmptyStrings = false);
	/// Position for "not found."
	static const unsigned NO_POS = 0xffffffff;
	/// Initial dynamic allocation size.
	static const unsigned MIN_CAPACITY = 8;
	/// Empty string.
	static const tString EMPTY;
private:
	/**
	* @brief : Move a range of characters within the string
	*/
	void MoveRange(unsigned dest, unsigned src, unsigned count)
	{
		if (count)
			memmove(_buffer + dest, _buffer + src, count);
	}

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

tString::tString(String && str) noexcept
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

template <typename T> tString::tString(const T& value)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	*this = value.ToString();
}

tString::~tString()
{
	if (_capacity)
		delete[] _buffer;
}

tString& tString::operator =(const tString& rhs)
{
	if (&rhs != this)
	{
		Resize(rhs._length);
		CopyChars(_buffer, rhs._buffer, rhs._length);
	}
	return *this;
}

tString& tString::operator =(tString && rhs) noexcept
{
	assert(&rhs != this);
	Swap(rhs);
	return *this;
}

tString& tString::operator =(const char* rhs)
{
	unsigned rhsLength = CStrLength(rhs);
	Resize(rhsLength);
	CopyChars(_buffer, rhs, rhsLength);

	return *this;
}

tString& tString::operator +=(const String& rhs)
{
	unsigned oldLength = _length;
	Resize(_length + rhs._length);
	CopyChars(_buffer + oldLength, rhs._buffer, rhs._length);

	return *this;
}

tString& tString::operator +=(const char* rhs)
{
	unsigned rhsLength = CStrLength(rhs);
	unsigned oldLength = _length;
	Resize(_length + rhsLength);
	CopyChars(_buffer + oldLength, rhs, rhsLength);

	return *this;
}

tString& tString::operator +=(char rhs)
{
	unsigned oldLength = _length;
	Resize(_length + 1);
	_buffer[oldLength] = rhs;

	return *this;
}

tString& tString::operator +=(int rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(short rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(long rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(long long rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(unsigned rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(unsigned short rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(unsigned long rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(unsigned long long rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(float rhs)
{
	return *this += tString(rhs);
}

tString& tString::operator +=(bool rhs)
{
	return *this += tString(rhs);
}

template <class T> tString& tString::operator +=(const T& rhs)
{ 
	return *this += rhs.ToString(); 
}

tString tString::operator +(const tString& rhs) const
{
	tString str;
	str.Resize(_length + rhs._length);
	CopyChars(str._buffer, _buffer, _length);
	CopyChars(str._buffer + _length, rhs._buffer, rhs._length);

	return str;
}

tString::tString::operator +(const char* rhs) const
{
	unsigned rhslength = CStrLength(rhs);
	tString::str;
	str.Resize(_length + rhsLength);
	CopyChars(str._buffer, _buffer, _length);
	CopyChars(str._buffer + _length, rhs, rhsLength);

	return str;
}

bool tString::operator ==(const tString& rhs) const 
{ 
	return strcmp(CStr(), rhs.CStr()) == 0; 
}

bool tString::operator !=(const tString& rhs) const 
{ 
	return strcmp(CStr(), rhs.CStr()) != 0; 
}

bool tString::operator <(const tString& rhs) const 
{ 
	return strcmp(CStr(), rhs.CStr()) < 0; 
}

bool tString::operator >(const tString& rhs) const 
{ 
	return strcmp(CStr(), rhs.CStr()) > 0; 
}

bool tString::operator ==(const char* rhs) const 
{ 
	return strcmp(CStr(), rhs) == 0; 
}

bool tString::operator !=(const char* rhs) const 
{ 
	return strcmp(CStr(), rhs) != 0; 
}

bool tString::operator <(const char* rhs) const 
{ 
	return strcmp(CStr(), rhs) < 0; 
}

bool tString::operator >(const char* rhs) const
{ 
	return strcmp(CStr(), rhs) > 0; 
}

char& tString::operator [](unsigned index)
{
	assert(index < _length);
	return _buffer[index];
}

const char& tString::operator [](unsigned index) const
{
	assert(index < _length);
	return _buffer[index];
}

void tString::Replace(unsigned pos, unsigned length, const char * srcStart, unsigned srcLength)
{
	int delta = (int)srcLength - (int)length;

	if (pos + length < length_)
	{
		if (delta < 0)
		{
			MoveRange(pos + srcLength, pos + length, _length - pos - length);
			Resize(_length + delta);
		}
		if (delta > 0)
		{
			Resize(_length + delta);
			MoveRange(pos + srcLength, pos + length, _length - pos - length - delta);
		}
	}
	else
		Resize(_length + delta);

	CopyChars(_buffer + pos, srcStart, srcLength);
}

void tString::Replace(char replaceTarget, char replaceParam, bool caseSensitive)
{
	if (caseSensitive)
	{
		for (unsigned i = 0; i < _length; ++i)
		{
			if (_length[i] == replaceTarget)
				_length[i] = replaceParam;
		}
	}
	else
	{
		replaceTarget = (char)tolower(replaceTarget);
		for (unsigned i = 0; i < _length; ++i)
		{
			if (tolower(_buffer[i]) == replaceTarget)
				_buffer[i] = replaceParam;
		}
	}
}

void tString::Replace(const tString & replaceTarget, const tString & replaceParam, bool caseSensitive)
{
	unsigned nextPos = 0;

	while (nextPos < _length)
	{
		unsigned pos = Find(replaceTarget, nextPos, caseSensitive);
		if (pos == NO_POS)
			break;
		Replace(pos, replaceTarget._length, replaceParam);
		nextPos = pos + replaceParam._length;
	}
}

void tString::Replace(unsigned pos, unsigned length, const tString & replaceParam)
{
	// If substring is illegal, do nothing
	if (pos + length > _length)
		return;

	Replace(pos, length, replaceWith._buffer, replaceWith._length);
}

void tString::Replace(unsigned pos, unsigned length, const char * replaceParam)
{
	// If substring is illegal, do nothing
	if (pos + length > _length)
		return;

	Replace(pos, length, replaceParam, CStrLength(replaceParam));
}

Iterator tString::Replace(const Iterator& start, const Iterator& end, const tString& replaceParam)
{
	unsigned pos = (unsigned)(start - Begin());
	if (pos >= _length)
		return End();
	auto length = (unsigned)(end - start);
	Replace(pos, length, replaceParam);

	return Begin() + pos;
}

tString tString::Replaced(char replaceTarget, char replaceParam, bool caseSensitive) const
{
	tString ret(*this);
	ret.Replace(replaceTarget, replaceParam, caseSensitive);
	return ret;
}

tString tString::Replaced(const tString& replaceTarget, const tString& replaceParam, bool caseSensitive) const
{
	tString ret(*this);
	ret.Replace(replaceTarget, replaceParam, caseSensitive);
	return ret;
}

tString& tString::Append(const tString& str)
{
	return *this += str;
}

tString& tString::Append(const char* str)
{
	return *this += str;
}

tString& tString::Append(char c)
{
	return *this += c;
}

tString& tString::Append(const char* str, unsigned length)
{
	if (str)
	{
		unsigned oldLength = _length;
		Resize(oldLength + length);
		CopyChars(&_buffer[oldLength], str, length);
	}
	return *this;
}

void tString::Insert(unsigned pos, const tString& str)
{
	if (pos > _length)
		pos = _length;

	if (pos == _length)
		(*this) += str;
	else
		Replace(pos, 0, str);
}

void tString::Insert(unsigned pos, char c)
{
	if (pos > _length)
		pos = _length;

	if (pos == _length)
		(*this) += c;
	else
	{
		unsigned oldLength = _length;
		Resize(_length + 1);
		MoveRange(pos + 1, pos, oldLength - pos);
		_buffer[pos] = c;
	}
}

tString::Iterator tString::Insert(const tString::Iterator& dest, const tString& str)
{
	unsigned pos = (unsigned)(dest - Begin());
	if (pos > _length)
		pos = _length;
	Insert(pos, str);

	return Begin() + pos;
}

tString::Iterator tString::Insert(const tString::Iterator& dest, const tString::Iterator& start, const tString::Iterator& end)
{
	unsigned pos = (unsigned)(dest - Begin());
	if (pos > _length)
		pos = _length;
	auto length = (unsigned)(end - start);
	Replace(pos, 0, &(*start), length);

	return Begin() + pos;
}

tString::Iterator tString::Insert(const tString::Iterator& dest, char c)
{
	unsigned pos = (unsigned)(dest - Begin());
	if (pos > _length)
		pos = _length;
	Insert(pos, c);

	return Begin() + pos;
}

void tString::Erase(unsigned pos, unsigned length)
{
	Replace(pos, length, tString::EMPTY);
}

Iterator tString::Erase(const Iterator& it)
{
	unsigned pos = (unsigned)(it - Begin());
	if (pos >= _length)
		return End();
	Erase(pos);

	return Begin() + pos;
}

Iterator tString::Erase(const Iterator& start, const Iterator& end)
{
	unsigned pos = (unsigned)(start - Begin());
	if (pos >= _length)
		return End();
	auto length = (unsigned)(end - start);
	Erase(pos, length);

	return Begin() + pos;
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

void tString::Reserve(unsigned newCapacity)
{
	if (newCapacity < _length + 1)
		newCapacity = _length + 1;
	if (newCapacity == _capacity)
		return;

	auto* newBuffer = new char[newCapacity];
	// Move the existing data to the new buffer, then delete the old buffer
	CopyChars(newBuffer, _buffer, _length + 1);
	if (_capacity)
		delete[] _buffer;

	_capacity = newCapacity;
	_buffer = newBuffer;
}

void tString::Compact()
{
	if (_capacity)
		Reserve(_length + 1);
}

void tString::Clear()
{
	Resize(0);
}

void tString::Swap(tString & str)
{
	KH_STL::Detail::Swap(_length, str._length);
	KH_STL::Detail::Swap(_capacity, str._capacity);
	KH_STL::Detail::Swap(_buffer, str._buffer);
}

tString tString::SubString(unsigned pos) const
{
	if (pos < _length)
	{
		String ret;
		ret.Resize(_length - pos);
		CopyChars(ret._buffer, _buffer + pos, ret._length);

		return ret;
	}
	else
		return tString();
}

tString tString::Substring(unsigned pos, unsigned length) const
{
	if (pos < _length)
	{
		tString ret;
		if (pos + length > _length)
			length = _length - pos;
		ret.Resize(length);
		CopyChars(ret._buffer, _buffer + pos, ret._length);

		return ret;
	}
	else
		return tString();
}

tString tString::Trimmed() const
{
	unsigned trimStart = 0;
	unsigned trimEnd = _length;

	while (trimStart < trimEnd)
	{
		char c = _buffer[trimStart];
		if (c != ' ' && c != 9)
			break;
		++trimStart;
	}
	while (trimEnd > trimStart)
	{
		char c = _buffer[trimEnd - 1];
		if (c != ' ' && c != 9)
			break;
		--trimEnd;
	}

	return Substring(trimStart, trimEnd - trimStart);
}

tString tString::ToLower() const
{
	tString ret(*this);
	for (unsigned i = 0; i < ret._length; ++i)
		ret[i] = (char)tolower(_buffer[i]);

	return ret;
}

tString tString::ToUpper() const
{
	tString ret(*this);
	for (unsigned i = 0; i < ret._length; ++i)
		ret[i] = (char)toupper(_buffer[i]);

	return ret;
}

tVector<tString> tString::Split(char separator, bool keepEmptyStrings) const
{
	return Split(CStr(), separator, keepEmptyStrings);
}


unsigned tString::Find(const tString& str, unsigned startPos, bool caseSensitive) const
{
	if (!str._length || str._length > _length)
		return NO_POS;

	char first = str._buffer[0];
	if (!caseSensitive)
		first = (char)tolower(first);

	for (unsigned i = startPos; i <= _length - str._length; ++i)
	{
		char c = _buffer[i];
		if (!caseSensitive)
			c = (char)tolower(c);

		if (c == first)
		{
			unsigned skip = NO_POS;
			bool found = true;
			for (unsigned j = 1; j < str._length; ++j)
			{
				c = _buffer[i + j];
				char d = str._buffer[j];
				if (!caseSensitive)
				{
					c = (char)tolower(c);
					d = (char)tolower(d);
				}

				if (skip == NO_POS && c == first)
					skip = i + j - 1;

				if (c != d)
				{
					found = false;
					if (skip != NO_POS)
						i = skip;
					break;
				}
			}
			if (found)
				return i;
		}
	}

	return NO_POS;
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

tVector<tString> tString::Split(const char* str, char separator, bool keepEmptyStrings)
{
	tVector<tString> ret;
	const char* strEnd = str + tString::CStrLength(str);

	for (const char* splitEnd = str; splitEnd != strEnd; ++splitEnd)
	{
		if (*splitEnd == separator)
		{
			const ptrdiff_t splitLen = splitEnd - str;
			if (splitLen > 0 || keepEmptyStrings)
				ret.Push(tString(str, splitLen));
			str = splitEnd + 1;
		}
	}

	const ptrdiff_t splitLen = strEnd - str;
	if (splitLen > 0 || keepEmptyStrings)
		ret.Push(tString(str, splitLen));

	return ret;
}


#include "Type_String.inl"

}
}

#endif //!KH_STL_CORE_TYPE_STRING_H_