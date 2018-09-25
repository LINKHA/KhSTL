#ifndef KhSTL_TYPE_ITERATOR_H_
#define KhSTL_TYPE_ITERATOR_H_
#include "TypeBaseIterator.h"

namespace KhSTL {
namespace Detail
{
template <typename _Container> class tIterator
	:tBase_Iterator<_Container>
{
	typedef tIterator<_Container> This;
public:
	/**
	* @brief : Construct
	*/
	tIterator()
		: ptr(nullptr)
	{}
	/**
	* @brief : Construct with an object pointer
	*/
	explicit tIterator(_Container* sptr)
		: ptr(sptr)
	{}
	/**
	* @brief : Point to the object
	*/
	_Container* operator ->() const { return ptr; }
	/**
	* @brief : Dereference the object
	*/
	_Container& operator *() const { return *ptr; }
	/**
	* @brief : Preincrement the pointer
	*/
	tIterator<_Container>& operator ++()
	{
		++ptr;
		return *this;
	}
	/**
	* @brief : Postincrement the pointer
	*/
	tIterator<_Container> operator ++(int)
	{
		tIterator<_Container> it = *this;
		++ptr;
		return it;
	}
	/**
	* @brief : Predecrement the pointer
	*/
	tIterator<_Container>& operator --()
	{
		--ptr;
		return *this;
	}
	/**
	* @brief : Postdecrement the pointer
	*/
	tIterator<_Container> operator --(int)
	{
		tIterator<_Container> it = *this;
		--ptr;
		return it;
	}
	/**
	* @brief : Add an offset to the pointer
	*/
	tIterator<_Container>& operator +=(int value){ ptr += value;return *this;}
	/**
	* @brief : Subtract an offset from the pointer
	*/
	tIterator<_Container>& operator -=(int value){ ptr -= value; return *this;}
	/**
	* @brief : Add an offset to the pointer
	*/
	tIterator<_Container> operator +(int value) const { return tIterator<_Container>(ptr + value); }
	/**
	* @brief : Subtract an offset from the pointer
	*/
	tIterator<_Container> operator -(int value) const { return tIterator<_Container>(ptr - value); }
	/**
	* @brief : Calculate offset to another iterator
	*/
	int operator -(const tIterator& rhs) const { return (int)(ptr - rhs.ptr); }
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const tIterator& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const tIterator& rhs) const { return ptr != rhs.ptr; }
	/**
	* @brief : Test for less than with another iterator
	*/
	bool operator <(const tIterator& rhs) const { return ptr < rhs.ptr; }
	/**
	* @brief : Test for greater than with another iterator
	*/
	bool operator >(const tIterator& rhs) const { return ptr > rhs.ptr; }
	/**
	* @brief : Test for less than or equal with another iterator
	*/
	bool operator <=(const tIterator& rhs) const { return ptr <= rhs.ptr; }
	/**
	* @brief : Test for greater than or equal with another iterator
	*/
	bool operator >=(const tIterator& rhs) const { return ptr >= rhs.ptr; }

	/// Pointer.
	_Container* ptr;
};



template <typename _Container> class tConstIterator
	:tBase_Iterator<_Container>
{
	typedef tConstIterator<_Container> This;
public:
	/**
	* @brief : Construct
	*/
	tConstIterator()
		: ptr(0)
	{}
	/**
	* @brief : Construct with an object pointer
	*/
	explicit tConstIterator(const _Container* sptr)
		: ptr(sptr)
	{}
	/**
	* @brief : Construct from a non-const iterator
	*/
	tConstIterator(const tConstIterator<_Container>& rhs)     // NOLINT(google-explicit-constructor)
		: ptr(rhs.ptr)
	{}
	/**
	* @brief : Assign from a non-const iterator
	*/
	tConstIterator<_Container>& operator =(const tConstIterator<_Container>& rhs)
	{
		ptr = rhs.ptr;
		return *this;
	}
	/**
	* @brief : Point to the object
	*/
	const _Container* operator ->() const { return ptr; }
	/**
	* @brief : Dereference the object
	*/
	const _Container& operator *() const { return *ptr; }
	/**
	* @brief : Preincrement the pointer
	*/
	tConstIterator<_Container>& operator ++()
	{
		++ptr;
		return *this;
	}
	/**
	* @brief : Postincrement the pointer
	*/
	tConstIterator<_Container> operator ++(int)
	{
		tConstIterator<_Container> it = *this;
		++ptr;
		return it;
	}
	/**
	* @brief : Predecrement the pointer
	*/
	tConstIterator<_Container>& operator --()
	{
		--ptr;
		return *this;
	}
	/**
	* @brief : Postdecrement the pointer
	*/
	tConstIterator<_Container> operator --(int)
	{
		tConstIterator<_Container> it = *this;
		--ptr;
		return it;
	}
	/**
	* @brief : Add an offset to the pointer
	*/
	tConstIterator<_Container>& operator +=(int value)
	{
		ptr += value;
		return *this;
	}
	/**
	* @brief : Subtract an offset from the pointer
	*/
	tConstIterator<_Container>& operator -=(int value)
	{
		ptr -= value;
		return *this;
	}
	/**
	* @brief : Add an offset to the pointer
	*/
	tConstIterator<_Container> operator +(int value) const { return tConstIterator<_Container>(ptr + value); }
	/**
	* @brief : Subtract an offset from the pointer
	*/
	tConstIterator<_Container> operator -(int value) const { return tConstIterator<_Container>(ptr - value); }
	/**
	* @brief : Calculate offset to another iterator
	*/
	int operator -(const tConstIterator& rhs) const { return (int)(ptr - rhs.ptr); }
	/**
	* @brief : Test for equality with another iterator
	*/
	bool operator ==(const tConstIterator& rhs) const { return ptr == rhs.ptr; }
	/**
	* @brief : Test for inequality with another iterator
	*/
	bool operator !=(const tConstIterator& rhs) const { return ptr != rhs.ptr; }
	/**
	* @brief : Test for less than with another iterator
	*/
	bool operator <(const tConstIterator& rhs) const { return ptr < rhs.ptr; }
	/**
	* @brief : Test for greater than with another iterator
	*/
	bool operator >(const tConstIterator& rhs) const { return ptr > rhs.ptr; }
	/**
	* @brief : Test for less than or equal with another iterator
	*/
	bool operator <=(const tConstIterator& rhs) const { return ptr <= rhs.ptr; }
	/**
	* @brief : Test for greater than or equal with another iterator
	*/
	bool operator >=(const tConstIterator& rhs) const { return ptr >= rhs.ptr; }

	/// Pointer.
	const _Container* ptr;
};


}
}

#endif //!KhSTL_TYPE_ITERATOR_H_
