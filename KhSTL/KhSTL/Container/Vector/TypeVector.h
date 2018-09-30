#ifndef KH_STL_TYPE_VECTOR_H_
#define KH_STL_TYPE_VECTOR_H_


#include "TypeVectorBase.h"
#include "../../Utility/TypeIterator.h"

#include <initializer_list>
#include <utility>
//#include <algorithm>
#include <cassert>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:6293)
#endif

namespace KhSTL {

/**
* Vector class
*/
template <typename _Ty>
	class tVector : public tVectorBase
{
public:
	struct CopyTag {};
	struct MoveTag {};

	using ValueType = _Ty;
	using Iterator = tIterator<_Ty>;
	using ConstIterator = tConstIterator<_Ty>;
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
	tVector(unsigned size, const _Ty& value)
	{
		Resize(size);
		for (unsigned i = 0; i < size; ++i)
			At(i) = value;
	}
	/**
	* @brief : Construct with initial data
	*/
	tVector(const _Ty* data, unsigned size)
	{
		doInsertElements(0, data, data + size, CopyTag{});
	}
	/**
	* @brief : Copy-construct from another vector
	*/
	tVector(const tVector<_Ty>& vector)
	{
		doInsertElements(0, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Move-construct from another vector
	*/
	tVector(tVector<_Ty> && vector)
	{
		Swap(vector);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tVector(const std::initializer_list<_Ty>& list)
		: tVector()
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			PushBack(*it);
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
	tVector<_Ty>& operator =(const tVector<_Ty>& rhs)
	{
		// In case of self-assignment do nothing
		if (&rhs != this)
		{
			tVector<_Ty> copy(rhs);
			Swap(copy);
		}
		return *this;
	}
	/**
	* @brief : Move-assign from another vector
	*/
	tVector<_Ty>& operator =(tVector<_Ty> && rhs)
	{
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign an element
	*/
	tVector<_Ty>& operator +=(const _Ty& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign another vector
	*/
	tVector<_Ty>& operator +=(const tVector<_Ty>& rhs)
	{
		Push(rhs);
		return *this;
	}
	/**
	* @brief : Add an element
	*/
	tVector<_Ty> operator +(const _Ty& rhs) const
	{
		tVector<_Ty> ret(*this);
		ret.Push(rhs);
		return ret;
	}
	/**
	* @brief : Add another vector
	*/
	tVector<_Ty> operator +(const tVector<_Ty>& rhs) const
	{
		tVector<_Ty> ret(*this);
		ret.Push(rhs);
		return ret;
	}
	/**
	* @brief : Test for equality with another vector
	*/
	bool operator ==(const tVector<_Ty>& rhs) const
	{
		if (rhs._size != _size)
			return false;

		_Ty* buffer = Buffer();
		_Ty* rhsBuffer = rhs.Buffer();
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
	bool operator !=(const tVector<_Ty>& rhs) const
	{
		if (rhs._size != _size)
			return true;

		_Ty* buffer = Buffer();
		_Ty* rhsBuffer = rhs.Buffer();
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
	_Ty& operator [](unsigned index)
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const _Ty& operator [](unsigned index) const
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return element at index
	*/
	_Ty& At(unsigned index)
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Return const element at index
	*/
	const _Ty& At(unsigned index) const
	{
		assert(index < _size);
		return Buffer()[index];
	}
	/**
	* @brief : Create an element at the end
	*/
	template <typename... Args> _Ty& EmplaceBack(Args&&... args)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) _Ty(std::forward<Args>(args)...);
		}
		else
		{
			_Ty value(std::forward<Args>(args)...);
			PushBack(std::move(value));
		}
		return Back();
	}

#ifndef COVERITY_SCAN_MODEL
	/**
	* @brief : Add an element at the end
	*/
	void PushBack(const _Ty& value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) _Ty(value);
		}
		else
			doInsertElements(_size, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief : Add another vector at the end
	*/

	void PushBack(_Ty && value)
	{
		if (_size < _capacity)
		{
			// Optimize common case
			++_size;
			new (&Back()) _Ty(std::move(value));
		}
		else
			doInsertElements(_size, &value, &value + 1, MoveTag{});
	}
#else
	/**
	* @brief :FIXME: Attempt had been made to use this model in the Coverity-Scan model file without any success
	*			Probably because the model had generated a different mangled name than the one used by static analyzer
	*/
	void PushBack(const _Ty& value)
	{
		T array[] = { value };
		doInsertElements(_size, array, array + 1, CopyTag{});
	}
#endif
	/**
	* @brief : Add another vector at the end
	*/
	void PushBack(const tVector<_Ty>& vector)
	{
		doInsertElements(_size, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Remove the last element
	*/
	void PopBack()
	{
		if (_size)
			Resize(_size - 1);
	}
	/**
	* @brief : Insert an element at position
	*/
	void Insert(unsigned pos, const _Ty& value)
	{
		doInsertElements(pos, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief : Insert an element at position
	*/
	void Insert(unsigned pos, _Ty && value)
	{
		doInsertElements(pos, &value, &value + 1, MoveTag{});
	}
	/**
	* @brief : Insert another vector at position
	*/
	void Insert(unsigned pos, const tVector<_Ty>& vector)
	{
		doInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
	}
	/**
	* @brief : Insert an element by iterator
	*/
	Iterator Insert(const Iterator& dest, const _Ty& value)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, &value, &value + 1, CopyTag{});
	}
	/**
	* @brief : Move-insert an element by iterator
	*/
	Iterator Insert(const Iterator& dest, _Ty && value)
	{
		auto pos = (unsigned)(dest - Begin());
		return doInsertElements(pos, &value, &value + 1, MoveTag{});
	}
	/**
	* @brief : Insert a vector by iterator
	*/
	Iterator Insert(const Iterator& dest, const tVector<_Ty>& vector)
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
	Iterator Insert(const Iterator& dest, const _Ty* start, const _Ty* end)
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
			_Ty* buffer = Buffer();
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
	bool Remove(const _Ty& value)
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
	bool RemoveSwap(const _Ty& value)
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
	void Resize(unsigned newSize, const _Ty& value)
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
			_Ty* newBuffer = nullptr;
			_capacity = newCapacity;

			if (_capacity)
			{
				newBuffer = reinterpret_cast<_Ty*>(allocateBuffer((unsigned)(_capacity * sizeof(_Ty))));
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
	Iterator Find(const _Ty& value)
	{
		Iterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return const iterator to value, or to the end if not found
	*/
	ConstIterator Find(const _Ty& value) const
	{
		ConstIterator it = Begin();
		while (it != End() && *it != value)
			++it;
		return it;
	}
	/**
	* @brief : Return index of value in vector, or size if not found
	*/
	unsigned IndexOf(const _Ty& value) const
	{
		return Find(value) - Begin();
	}
	/**
	* @brief : Return whether contains a specific value
	*/
	bool Contains(const _Ty& value) const { return Find(value) != End(); }
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
	_Ty& Front()
	{
		assert(_size);
		return Buffer()[0];
	}
	/**
	* @brief : Return const first element
	*/
	const _Ty& Front() const
	{
		assert(_size);
		return Buffer()[0];
	}
	/**
	* @brief : Return last element
	*/
	_Ty& Back()
	{
		assert(_size);
		return Buffer()[_size - 1];
	}
	/**
	* @brief : Return const last element
	*/
	const _Ty& Back() const
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
	_Ty* Buffer() const { return reinterpret_cast<_Ty*>(_buffer); }

private:
	/**
	* @brief : Construct elements using default ctor
	*/
	static void constructElements(_Ty* dest, unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) _Ty();
	}
	/**
	* @brief : Copy-construct elements
	*/
	template <typename _RandomIterator>
	static void constructElements(_Ty* dest, _RandomIterator start, _RandomIterator end, CopyTag)
	{
		const unsigned count = end - start;
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) _Ty(*(start + i));
	}
	/**
	* @brief : Move-construct elements
	*/
	template <typename _RandomIterator>
	static void constructElements(_Ty* dest, _RandomIterator start, _RandomIterator end, MoveTag)
	{
		const unsigned count = end - start;
		for (unsigned i = 0; i < count; ++i)
			new(dest + i) _Ty(std::move(*(start + i)));
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
				_Ty* src = Buffer();

				// Reallocate vector
				tVector<_Ty> newVector;
				newVector.Reserve(calculateCapacity(newSize, _capacity));
				newVector._size = _size;
				_Ty* dest = newVector.Buffer();

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
	template <typename _Tag, typename _RandomIterator>
	Iterator doInsertElements(unsigned pos, _RandomIterator start, _RandomIterator end, _Tag)
	{
		if (pos > _size)
			pos = _size;

		const unsigned numElements = end - start;
		if (_size + numElements > _capacity)
		{
			_Ty* src = Buffer();

			// Reallocate vector
			tVector<_Ty> newVector;
			newVector.Reserve(calculateCapacity(_size + numElements, _capacity));
			newVector._size = _size + numElements;
			_Ty* dest = newVector.Buffer();

			// Copy or move new elements
			constructElements(dest + pos, start, end, _Tag{});

			// Move old elements
			if (pos > 0)
				constructElements(dest, src, src + pos, MoveTag{});
			if (pos < _size)
				constructElements(dest + pos + numElements, src + pos, src + _size, MoveTag{});

			Swap(newVector);
		}
		else if (numElements > 0)
		{
			_Ty* buffer = Buffer();

			// Copy or move new elements
			constructElements(buffer + _size, start, end, _Tag{});

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
		_Ty* buffer = Buffer();
		std::move(buffer + pos + count, buffer + _size, buffer + pos);
		Resize(_size - count);
		return Begin() + pos;
	}
	/**
	* @brief : Call the elements' destructors
	*/
	static void destructElements(_Ty* dest, unsigned count)
	{
		while (count--)
		{
			dest->~_Ty();
			++dest;
		}
	}
};


}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif //!KH_STL_TYPE_VECTOR_H_