#ifndef KH_STL_CORE_TYPE_VECTOR_H_
#define KH_STL_CORE_TYPE_VECTOR_H_

#include "Type_VectorBase.hpp"
#include "Type_Iterator.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:6293)
#endif

namespace KH_STL {
namespace Detail
{
/**
* Vector class
*/
template <typename T> class tVector : public tVectorBase
{
	struct CopyTag {};
	struct MoveTag {};

	using ValueType = T;
	using Iterator = tIterator<T>;
	using ConstIterator = tConstIterator<T>;
public:
	/**
	* @brief : Construct empty
	*/
	tVector() noexcept = default;
	/**
	* @brief : Construct with initial size
	*/
	explicit tVector(unsigned size)
	{
		Resize(size);
	}
	/**
	* @brief : Construct with initial size and default value
	*/
	tVector(unsigned size, const T& value)
	{
		Resize(size);
		for (unsigned i = 0; i < size; ++i)
			At(i) = value;
	}
	/**
	* @brief : Construct with initial data
	*/
	tVector(const T* data, unsigned size)
	{
		DoInsertElements(0, data, data + size, CopyTag{});
	}
	/**
	* @brief : Copy-construct from another vector
	*/
	tVector(const tVector<T>& vector)
	{
		DoInsertElements(0, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Move-construct from another vector
	*/
	tVector(tVector<T> && vector)
	{
		Swap(vector);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tVector(const std::initializer_list<T>& list) : Vector()
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			Push(*it);
		}
	}
	/**
	* @brief : Destruct
	*/
	~tVector()
	{
		DestructElements(Buffer(), _size);
		delete[] _buffer;
	}

	/**
	* @brief : Assign from another vector
	*/
	tVector<T>& operator =(const tVector<T>& rhs)
	{
		// In case of self-assignment do nothing
		if (&rhs != this)
		{
			tVector<T> copy(rhs);
			Swap(copy);
		}
		return *this;
	}
	/**
	* @brief : Move-assign from another vector
	*/
	tVector<T>& operator =(tVector<T> && rhs)
	{
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign an element
	*/
	tVector<T>& operator +=(const T& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign another vector
	*/
	tVector<T>& operator +=(const tVector<T>& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add an element
	*/
	tVector<T> operator +(const T& rhs) const
	{
		tVector<T> ret(*this);
		ret.Push(rhs);
		return ret;
	}
	/**
	* @brief : Add another vector
	*/
	tVector<T> operator +(const tVector<T>& rhs) const
	{
		tVector<T> ret(*this);
		ret.Push(rhs);
		return ret;
	}
	/**
	* @brief : Test for equality with another vector
	*/
	bool operator ==(const tVector<T>& rhs) const
	{
		if (rhs._size != _size)
			return false;

		T* buffer = Buffer();
		T* rhsBuffer = rhs.Buffer();
		for (unsigned i = 0; i < _size; ++i)
		{
			if (buffer[i] != rhsBuffer[i])
				return false;
		}

		return true;
	}
	/**
	* @brief : Test for inequality with another vector
	*/
	bool operator !=(const tVector<T>& rhs) const
	{
		if (rhs._size != _size)
			return true;

		T* buffer = Buffer();
		T* rhsBuffer = rhs.Buffer();
		for (unsigned i = 0; i < _size; ++i)
		{
			if (buffer[i] != rhsBuffer[i])
				return true;
		}

		return false;
	}
	/**
	* @brief : Return element at index
	*/
	T& operator [](unsigned index)
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const T& operator [](unsigned index) const
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return element at index
	*/
	T& At(unsigned index)
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const T& At(unsigned index) const
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Create an element at the end
	*/
	template <typename... Args> T& EmplaceBack(Args&&... args)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) T(std::forward<Args>(args)...);
		}
		else
		{
			T value(std::forward<Args>(args)...);
			Push(std::move(value));
		}
		return Back();
	}

	/// Add an element at the end.
#ifndef COVERITY_SCAN_MODEL
	void Push(const T& value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) T(value);
		}
		else
			DoInsertElements(_size, &value, &value + 1, CopyTag{});
	}

	/// Move-add an element at the end.
	void Push(T && value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) T(std::move(value));
		}
		else
			DoInsertElements(_size, &value, &value + 1, MoveTag{});
	}
#else
	// FIXME: Attempt had been made to use this model in the Coverity-Scan model file without any success
	// Probably because the model had generated a different mangled name than the one used by static analyzer
	void Push(const T& value)
	{
		T array[] = { value };
		DoInsertElements(_size, array, array + 1, CopyTag{});
	}
#endif


};


#include "Type_Vector.inl"

}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // !KH_STL_CORE_TYPE_VECTOR_H_