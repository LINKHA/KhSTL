#pragma once
#include "../KhSTL.h"

namespace KH_STL {
class String;

class WString
{
	/// Construct empty.
	WString() 
		: _length(0)
		, _buffer(nullptr)
	{
	}
	/// Construct from a string.
	explicit WString(const String& str);
	/// Destruct.
	~WString();

private:
	unsigned _length;
	char* _buffer;
};

#include "WString.inl"

}