#pragma once

#include "STLCom.h"

#include <cstddef>

namespace KhSTL
{

/// Random access iterator.
template <typename _Ty> struct RandomAccessIterator
{
    /// Construct a null iterator.
    RandomAccessIterator() :
        _ptr(nullptr)
    {
    }

    /// Construct from a raw pointer.
    explicit RandomAccessIterator(_Ty* ptr_) :
        _ptr(ptr_)
    {
    }

    /// Point to the object.
    _Ty* operator -> () const { return _ptr; }
    /// Dereference the object.
    _Ty& operator * () const { return *_ptr; }
    /// Preincrement the pointer.
    RandomAccessIterator<_Ty>& operator ++ () { ++_ptr; return *this; }
    /// Postincrement the pointer.
    RandomAccessIterator<_Ty> operator ++ (int) { RandomAccessIterator<_Ty> i = *this; ++_ptr; return i; }
    /// Predecrement the pointer.
    RandomAccessIterator<_Ty>& operator -- () { --_ptr; return *this; }
    /// Postdecrement the pointer.
    RandomAccessIterator<_Ty> operator -- (int) { RandomAccessIterator<_Ty> i = *this; --_ptr; return i; }
    /// Add an offset to the pointer.
    RandomAccessIterator<_Ty>& operator += (int value) { _ptr += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<_Ty>& operator -= (int value) { _ptr -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessIterator<_Ty>& operator += (size_t value) { _ptr += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<_Ty>& operator -= (size_t value) { _ptr -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessIterator<_Ty> operator + (int value) const { return RandomAccessIterator<_Ty>(_ptr + value); }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<_Ty> operator - (int value) const { return RandomAccessIterator<_Ty>(_ptr - value); }
    /// Add an offset to the pointer.
    RandomAccessIterator<_Ty> operator + (size_t value) const { return RandomAccessIterator<_Ty>(_ptr + value); }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<_Ty> operator - (size_t value) const { return RandomAccessIterator<_Ty>(_ptr - value); }
    /// Calculate offset to another iterator.
    int operator - (const RandomAccessIterator& rhs) const { return (int)(_ptr - rhs._ptr); }
    /// Test for equality with another iterator.
    bool operator == (const RandomAccessIterator& rhs) const { return _ptr == rhs._ptr; }
    /// Test for inequality with another iterator.
    bool operator != (const RandomAccessIterator& rhs) const { return _ptr != rhs._ptr; }
    /// Test for less than with another iterator.
    bool operator < (const RandomAccessIterator& rhs) const { return _ptr < rhs._ptr; }
    /// Test for greater than with another iterator.
    bool operator > (const RandomAccessIterator& rhs) const { return _ptr > rhs._ptr; }
    /// Test for less than or equal with another iterator.
    bool operator <= (const RandomAccessIterator& rhs) const { return _ptr <= rhs._ptr; }
    /// Test for greater than or equal with another iterator.
    bool operator >= (const RandomAccessIterator& rhs) const { return _ptr >= rhs._ptr; }

    /// Pointer to the random-accessed object(s).
    _Ty* _ptr;
};

/// Random access const iterator.
template <typename _Ty> struct RandomAccessConstIterator
{
    /// Construct a null iterator.
    RandomAccessConstIterator() :
        _ptr(nullptr)
    {
    }

    /// Construct from a raw pointer.
    explicit RandomAccessConstIterator(_Ty* ptr_) :
        _ptr(ptr_)
    {
    }

    /// Construct from a non-const iterator.
    RandomAccessConstIterator(const RandomAccessIterator<_Ty>& it) :
        _ptr(it._ptr)
    {
    }

    /// Assign from a non-const iterator.
    RandomAccessConstIterator<_Ty>& operator = (const RandomAccessIterator<_Ty>& rhs) { _ptr = rhs._ptr; return *this; }
    /// Point to the object.
    const _Ty* operator -> () const { return _ptr; }
    /// Dereference the object.
    const _Ty& operator * () const { return *_ptr; }
    /// Preincrement the pointer.
    RandomAccessConstIterator<_Ty>& operator ++ () { ++_ptr; return *this; }
    /// Postincrement the pointer.
    RandomAccessConstIterator<_Ty> operator ++ (int) { RandomAccessConstIterator<_Ty> i = *this; ++_ptr; return i; }
    /// Predecrement the pointer.
    RandomAccessConstIterator<_Ty>& operator -- () { --_ptr; return *this; }
    /// Postdecrement the pointer.
    RandomAccessConstIterator<_Ty> operator -- (int) { RandomAccessConstIterator<_Ty> i = *this; --_ptr; return i; }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<_Ty>& operator += (int value) { _ptr += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<_Ty>& operator -= (int value) { _ptr -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<_Ty>& operator += (size_t value) { _ptr += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<_Ty>& operator -= (size_t value) { _ptr -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<_Ty> operator + (int value) const { return RandomAccessConstIterator<_Ty>(_ptr + value); }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<_Ty> operator - (int value) const { return RandomAccessConstIterator<_Ty>(_ptr - value); }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<_Ty> operator + (size_t value) const { return RandomAccessConstIterator<_Ty>(_ptr + value); }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<_Ty> operator - (size_t value) const { return RandomAccessConstIterator<_Ty>(_ptr - value); }
    /// Calculate offset to another iterator.
    int operator - (const RandomAccessConstIterator& rhs) const { return (int)(_ptr - rhs._ptr); }
    /// Test for equality with another iterator.
    bool operator == (const RandomAccessConstIterator& rhs) const { return _ptr == rhs._ptr; }
    /// Test for inequality with another iterator.
    bool operator != (const RandomAccessConstIterator& rhs) const { return _ptr != rhs._ptr; }
    /// Test for less than with another iterator.
    bool operator < (const RandomAccessConstIterator& rhs) const { return _ptr < rhs._ptr; }
    /// Test for greater than with another iterator.
    bool operator > (const RandomAccessConstIterator& rhs) const { return _ptr > rhs._ptr; }
    /// Test for less than or equal with another iterator.
    bool operator <= (const RandomAccessConstIterator& rhs) const { return _ptr <= rhs._ptr; }
    /// Test for greater than or equal with another iterator.
    bool operator >= (const RandomAccessConstIterator& rhs) const { return _ptr >= rhs._ptr; }

    /// Pointer to the random-accessed object(s).
    _Ty* _ptr;
};


template <typename _Ty> struct ReverseIterator
{	// wrap iterator to run it backwards
public:
	using ValueType = typename _Ty::ValueType;

	ReverseIterator()
		: _ptr()
	{	// construct with value-initialized wrapped iterator
	}

	explicit ReverseIterator(_Ty rhs)
		: _ptr(rhs)
	{	// construct wrapped iterator from _Right
	}

	template<class _Other>
	ReverseIterator(const ReverseIterator<_Other>& rhs)
		: _ptr(rhs.Base())
	{	// initialize with compatible Base
	}

	template<class _Other>
	ReverseIterator& operator =(const ReverseIterator<_Other>& rhs)
	{	// assign from compatible Base
		_ptr = rhs.Base();
		return *this;
	}

	_Ty Base() const
	{	// return wrapped iterator
		return _ptr;
	}

	ValueType& operator *() const
	{	// return designated value
		_Ty temp = _ptr;
		temp--;
		return *temp;
	}

	ValueType* operator ->() const
	{	// return pointer to class object
		_Ty tmp = _ptr;
		tmp--;
		ValueType valueTmp = *tmp;
		return &valueTmp;
	}

	ReverseIterator& operator ++()
	{	// preincrement
		--_ptr;
		return *this;
	}

	ReverseIterator operator ++(int)
	{	// postincrement
		ReverseIterator _Tmp = *this;
		--_ptr;
		return (_Tmp);
	}

	ReverseIterator& operator --()
	{	// predecrement
		++_ptr;
		return (*this);
	}

	ReverseIterator operator --(int)
	{	// postdecrement
		ReverseIterator _Tmp = *this;
		++_ptr;
		return (_Tmp);
	}

	// N.B. functions valid for random-access iterators only beyond this point

	ReverseIterator& operator +=(int offset)
	{	// Increment by integer
		_ptr -= offset;
		return (*this);
	}

	ReverseIterator operator +(int offset) const
	{	// return this + integer
		return (ReverseIterator(_ptr - offset));
	}

	ReverseIterator& operator -=(int offset)
	{	// Decrement by integer
		_ptr += offset;
		return (*this);
	}

	ReverseIterator operator -(int offset) const
	{	// return this - integer
		return (ReverseIterator(_ptr + offset));
	}

	ValueType& operator [](int offset) const
	{	// subscript
		return (*(*this + offset));
	}

	bool operator ==(const ReverseIterator& right) const
	{
		return _ptr == right._ptr;
	}
	/**
	* @brief : Test for iterator inequality
	*/
	bool operator !=(const ReverseIterator& right) const
	{
		return _ptr != right._ptr;
	}

	_Ty _ptr;	// the wrapped iterator
};

}
