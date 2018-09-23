#ifndef KH_STL_CORE_TYPE_STRING_H_
#define KH_STL_CORE_TYPE_STRING_H_


#ifdef _MSC_VER
//#pragma warning(disable:6293)
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include <cstring>
#include <cstdio>
#include <cassert>
#include <cstdarg>
#include <cctype>

#include "Type_Iterator.h"
#include "Type_BasicString.h"
#include "Type_Swap.h"
#include "Type_Vector.h"

namespace KH_STL {
namespace Detail
{

class tWString;

#define GET_NEXT_CONTINUATION_BYTE(ptr) *(ptr); if ((unsigned char)*(ptr) < 0x80 || (unsigned char)*(ptr) >= 0xc0) return '?'; else ++(ptr);

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
	tString(const tString& str);
	/**
	* @brief : Move-construct from another string
	*/
	tString(tString && str) noexcept;
	/**
	* @brief : Construct from the C string
	*/
	tString(const char* str);
	/**
	* @brief : Construct from the C string
	*/
	tString(char* str);
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
	explicit tString(const tWString& str);
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
	tString& operator +=(const tString& rhs);
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
		assert(index < _length);
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
	* @brief : Return index to the first occurrence of a character, or NO_POS if not found
	*/
	unsigned Find(char c, unsigned startPos = 0, bool caseSensitive = true) const;
	/**
	* @brief : Return index to the first occurrence of a string, or NO_POS if not found
	*/
	unsigned Find(const tString& str, unsigned startPos, bool caseSensitive) const;
	/**
	* @brief : Return index to the last occurrence of a string, or NPOS if not found
	*/
	unsigned FindLast(const tString& str, unsigned startPos = NO_POS, bool caseSensitive = true) const;
	/**
	* @brief : Return index to the last occurrence of a character, or NO_POS if not found
	*/
	unsigned FindLast(char c, unsigned startPos = NO_POS, bool caseSensitive = true) const;
	/**
	* @brief : Return whether starts with a string
	*/
	bool StartsWith(const tString& str, bool caseSensitive = true) const;
	/**
	* @brief : Return whether ends with a string
	*/
	bool EndsWith(const tString& str, bool caseSensitive = true) const;
	/**
	* @brief : Return C str
	*/
	const char* CStr() const { return _buffer; }
	/**
	* @brief : Return length
	*/
	unsigned Length() const { return _length; }
	/**
	* @brief : Return buffer capacity
	*/
	unsigned Capacity() const { return _capacity; }
	/**
	* @brief : Return whether the string is empty
	*/
	bool Empty() const { return _length == 0; }
	/**
	* @brief : Return comparison result with a string
	*/
	int Compare(const tString& str, bool caseSensitive = true) const;
	/**
	* @brief : Return comparison result with a C string
	*/
	int Compare(const char* str, bool caseSensitive = true) const;
	/**
	* @brief : Return whether contains a specific occurrence of a string
	*/
	bool Contains(const tString& str, bool caseSensitive = true) const { return Find(str, 0, caseSensitive) != NO_POS; }
	/**
	* @brief : Return whether contains a specific char
	*/
	bool Contains(char c, bool caseSensitive = true) const { return Find(c, 0, caseSensitive) != NO_POS; }

	/**
	* @brief : Construct UTF8 content from Latin1
	*/
	void SetUTF8FromLatin1(const char* str);
	/**
	* @brief : Constructing UTF 8 content with wide char
	*/
	void SetUTF8FromWChar(const wchar_t* str);
	/**
	* @brief : Calculate number of characters in UTF8 content
	*/
	unsigned LengthUTF8() const;
	/**
	* @brief : Return byte offset to char in UTF8 content
	*/
	unsigned ByteOffsetUTF8(unsigned index) const;
	/**
	* @brief : Return next Unicode character from UTF8 content and increase byte offset
	*/
	unsigned NextUTF8Char(unsigned& byteOffset) const;
	/**
	* @brief : Return Unicode character at index from UTF8 content
	*/
	unsigned AtUTF8(unsigned index) const;
	/**
	* @brief : Replace Unicode character at index from UTF8 content
	*/
	void ReplaceUTF8(unsigned index, unsigned unicodeChar);
	/**
	* @brief : Append Unicode character at the end as UTF8
	*/
	tString& AppendUTF8(unsigned unicodeChar);
	/**
	* @brief : Return a UTF8 substring from position to end
	*/
	tString SubstringUTF8(unsigned pos) const;
	/**
	* @brief : Return a UTF8 substring with length from position
	*/
	tString SubstringUTF8(unsigned pos, unsigned length) const;
	/**
	* @brief : Return hash value for HashSet & HashMap
	*/
	unsigned ToHash() const;

	/**
	* @brief : Return substrings split by a separator char. By default don't return empty strings
	*/
	static tVector<tString> Split(const char* str, char separator, bool keepEmptyStrings = false);
	/**
	* @brief : Return a string by joining substrings with a 'glue' string
	*/
	static tString Joined(const tVector<tString>& subStrings, const tString& glue);
	/**
	* @brief : Encode Unicode character to UTF8. Pointer will be incremented
	*/
	static void EncodeUTF8(char*& dest, unsigned unicodeChar);
	/**
	* @brief : Decode Unicode character from UTF8. Pointer will be incremented
	*/
	static unsigned DecodeUTF8(const char*& src);
#ifdef _WIN32
	/**
	* @brief : Encode Unicode character to UTF16. Pointer will be incremented
	*/
	static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
	/**
	* @brief : Decode Unicode character from UTF16. Pointer will be incremented
	*/
	static unsigned DecodeUTF16(const wchar_t*& src);
#endif
	/**
	* @brief : Return length of a C string
	*/
	static unsigned CStrLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }

	/**
	* @brief : Append to string using formatting
	*/
	tString& AppendWithFormat(const char* formatString, ...);
	/**
	* @brief : Append to string using variable arguments
	*/
	tString& AppendWithFormatArgs(const char* formatString, va_list args);
	/**
	* @brief : Compare two C strings
	*/
	static int Compare(const char* lhs, const char* rhs, bool caseSensitive);


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



}
}

#endif //!KH_STL_CORE_TYPE_STRING_H_