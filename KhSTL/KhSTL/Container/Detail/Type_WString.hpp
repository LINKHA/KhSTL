#ifndef KH_STL_CORE_TYPE_WIDE_STRING_H_
#define KH_STL_CORE_TYPE_WIDE_STRING_H_
namespace KH_STL {
namespace Detail
{
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

#include "Type_WString.inl"

}
}

#endif // ! KH_STL_CORE_TYPE_WIDE_STRING_H_