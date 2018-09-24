#pragma once

#include "TY_VectorBase.h"
#include "TY_Iterator.h"
#include <initializer_list>
#include <utility>
#include <algorithm>
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
		doInsertElements(0, data, data + size, CopyTag{});
	}
	/**
	* @brief : Copy-construct from another vector
	*/
	tVector(const tVector<T>& vector)
	{
		doInsertElements(0, vector.Begin(), vector.End(), CopyTag{});
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
	tVector(const std::initializer_list<T>& list) 
		: tVector()
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
		destructElements(Buffer(), _size);
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
	
#ifndef COVERITY_SCAN_MODEL
	/**
	* @brief : Add an element at the end
	*/
	void Push(const T& value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) T(value);
		}
		else
			doInsertElements(_size, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief :
	*/

	void Push(T && value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) T(std::move(value));
		}
		else
			doInsertElements(_size, &value, &value + 1, MoveTag{});
	}
#else
	/**
	* @brief :FIXME: Attempt had been made to use this model in the Coverity-Scan model file without any success
	*			Probably because the model had generated a different mangled name than the one used by static analyzer
	*/
	void Push(const T& value)
	{
		T array[] = { value };
		doInsertElements(_size, array, array + 1, CopyTag{});
	}
#endif
	/**
	* @brief : Add another vector at the end
	*/
	void Push(const tVector<T>& vector) 
	{ 
		doInsertElements(_size, vector.Begin(), vector.End(), CopyTag{}); 
	}
	/**
	* @brief : Remove the last element
	*/
	void Pop()
	{
		if (_size)
			Resize(_size - 1);
	}
	/**
	* @brief : Insert an element at position
	*/
	void Insert(unsigned pos, const T& value)
	{
		doInsertElements(pos, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief : Insert an element at position
	*/
	void Insert(unsigned pos, T && value)
	{
		doInsertElements(pos, &value, &value + 1, MoveTag{});
	}
	/**
	* @brief : Insert another vector at position
	*/
	void Insert(unsigned pos, const tVector<T>& vector)
	{
		doInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Insert an element by iterator
	*/
	Iterator Insert(const Iterator& dest, const T& value)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief : Move-insert an element by iterator
	*/
	Iterator Insert(const Iterator& dest, T && value)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, &value, &value + 1, MoveTag{});
	}
	/**
	* @brief : Insert a vector by iterator
	*/
	Iterator Insert(const Iterator& dest, const tVector<T>& vector)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Insert a vector partially by iterators
	*/
	Iterator Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, start, end, CopyTag{});
	}
	/**
	* @brief : Insert elements
	*/
	Iterator Insert(const Iterator& dest, const T* start, const T* end)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, start, end, CopyTag{});
	}
	/**
	* @brief : Erase a range of elements
	*/
	void Erase(unsigned pos, unsigned length = 1)
	{
		// Return if the range is illegal
		if (pos + length > _size || !length)
			return;

		doEraseElements(pos, length);
	}
	/**
	* @brief : Erase a range of elements by swapping elements from the end of the array
	*/
	void EraseSwap(unsigned pos, unsigned length = 1)
	{
		unsigned shiftStartIndex = pos + length;
		// Return if the range is illegal
		if (shiftStartIndex > _size || !length)
			return;

		unsigned newSize = _size - length;
		unsigned trailingCount = _size - shiftStartIndex;
		if (trailingCount <= length)
		{
			// We're removing more elements from the array than exist past the end of the range being removed, so perform a normal shift and destroy
			doEraseElements(pos, length);
		}
		else
		{
			// Swap elements from the end of the array into the empty space
			T* buffer = Buffer();
			std::move(buffer + newSize, buffer + _size, buffer + pos);
			Resize(newSize);
		}
	}
	/**
	* @brief : Erase an element by iterator. Return iterator to the next element
	*/
	Iterator Erase(const Iterator& it)
	{
		auto pos = (unsigned)(it - Begin());
		if (pos >= _size)
			return End();
		Erase(pos);

		return Begin() + pos;
	}
	/**
	* @brief : Erase a range by iterators. Return iterator to the next element
	*/
	Iterator Erase(const Iterator& start, const Iterator& end)
	{
		auto pos = (unsigned)(start - Begin());
		if (pos >= _size)
			return End();
		auto length = (unsigned)(end - start);
		Erase(pos, length);

		return Begin() + pos;
	}
	/**
	* @brief : Erase an element by value.Return true if was found and erased
	*/
	bool Remove(const T& value)
	{
		Iterator i = Find(value);
		if (i != End())
		{
			Erase(i);
			return true;
		}
		else
			return false;
	}
	/**
	* @brief : Erase an element by value by swapping with the last element. 
				Return true if was found and erased
	*/
	bool RemoveSwap(const T& value)
	{
		Iterator i = Find(value);
		if (i != End())
		{
			EraseSwap(i - Begin());
			return true;
		}
		else
			return false;
	}
	/**
	* @brief : Clear the vector
	*/
	void Clear() { Resize(0); }
	/**
	* @brief : Resize the vector
	*/
	void Resize(unsigned newSize) { doResize(newSize); }
	/**
	* @brief : Resize the vector and fill new elements with default value
	*/
	void Resize(unsigned newSize, const T& value)
	{
		unsigned oldSize = Size();
		doResize(newSize);
		for (unsigned i = oldSize; i < newSize; ++i)
			At(i) = value;
	}
	/**
	* @brief : Set new capacity
	*/
	void Reserve(unsigned newCapacity)
	{
		if (newCapacity < _size)
			newCapacity = _size;

		if (newCapacity != _capacity)
		{
			T* newBuffer = nullptr;
			_capacity = newCapacity;

			if (_capacity)
			{
				newBuffer = reinterpret_cast<T*>(allocateBuffer((unsigned)(_capacity * sizeof(T))));
				// Move the data into the new buffer
				constructElements(newBuffer, Begin(), End(), MoveTag{});
			}

			// Delete the old buffer
			destructElements(Buffer(), _size);
			delete[] _buffer;
			_buffer = reinterpret_cast<unsigned char*>(newBuffer);
		}
	}
	/**
	* @brief : Reallocate so that no extra memory is used
	*/
	void Compact() { Reserve(_size); }
	/**
	* @brief : Return iterator to value, or to the end if not found
	*/
	Iterator Find(const T& value)
	{
		Iterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return const iterator to value, or to the end if not found
	*/
	ConstIterator Find(const T& value) const
	{
		ConstIterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return index of value in vector, or size if not found
	*/
	unsigned IndexOf(const T& value) const
	{
		return Find(value) - Begin();
	}
	/**
	* @brief : Return whether contains a specific value
	*/
	bool Contains(const T& value) const { return Find(value) != End(); }
	/**
	* @brief : Return iterator to the beginning
	*/
	Iterator Begin() { return Iterator(Buffer()); }
	/**
	* @brief : Return const iterator to the beginning
	*/
	ConstIterator Begin() const { return ConstIterator(Buffer()); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(Buffer() + _size); }
	/**
	* @brief : Return const iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(Buffer() + _size); }
	/**
	* @brief : Return first element
	*/
	T& Front()
	{
		assert(_size);
		return Buffer()[0];
	}
	/**
	* @brief : Return const first element
	*/
	const T& Front() const
	{
		assert(_size);
		return Buffer()[0];
	}
	/**
	* @brief : Return last element
	*/
	T& Back()
	{
		assert(_size);
		return Buffer()[_size - 1];
	}
	/**
	* @brief : Return const last element
	*/
	const T& Back() const
	{
		assert(_size);
		return Buffer()[_size - 1];
	}
	/**
	* @brief : Return size of vector
	*/
	unsigned Size() const { return _size; }
	/**
	* @brief : Return capacity of vector
	*/
	unsigned Capacity() const { return _capacity; }
	/**
	* @brief : Return whether vector is empty
	*/
	bool Empty() const { return _size == 0; }
	/**
	* @brief : Return the buffer with right type
	*/
	T* Buffer() const { return reinterpret_cast<T*>(_buffer); }

private:
	/**
	* @brief : Construct elements using default ctor
	*/
	static void constructElements(T* dest, unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) T();
	}
	/**
	* @brief : Copy-construct elements
	*/
	template <class RandomIteratorT>
	static void constructElements(T* dest, RandomIteratorT start, RandomIteratorT end, CopyTag)
	{
		const unsigned count = end - start;
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) T(*(start + i));
	}
	/**
	* @brief : Move-construct elements
	*/
	template <class RandomIteratorT>
	static void constructElements(T* dest, RandomIteratorT start, RandomIteratorT end, MoveTag)
	{
		const unsigned count = end - start;
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) T(std::move(*(start + i)));
	}
	/**
	* @brief : Calculate new vector capacity
	*/
	static unsigned calculateCapacity(unsigned size, unsigned capacity)
	{
		if (!capacity)
			return size;
		else
		{
			while (capacity < size)
				capacity += (capacity + 1) >> 1;
			return capacity;
		}
	}
	/**
	* @brief : Resize the vector and create/remove new elements as necessary
	*/
	void doResize(unsigned newSize)
	{
		// If size shrinks, destruct the removed elements
		if (newSize < _size)
			destructElements(Buffer() + newSize, _size - newSize);
		else
		{
			// Allocate new buffer if necessary and copy the current elements
			if (newSize > _capacity)
			{
				T* src = Buffer();

				// Reallocate vector
				tVector<T> newVector;
				newVector.Reserve(calculateCapacity(newSize, _capacity));
				newVector._size = _size;
				T* dest = newVector.Buffer();

				// Move old elements
				constructElements(dest, src, src + _size, MoveTag{});

				Swap(newVector);
			}

			// Initialize the new elements
			constructElements(Buffer() + _size, newSize - _size);
		}

		_size = newSize;
	}
	/**
	* @brief : Insert elements into the vector using copy or move constructor
	*/
	template <class Tag, class RandomIteratorT>
	Iterator doInsertElements(unsigned pos, RandomIteratorT start, RandomIteratorT end, Tag)
	{
		if (pos > _size)
			pos = _size;

		const unsigned numElements = end - start;
		if (_size + numElements > _capacity)
		{
			T* src = Buffer();

			// Reallocate vector
			tVector<T> newVector;
			newVector.Reserve(calculateCapacity(_size + numElements, _capacity));
			newVector._size = _size + numElements;
			T* dest = newVector.Buffer();

			// Copy or move new elements
			constructElements(dest + pos, start, end, Tag{});

			// Move old elements
			if (pos > 0)
				constructElements(dest, src, src + pos, MoveTag{});
			if (pos < _size)
				constructElements(dest + pos + numElements, src + pos, src + _size, MoveTag{});

			Swap(newVector);
		}
		else if (numElements > 0)
		{
			T* buffer = Buffer();

			// Copy or move new elements
			constructElements(buffer + _size, start, end, Tag{});

			// Rotate buffer
			if (pos < _size)
			{
				std::rotate(buffer + pos, buffer + _size, buffer + _size + numElements);
			}

			// Update size
			_size += numElements;
		}

		return Begin() + pos;
	}
	/**
	* @brief : Erase elements from the vector
	*/
	Iterator doEraseElements(unsigned pos, unsigned count)
	{
		assert(count > 0);
		assert(pos + count <= _size);
		T* buffer = Buffer();
		std::move(buffer + pos + count, buffer + _size, buffer + pos);
		Resize(_size - count);
		return Begin() + pos;
	}
	/**
	* @brief : Call the elements' destructors
	*/
	static void destructElements(T* dest, unsigned count)
	{
		while (count--)
		{
			dest->~T();
			++dest;
		}
	}
};




}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
