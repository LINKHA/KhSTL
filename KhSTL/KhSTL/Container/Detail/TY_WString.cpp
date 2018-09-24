#include "TY_WString.h"
#include <assert.h>
#include <string.h>

namespace KH_STL {
namespace Detail
{

tWString::tWString()
	: _length(0)
	, _buffer(nullptr)
{}

tWString::tWString(const tString& str)
	: _length(0)
	, _buffer(nullptr)
{}

tWString::~tWString()
{
	delete[] _buffer;
}

wchar_t& tWString::operator [](unsigned index)
{
	assert(index < _length);
	return _buffer[index];
}

const wchar_t& tWString::operator [](unsigned index) const
{
	assert(index < _length);
	return _buffer[index];
}

wchar_t& tWString::At(unsigned index)
{
	assert(index < _length);
	return _buffer[index];
}

const wchar_t& tWString::At(unsigned index) const
{
	assert(index < _length);
	return _buffer[index];
}

void tWString::Resize(unsigned newLength)
{
	if (!newLength)
	{
		delete[] _buffer;
		_buffer = nullptr;
		_length = 0;
	}
	else
	{
		auto* newBuffer = new wchar_t[newLength + 1];
		if (_buffer)
		{
			unsigned copyLength = _length < newLength ? _length : newLength;
			memcpy(newBuffer, _buffer, copyLength * sizeof(wchar_t));
			delete[] _buffer;
		}
		newBuffer[newLength] = 0;
		_buffer = newBuffer;
		_length = newLength;
	}
}


}
}