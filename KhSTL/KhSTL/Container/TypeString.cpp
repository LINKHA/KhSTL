#include "TypeString.h"
#include "TypeWString.h"

namespace KhSTL {

char tString::endZero = 0;

const tString tString::EMPTY;

		
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

tString::tString(tString&& str) noexcept
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

tString::tString(const tWString& str)
	: _length(0)
	, _capacity(0)
	, _buffer(&endZero)
{
	SetUTF8FromWChar(str.CStr());
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
tString& tString::operator+=(const tString & rhs)
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

tString tString::operator +(const char* rhs) const
{
	unsigned rhsLength = CStrLength(rhs);
	tString str;
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

std::istream& operator >>(std::istream &in, tString& rhs) {
	in >> rhs._buffer;
	return in;
}

std::ostream& operator <<(std::ostream& out, tString& rhs)
{
	out << rhs._buffer;
	return out;
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

void tString::Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength)
{
	int delta = (int)srcLength - (int)length;

	if (pos + length < _length)
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
			if (_buffer[i] == replaceTarget)
				_buffer[i] = replaceParam;
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

void tString::Replace(unsigned pos, unsigned length, const tString& replaceParam)
{
	// If substring is illegal, do nothing
	if (pos + length > _length)
		return;

	Replace(pos, length, replaceParam._buffer, replaceParam._length);
}

void tString::Replace(unsigned pos, unsigned length, const char* replaceParam)
{
	// If substring is illegal, do nothing
	if (pos + length > _length)
		return;

	Replace(pos, length, replaceParam, CStrLength(replaceParam));
}

tString::Iterator tString::Replace(const Iterator& start, const Iterator& end, const tString& replaceParam)
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

tString::Iterator tString::Erase(const Iterator& it)
{
	unsigned pos = (unsigned)(it - Begin());
	if (pos >= _length)
		return End();
	Erase(pos);

	return Begin() + pos;
}

tString::Iterator tString::Erase(const Iterator& start, const Iterator& end)
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
	KhSTL::Swap(_length, str._length);
	KhSTL::Swap(_capacity, str._capacity);
	KhSTL::Swap(_buffer, str._buffer);
}

tString tString::SubString(unsigned pos) const
{
	if (pos < _length)
	{
		tString ret;
		ret.Resize(_length - pos);
		CopyChars(ret._buffer, _buffer + pos, ret._length);

		return ret;
	}
	else
		return tString();
}

tString tString::SubString(unsigned pos, unsigned length) const
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

	return SubString(trimStart, trimEnd - trimStart);
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

unsigned tString::Find(char c, unsigned startPos, bool caseSensitive) const
{
	if (caseSensitive)
	{
		for (unsigned i = startPos; i < _length; ++i)
		{
			if (_buffer[i] == c)
				return i;
		}
	}
	else
	{
		c = (char)tolower(c);
		for (unsigned i = startPos; i < _length; ++i)
		{
			if (tolower(_buffer[i]) == c)
				return i;
		}
	}

	return NO_POS;
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

unsigned tString::FindLast(const tString & str, unsigned startPos, bool caseSensitive) const
{
	if (!str._length || str._length > _length)
		return NO_POS;
	if (startPos > _length - str._length)
		startPos = _length - str._length;

	char first = str._buffer[0];
	if (!caseSensitive)
		first = (char)tolower(first);

	for (unsigned i = startPos; i < _length; --i)
	{
		char c = _buffer[i];
		if (!caseSensitive)
			c = (char)tolower(c);

		if (c == first)
		{
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

				if (c != d)
				{
					found = false;
					break;
				}
			}
			if (found)
				return i;
		}
	}

	return NO_POS;
}

unsigned tString::FindLast(char c, unsigned startPos, bool caseSensitive) const
{
	if (startPos >= _length)
		startPos = _length - 1;

	if (caseSensitive)
	{
		for (unsigned i = startPos; i < _length; --i)
		{
			if (_buffer[i] == c)
				return i;
		}
	}
	else
	{
		c = (char)tolower(c);
		for (unsigned i = startPos; i < _length; --i)
		{
			if (tolower(_buffer[i]) == c)
				return i;
		}
	}

	return NO_POS;
}

bool tString::StartsWith(const tString & str, bool caseSensitive) const
{
	return Find(str, 0, caseSensitive) == 0;
}

bool tString::EndsWith(const tString& str, bool caseSensitive) const
{
	unsigned pos = FindLast(str, Length() - 1, caseSensitive);
	return pos != NO_POS && pos == Length() - str.Length();
}


int tString::tString::Compare(const tString& str, bool caseSensitive) const
{
	return Compare(CStr(), str.CStr(), caseSensitive);
}

int tString::tString::Compare(const char* str, bool caseSensitive) const
{
	return Compare(CStr(), str, caseSensitive);
}


void tString::SetUTF8FromLatin1(const char * str)
{
	char tc[7];

	Clear();
	if (!str)
		return;

	while (*str)
	{
		char* dest = tc;
		EncodeUTF8(dest, (unsigned)*str++);
		*dest = 0;
		Append(tc);
	}
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

unsigned tString::LengthUTF8() const
{
	unsigned ret = 0;

	const char* src = _buffer;
	if (!src)
		return ret;
	const char* end = _buffer + _length;

	while (src < end)
	{
		DecodeUTF8(src);
		++ret;
	}

	return ret;
}

unsigned tString::ByteOffsetUTF8(unsigned index) const
{
	unsigned byteOffset = 0;
	unsigned utfPos = 0;

	while (utfPos < index && byteOffset < _length)
	{
		NextUTF8Char(byteOffset);
		++utfPos;
	}

	return byteOffset;
}

unsigned tString::NextUTF8Char(unsigned& byteOffset) const
{
	if (!_buffer)
		return 0;

	const char* src = _buffer + byteOffset;
	unsigned ret = DecodeUTF8(src);
	byteOffset = (unsigned)(src - _buffer);

	return ret;
}

unsigned tString::AtUTF8(unsigned index) const
{
	unsigned byteOffset = ByteOffsetUTF8(index);
	return NextUTF8Char(byteOffset);
}

void tString::ReplaceUTF8(unsigned index, unsigned unicodeChar)
{
	unsigned utfPos = 0;
	unsigned byteOffset = 0;

	while (utfPos < index && byteOffset < _length)
	{
		NextUTF8Char(byteOffset);
		++utfPos;
	}

	if (utfPos < index)
		return;

	unsigned beginCharPos = byteOffset;
	NextUTF8Char(byteOffset);

	char temp[7];
	char* dest = temp;
	EncodeUTF8(dest, unicodeChar);
	*dest = 0;

	Replace(beginCharPos, byteOffset - beginCharPos, temp, (unsigned)(dest - temp));
}

tString& tString::AppendUTF8(unsigned unicodeChar)
{
	char temp[7];
	char* dest = temp;
	EncodeUTF8(dest, unicodeChar);
	*dest = 0;
	return Append(temp);
}

tString tString::SubstringUTF8(unsigned pos) const
{
	unsigned utf8Length = LengthUTF8();
	unsigned byteOffset = ByteOffsetUTF8(pos);
	tString ret;

	while (pos < utf8Length)
	{
		ret.AppendUTF8(NextUTF8Char(byteOffset));
		++pos;
	}

	return ret;
}

tString tString::SubstringUTF8(unsigned pos, unsigned length) const
{
	unsigned utf8Length = LengthUTF8();
	unsigned byteOffset = ByteOffsetUTF8(pos);
	unsigned endPos = pos + length;
	tString ret;

	while (pos < endPos && pos < utf8Length)
	{
		ret.AppendUTF8(NextUTF8Char(byteOffset));
		++pos;
	}

	return ret;
}

unsigned tString::ToHash() const
{
	unsigned hash = 0;
	const char* ptr = _buffer;
	while (*ptr)
	{
		hash = *ptr + (hash << 6u) + (hash << 16u) - hash;
		++ptr;
	}

	return hash;
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

tString tString::Joined(const tVector<tString>& subStrings, const tString& glue)
{
	if (subStrings.Empty())
		return tString();

	tString joinedString(subStrings[0]);
	for (unsigned i = 1; i < subStrings.Size(); ++i)
		joinedString.Append(glue).Append(subStrings[i]);

	return joinedString;
}

void tString::EncodeUTF8(char*& dest, unsigned unicodeChar)
{
	if (unicodeChar < 0x80)
		*dest++ = unicodeChar;
	else if (unicodeChar < 0x800)
	{
		dest[0] = (char)(0xc0u | ((unicodeChar >> 6u) & 0x1fu));
		dest[1] = (char)(0x80u | (unicodeChar & 0x3fu));
		dest += 2;
	}
	else if (unicodeChar < 0x10000)
	{
		dest[0] = (char)(0xe0u | ((unicodeChar >> 12u) & 0xfu));
		dest[1] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
		dest[2] = (char)(0x80u | (unicodeChar & 0x3fu));
		dest += 3;
	}
	else if (unicodeChar < 0x200000)
	{
		dest[0] = (char)(0xf0u | ((unicodeChar >> 18u) & 0x7u));
		dest[1] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
		dest[2] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
		dest[3] = (char)(0x80u | (unicodeChar & 0x3fu));
		dest += 4;
	}
	else if (unicodeChar < 0x4000000)
	{
		dest[0] = (char)(0xf8u | ((unicodeChar >> 24u) & 0x3u));
		dest[1] = (char)(0x80u | ((unicodeChar >> 18u) & 0x3fu));
		dest[2] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
		dest[3] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
		dest[4] = (char)(0x80u | (unicodeChar & 0x3fu));
		dest += 5;
	}
	else
	{
		dest[0] = (char)(0xfcu | ((unicodeChar >> 30u) & 0x1u));
		dest[1] = (char)(0x80u | ((unicodeChar >> 24u) & 0x3fu));
		dest[2] = (char)(0x80u | ((unicodeChar >> 18u) & 0x3fu));
		dest[3] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
		dest[4] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
		dest[5] = (char)(0x80u | (unicodeChar & 0x3fu));
		dest += 6;
	}
}

unsigned tString::DecodeUTF8(const char*& src)
{
	if (src == nullptr)
		return 0;

	unsigned char char1 = *src++;

	// Check if we are in the middle of a UTF8 character
	if (char1 >= 0x80 && char1 < 0xc0)
	{
		while ((unsigned char)*src >= 0x80 && (unsigned char)*src < 0xc0)
			++src;
		return '?';
	}

	if (char1 < 0x80)
		return char1;
	else if (char1 < 0xe0)
	{
		unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
		return (unsigned)((char2 & 0x3fu) | ((char1 & 0x1fu) << 6u));
	}
	else if (char1 < 0xf0)
	{
		unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
		return (unsigned)((char3 & 0x3fu) | ((char2 & 0x3fu) << 6u) | ((char1 & 0xfu) << 12u));
	}
	else if (char1 < 0xf8)
	{
		unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
		return (unsigned)((char4 & 0x3fu) | ((char3 & 0x3fu) << 6u) | ((char2 & 0x3fu) << 12u) | ((char1 & 0x7u) << 18u));
	}
	else if (char1 < 0xfc)
	{
		unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
		return (unsigned)((char5 & 0x3fu) | ((char4 & 0x3fu) << 6u) | ((char3 & 0x3fu) << 12u) | ((char2 & 0x3fu) << 18u) |
			((char1 & 0x3u) << 24u));
	}
	else
	{
		unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
		unsigned char char6 = GET_NEXT_CONTINUATION_BYTE(src);
		return (unsigned)((char6 & 0x3fu) | ((char5 & 0x3fu) << 6u) | ((char4 & 0x3fu) << 12u) | ((char3 & 0x3fu) << 18u) |
			((char2 & 0x3fu) << 24u) | ((char1 & 0x1u) << 30u));
	}
}

#ifdef _WIN32
void tString::EncodeUTF16(wchar_t*& dest, unsigned unicodeChar)
{
	if (unicodeChar < 0x10000)
		*dest++ = unicodeChar;
	else
	{
		unicodeChar -= 0x10000;
		*dest++ = 0xd800 | ((unicodeChar >> 10) & 0x3ff);
		*dest++ = 0xdc00 | (unicodeChar & 0x3ff);
	}
}

unsigned tString::DecodeUTF16(const wchar_t*& src)
{
	if (src == nullptr)
		return 0;

	unsigned short word1 = *src++;

	// Check if we are at a low surrogate
	if (word1 >= 0xdc00 && word1 < 0xe000)
	{
		while (*src >= 0xdc00 && *src < 0xe000)
			++src;
		return '?';
	}

	if (word1 < 0xd800 || word1 >= 0xe000)
		return word1;
	else
	{
		unsigned short word2 = *src++;
		if (word2 < 0xdc00 || word2 >= 0xe000)
		{
			--src;
			return '?';
		}
		else
			return (((word1 & 0x3ff) << 10) | (word2 & 0x3ff)) + 0x10000;
	}
}
#endif

tString& tString::AppendWithFormat(const char* formatString, ...)
{
	va_list args;
	va_start(args, formatString);
	AppendWithFormatArgs(formatString, args);
	va_end(args);
	return *this;
}

tString& tString::AppendWithFormatArgs(const char* formatString, va_list args)
{
	int pos = 0, lastPos = 0;
	auto length = (int)strlen(formatString);

	while (true)
	{
		// Scan the format string and find %a argument where a is one of d, f, s ...
		while (pos < length && formatString[pos] != '%') pos++;
		Append(formatString + lastPos, (unsigned)(pos - lastPos));
		if (pos >= length)
			return *this;

		char format = formatString[pos + 1];
		pos += 2;
		lastPos = pos;

		switch (format)
		{
			// Integer
		case 'd':
		case 'i':
		{
			int arg = va_arg(args, int);
			Append(tString(arg));
			break;
		}

		// Unsigned
		case 'u':
		{
			unsigned arg = va_arg(args, unsigned);
			Append(tString(arg));
			break;
		}

		// Unsigned long
		case 'l':
		{
			unsigned long arg = va_arg(args, unsigned long);
			Append(tString(arg));
			break;
		}

		// Real
		case 'f':
		{
			double arg = va_arg(args, double);
			Append(tString(arg));
			break;
		}

		// Character
		case 'c':
		{
			int arg = va_arg(args, int);
			Append((char)arg);
			break;
		}

		// C string
		case 's':
		{
			char* arg = va_arg(args, char*);
			Append(arg);
			break;
		}

		// Hex
		case 'x':
		{
			char buf[BUFFER_LENGTH];
			int arg = va_arg(args, int);
			int arglen = ::sprintf(buf, "%x", arg);
			Append(buf, (unsigned)arglen);
			break;
		}

		// Pointer
		case 'p':
		{
			char buf[BUFFER_LENGTH];
			int arg = va_arg(args, int);
			int arglen = ::sprintf(buf, "%p", reinterpret_cast<void*>(arg));
			Append(buf, (unsigned)arglen);
			break;
		}

		case '%':
		{
			Append("%", 1);
			break;
		}

		default:
			printf("Unsupported format specifier: '%c'", format);
			break;
		}
	}
}

int tString::Compare(const char* lhs, const char* rhs, bool caseSensitive)
{
	if (!lhs || !rhs)
		return lhs ? 1 : (rhs ? -1 : 0);

	if (caseSensitive)
		return strcmp(lhs, rhs);
	else
	{
		for (;;)
		{
			auto l = (char)tolower(*lhs);
			auto r = (char)tolower(*rhs);
			if (!l || !r)
				return l ? 1 : (r ? -1 : 0);
			if (l < r)
				return -1;
			if (l > r)
				return 1;

			++lhs;
			++rhs;
		}
	}
}


}
