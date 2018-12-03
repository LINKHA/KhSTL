#pragma once
#include "../Algorithm/TypeAlgorithm.h"
namespace Auto3D {

template<typename _Ty> class tSharedPtr
{
public:
	tSharedPtr() noexcept
		: _ptr(nullptr)
	{}

	tSharedPtr(const tSharedPtr<_Ty>& rhs) noexcept
		: _ptr(rhs._ptr)
	{
		AddRef();
	}

	template <class U> tSharedPtr(const tSharedPtr<U>& rhs) noexcept
		: _ptr(rhs._ptr)
	{
		AddRef();
	}

	explicit tSharedPtr(_Ty* ptr) noexcept :
		_ptr(ptr)
	{
		AddRef();
	}
	virtual ~tSharedPtr()noexcept
	{
		ReleaseRef();
	}

	tSharedPtr<T>& operator =(_Ty* ptr)
	{
		if (this->_ptr == ptr)
			return *this;

		tSharedPtr<_Ty> copy(ptr);
		Swap(copy);

		return *this;
	}

	_Ty* operator ->() const { Assert(_ptr); return _ptr; }

	_Ty& operator *() const { Assert(_ptr); return *_ptr; }

	_Ty& operator [](int index) { Assert(_ptr); return _ptr[index]; }

	template <class U> bool operator <(const tSharedPtr<U>& rhs) const { return _ptr < rhs._ptr; }

	template <class U> bool operator ==(const tSharedPtr<U>& rhs) const { return _ptr == rhs._ptr; }

	template <class U> bool operator !=(const tSharedPtr<U>& rhs) const { return _ptr != rhs._ptr; }

	operator _Ty*() const { return _ptr; }

	void Swap(tSharedPtr& rhs) { KhSTL::Swap(_ptr, rhs._ptr); }

	void Reset() { ReleaseRef(); }

	_Ty* Detach()
	{
		_Ty* ptr = _ptr;
		if (_ptr)
		{
			tRefCount* refCount = RefCountPtr();
			++refCount->refs; // 2 refs
			Reset(); // 1 ref
			--refCount->refs; // 0 refs
		}
		return ptr;
	}

	template <class U> void StaticCast(const tSharedPtr<U>& rhs)
	{
		tSharedPtr<T> copy(static_cast<_Ty*>(rhs.Get()));
		Swap(copy);
	}
	template <class U> void DynamicCast(const tSharedPtr<U>& rhs)
	{
		tSharedPtr<_Ty> copy(dynamic_cast<_Ty*>(rhs.Get()));
		Swap(copy);
	}

	bool Null() const { return _ptr == 0; }

	bool NotNull() const { return _ptr != nullptr; }

	_Ty* Get() const { return _ptr; }

	int Refs() const { return _ptr ? _ptr->Refs() : 0; }

	long UseCount()const { return RefCountPtr()->refs; }

private:
	template <class U> friend class tSharedPtr;

	void AddRef()
	{
		if (_ptr)
			_ptr->AddRef();
	}
	void ReleaseRef()
	{
		if (_ptr)
		{
			_ptr->ReleaseRef();
			_ptr = nullptr;
		}
	}

	/// Pointer to the object.
	_Ty* _ptr;

};

/**
* @brief : Perform a static cast from one shared pointer type to another.
*/
template <class _Ty, class U> tSharedPtr<_Ty> StaticCast(const tSharedPtr<U>& ptr)
{
	tSharedPtr<_Ty> ret;
	ret.StaticCast(ptr);
	return ret;
}

/**
* @brief : Perform a dynamic cast from one weak pointer type to another.
*/
template <class T, class U> tSharedPtr<T> DynamicCast(const tSharedPtr<U>& ptr)
{
	tSharedPtr<T> ret;
	ret.DynamicCast(ptr);
	return ret;
}

}