#ifndef KH_STL_DEQUE_BASE_H_
#define KH_STL_DEQUE_BASE_H_

#include "../Algorithms/TypeSwap.h"
#include "../Allocator/TypeAllcator.h"

#include <memory>

namespace KhSTL {

template<class _Value
	, unsigned _Size>
	struct tDequeIterator
{
	using ValueType	= _Value;
	using DifferenceType = ptrdiff_t;
	using This = tDequeIterator;
	using Iterator = tDequeIterator<_Value, _Size>;

	/**
	* @brief : Transfer buffer position
	*/
	void SetNode(_Value** newNode)
	{
		node = newNode; 
		first = *newNode; 
		last = first + DifferenceType(BufferSize()); 
	}

	size_t BufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Value) < 512 ? size_t(512 / sizeof(_Size)) : size_t(1));
	}

	_Value& operator *() const { return *cur; }
	_Value* operator ->() const { return &(operator *()); }

	This& operator ++()
	{
		++cur; 
	
		if (cur == last)
		{
			SetNode(node + 1); 
			cur = first;
		}
		return *this;
	}

	This& operator ++(int)
	{
		This it = *this;
		++*this;
		return it;
	}

	This& operator --()
	{
		if (cur == first) 
		{
			SetNode(node - 1); 
			cur = last; 
		}
		--cur;
		return *this;
	}

	This& operator --(int)
	{
		This it = *this;
		--*this;
		return it;
	}

	This& operator +=(DifferenceType n)
	{
		DifferenceType offset = n + (cur - first); 

		if (offset >= 0 && offset < DifferenceType(BufferSize()))
		{
			cur += n;
		}
		else
		{
			DifferenceType nodeOffset = offset > 0
				? offset / DifferenceType(BufferSize()) 
				: - DifferenceType((- offset - 1) / BufferSize()) - 1; 
			SetNode(node + nodeOffset); 
			cur = first + (offset - nodeOffset * DifferenceType(BufferSize()));
		}
		return *this;
	}

	This operator +(DifferenceType n) const
	{
		This it = *this;
		return it += n;
	}

	This& operator -=(DifferenceType n)const { return *this += -n; }

	This operator -(DifferenceType n)const
	{
		This it = *this;
		return it -= n;
	}

	DifferenceType operator -(const This& x)
	{
		return DifferenceType(BufferSize())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	_Value& operator [](DifferenceType n)const { return *(*this + n); }

	bool operator ==(const This& x) const 
	{ 
		return cur == x.cur; 
	}

	bool operator !=(const This& x) const 
	{ 
		return cur != x.cur; 
	}

	bool operator <(const This& x) const
	{
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}


	_Value* cur; 
	_Value* first; 
	_Value* last; 
	_Value** node; 
};


template<class _Value
	, unsigned _Size>
	struct tDequeConstIterator
{
	using ValueType = _Value;
	using DifferenceType = ptrdiff_t;
	using This = tConstDequeIterator;
	using Iterator = tConstDequeIterator<_Value, _Size>;

	/**
	* @brief : Transfer buffer position
	*/
	void SetNode(_Value** newNode)
	{
		node = newNode;
		first = *newNode;
		last = first + DifferenceType(BufferSize());
	}

	size_t BufferSize()
	{
		return _Size != 0 ? _Size : (sizeof(_Value) < 512 ? size_t(512 / sizeof(_Size)) : size_t(1));
	}

	const _Value& operator *() const { return *cur; }
	const _Value* operator ->()const { return &(operator *()); }

	This& operator ++()
	{
		++cur;

		if (cur == last)
		{
			SetNode(node + 1);
			cur = first;
		}
		return *this;
	}

	This& operator ++(int)
	{
		This it = *this;
		++*this;
		return it;
	}

	This& operator --()
	{
		if (cur == first)
		{
			SetNode(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}

	This& operator --(int)
	{
		This it = *this;
		--*this;
		return it;
	}

	This& operator +=(DifferenceType n)
	{
		DifferenceType offset = n + (cur - first);

		if (offset >= 0 && offset < DifferenceType(BufferSize()))
		{
			cur += n;
		}
		else
		{
			DifferenceType nodeOffset = offset > 0
				? offset / DifferenceType(BufferSize())
				: -DifferenceType((-offset - 1) / BufferSize()) - 1;
			SetNode(node + nodeOffset);
			cur = first + (offset - nodeOffset * DifferenceType(BufferSize()));
		}
		return *this;
	}

	This operator +(DifferenceType n) const
	{
		This it = *this;
		return it += n;
	}

	This& operator -=(DifferenceType n)const { return *this += -n; }

	This operator -(DifferenceType n)const
	{
		This it = *this;
		return it -= n;
	}

	DifferenceType operator -(const This& x)
	{
		return DifferenceType(BufferSize())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	_Value& operator [](DifferenceType n)const { return *(*this + n); }

	bool operator ==(const This& x) const
	{
		return cur == x.cur;
	}

	bool operator !=(const This& x) const
	{
		return cur != x.cur;
	}

	bool operator <(const This& x) const
	{
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}


	_Value* cur;
	_Value* first;
	_Value* last;
	_Value** node;
};


}
#endif //!KH_STL_DEQUE_BASE_H_