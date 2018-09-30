#ifndef KH_STL_TYPE_WSTRING_H_
#define KH_STL_TYPE_WSTRING_H_

namespace KhSTL {

class tString;

class tWString
{
public:
	/**
	* @brief : Construct empty
	*/
	tWString()
		: _length(0)
		, _buffer(nullptr)
	{}
	/**
	* @brief : Construct from a string
	*/
	explicit tWString(const tString& str)
		: _length(0)
		, _buffer(nullptr)
	{}
	/**
	* @brief : Destruct
	*/
	~tWString()
	{
		delete[] _buffer;
	}
	/**
	* @brief : Return char at index
	*/
	wchar_t& operator [](unsigned index)
	{
		assert(index < _length);
		return _buffer[index];
	}

	/**
	* @brief : Return const char at index
	*/
	const wchar_t& operator [](unsigned index) const
	{
		assert(index < _length);
		return _buffer[index];
	}

	/**
	* @brief : Return char at index
	*/
	wchar_t& At(unsigned index)
	{
		assert(index < _length);
		return _buffer[index];
	}
	/**
	* @brief : Return const char at index
	*/
	const wchar_t& At(unsigned index) const
	{
		assert(index < _length);
		return _buffer[index];
	}
	/**
	* @brief : Resize the string
	*/
	void Resize(unsigned newLength)
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
#endif //!KH_STL_TYPE_WSTRING_H_
