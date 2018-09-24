#ifndef KH_STL_TYPE_WSTRING_H_
#define KH_STL_TYPE_WSTRING_H_

namespace KhSTL {
namespace Detail
{
class tString;

class tWString
{
public:
	/**
	* @brief : Construct empty
	*/
	tWString();
	/**
	* @brief : Construct from a string
	*/
	explicit tWString(const tString& str);
	/**
	* @brief : Destruct
	*/
	~tWString();
	/**
	* @brief : Return char at index
	*/
	wchar_t& operator [](unsigned index);
	/**
	* @brief : Return const char at index
	*/
	const wchar_t& operator [](unsigned index) const;
	/**
	* @brief : Return char at index
	*/
	wchar_t& At(unsigned index);
	/**
	* @brief : Return const char at index
	*/
	const wchar_t& At(unsigned index) const;
	/**
	* @brief : Resize the string
	*/
	void Resize(unsigned newLength);
	/**
	* @brief : Return whether the string is empty
	*/
	bool Empty() const { return _length == 0; }
	/**
	* @brief : Return length
	*/
	unsigned Length() const { return _length; }
	/**
	* @brief : Return character data
	*/
	const wchar_t* CStr() const { return _buffer; }

private:
	/// String length
	unsigned _length;
	/// String buffer, null if not allocated
	wchar_t* _buffer;
};



}
}


#endif //!KH_STL_TYPE_WSTRING_H_